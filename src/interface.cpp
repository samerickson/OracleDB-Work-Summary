#include "interface.hpp"
#include "statementKeys.hpp"

using namespace std;

Interface::Interface(Connection *conn, Statement *stmt[])
{
    // Make the user employee 1234, who is a technician by default
    //  this is for prototyping, normally, the employee would login
    //  to the system and their login credentials would be used to
    //  populate this information.
    this->mainMenu = 4;
    this->invoiceOpt = 5;
    this->state = 0;
    this->eid = 3;
    this->conn = conn;
    this->stmt = stmt;
    this->dataChanged = false;
}

Interface::~Interface() {}

// Make user an admin -- this is a utility function for prototyping
void Interface::makeAdmin() {
    mainMenu = 1;
    invoiceOpt = 3;
    eid = 1;
}

// API for getting current interface state
int Interface::getState()
{
    return state;
}

void Interface::setState(int p)
{
    state = p;
}

// Display red error message to the user
void Interface::errorMsg(string msg)
{
    cerr << "\033[1;31m" << '\n' << msg << '\n' << "\033[0m" << endl;
}

// Display success message in green to the user
void Interface::successMsg(string msg)
{
    cout << "\033[;32m]" << '\n' << msg << '\n' << "\033[0m" << endl;
}

// Gets passed a selection, then an array of valid responses,
//  then an array of states corresponding to the valid responses by index,
//  then the size of the two arrays
bool Interface::checkSelection(char s, const stateMap* m, int size)
{
    for (int i = 0; i < size; i++)
    {
        if(s == m[i].key){
            state = m[i].value;
            return true;
        }
    }

    string res(1, s);
    errorMsg("ERROR: " + res + " is an invalid selection.");

    cin.ignore();

    return false;
}

// Helper function for creating text interfaces
char Interface::createInterface(string prompt, const stateMap* m, int n)
{
    cout << prompt << endl;

    char selection;
    cin >> selection;
    selection = toupper(selection);

    if(checkSelection(selection, m, n)) return selection;

    return '\0';
}

// Get username by id from database
string Interface::getUserName(int id)
{
    stmt[GetEmpName]->setInt(1, id);
    ResultSet *rs = stmt[GetEmpName]->executeQuery();
    rs->next();
    string result = rs->getString(1);
    stmt[GetEmpName]->closeResultSet(rs);
    return result;
}

string Interface::makePrompt(string prompt, Statement *stmt, bool expected)
{
    int tries = 1;
    string response = "";

    while (tries < 3)
    {
        cout << prompt;

        cin >> response;

        stmt->setString(1, response);

        ResultSet *rs = stmt->executeQuery();

        if(!rs->next() && expected)
        {
            errorMsg("ERROR: " + response + " not valid. Please try again\n\n");
        } else if (rs->next() && !expected) {
            errorMsg("ERROR: " + response + " already exists. Please try again\n\n");
        } else {
            return response;
        }

        tries++;
        stmt->closeResultSet(rs);
    }

    return response;
}

string Interface::getValue(string prompt)
{
    string result;
    cout << prompt << endl;
    getline(cin, result);
    cout << endl;

    return result;
}

bool Interface::madeChanges()
{
    return dataChanged;
}

// PROMPTS
// ============================================================================

// Prompt 1
string Interface::getEid()
{
    return makePrompt("Enter employee id: ", stmt[CheckEid], true);
}

// Prompt 2
string Interface::getPo()
{
    return makePrompt("Enter po number: ", stmt[CheckPo], true);
}

// Prompt 3
bool Interface::createInvoice()
{
    string po = makePrompt("Enter po number: ", stmt[CheckPo], false);
    string cno = makePrompt("Enter customer number: ", stmt[CheckCID], true);

    cin.ignore();

    string status = getValue("Enter status: ");

    string description = getValue("Enter description: ");

    try
    {
        stmt[CreateInvoice]->setString(1, po);
        stmt[CreateInvoice]->setString(2, cno);
        stmt[CreateInvoice]->setString(3, status);
        stmt[CreateInvoice]->setString(4, description);

        stmt[CreateInvoice]->executeUpdate();
    }
    catch (SQLException & e)
    {
        errorMsg(e.what());
        return false;
    }

    successMsg("Created new Invoice");
    return true;
}

// Prompt 4
string Interface::getCustomerNum()
{
    return makePrompt("Enter customer number: ", stmt[CheckCID], true);
}

// Prompt 5
bool Interface::createClient()
{
    string cid = makePrompt("Enter id: ", stmt[CheckCID], false);

    cin.ignore();

    string fname = getValue("Enter first name: ");
    string lname = getValue("Enter last name: ");
    string email = getValue("Enter email: ");
    string address = getValue("Enter address: ");
    string pnumber = getValue("Enter phone-number: ");

    try
    {
        stmt[CreateClient]->setString(1, cid);
        stmt[CreateClient]->setString(2, fname);
        stmt[CreateClient]->setString(3, lname);
        stmt[CreateClient]->setString(4, email);
        stmt[CreateClient]->setString(5, address);
        stmt[CreateClient]->setString(6, pnumber);

        stmt[CreateClient]->executeUpdate();

        dataChanged = true;
    }
    catch(SQLException & e) {
        errorMsg(e.what());
        return false;
    }

    successMsg("Client added!");
    return true;
}

// Prompt 6
bool Interface::addPart(string po)
{
    cin.ignore();
    string pid = getValue("Enter part id: ");

    int quantity;
    cout << "Enter quantity: " << endl;
    cin >> quantity;
    cout << endl;

    // Check if part has already been used
    stmt[CheckPartUsed]->setString(1, po);
    stmt[CheckPartUsed]->setString(2, pid);

    ResultSet *rs = stmt[CheckPartUsed]->executeQuery();

    try {
        // If the part record exists add the new quantity to the existing
        //  quantity
        if(rs->next())
        {
            quantity += rs->getInt(1);

            stmt[UpdatePart]->setInt(1, quantity);
            stmt[UpdatePart]->setString(2, pid);
            stmt[UpdatePart]->setString(3, po);

            stmt[UpdatePart]->executeUpdate();
        }
        else
        {
            stmt[AddPart]->setInt(1, quantity);
            stmt[AddPart]->setString(2, pid);
            stmt[AddPart]->setString(3, po);

            stmt[AddPart]->executeUpdate();
        }
            dataChanged = true;
    }
    catch(SQLException & e)
    {
        errorMsg(e.what());
        return false;
    }

    stmt[CheckPart]->closeResultSet(rs);

    successMsg("Part(s) added!");
    return true;
}

// Prompt 7
bool Interface::createPart()
{
    string pid = makePrompt("Enter part id: ", stmt[CheckPart], false);

    cin.ignore();

    string description = getValue("Enter part description: ");
    string unit = getValue("Enter part unit: ");
    string wholesale = getValue("Enter wholesale cost: ");
    string retail = getValue("Enter retail cost: ");

    try
    {
        stmt[CreatePart]->setString(1, pid);
        stmt[CreatePart]->setString(2, description);
        stmt[CreatePart]->setString(3, unit);
        stmt[CreatePart]->setString(4, wholesale);
        stmt[CreatePart]->setString(5, retail);

        stmt[CreatePart]->executeUpdate();

        dataChanged = true;
    }
    catch(SQLException & e)
    {
        errorMsg(e.what());
        return false;
    }

    successMsg("Created part!");
    return true;
}

// Prompt 8
string Interface::getRate()
{
    return getValue("Enter new rate: ");
}

// INTERFACES
// ============================================================================

// Display interface 0
void Interface::selectGroup()
{
    string prompt = "Select user group:\n\n";
    prompt += "Press [A] for admin, and [T] for technician, or [Q] to quit.";


    const int P = 3;
    const struct stateMap map[P] = {
        {'A', 1},
        {'T', 4},
        {'Q', -1}
    };

    if(createInterface(prompt, map, P) == 'A')
        makeAdmin();
}

// Display interface 1
void Interface::adminMain()
{
    string username = getUserName(eid);
    string prompt = "Welcome to the Irrigation Billing 5000 application\n\n";
    prompt += "You are logged in as: " + username + "<Admin>\n\n";
    prompt += "Press:\n";
    prompt += "[C] To see customer options\n";
    prompt += "[I] To see invoice options\n"; 
    prompt += "[E] To see employee options\n";
    prompt += "[P] To see parts options\n";
    prompt += "[Q] To quit\n";

    const int P = 5;
    const struct stateMap map[P] = {
        {'C', 6},
        {'I', 3},
        {'E', 2},
        {'P', 9},
        {'Q', -1}
    };

    createInterface(prompt, map, P);
}

// Display interface 2
void Interface::adminEmployeeOptions()
{
    string prompt = "Employee Options\n\nPress:\n";
    prompt += "[U] To update employee record\n";
    prompt += "[B] To go back to main menu\n";

    const int P = 2;
    const struct stateMap map[P] = {
        {'U', 11},
        {'B', 1}
    };

    if(createInterface(prompt, map, P) == 'U')
    {
        string empId = getEid();

        // If empId is empty, something has gone wrong,
        //  repeat this interface
        if (empId.empty()) state = 2;

        // Otherwise go to update employee interface
        else editEmployeeDetails(empId);
    }
}

// Display interface 3
void Interface::adminInvoiceOptions()
{
    string prompt = "Invoice options\n\n";
    prompt += "Press:\n";
    prompt += "[C] To create a new invoice\n";
    prompt += "[P] List all parts used in invoice\n";
    prompt += "[S] To view invoices for a specific customer\n";
    prompt += "[B] To go back to main menu\n";

    const int P = 4;
    const struct stateMap map[P] = {
        {'C', 3},
        {'P', 9},
        {'S', 8},
        {'B', mainMenu}
    };

    createInterface(prompt, map, P);

    if (state == 3) createInvoice();
    else if (state == 9) partsList(getPo());
    else if(state == 8) invoiceList( getCustomerNum());
}


// Display interface 4
void Interface::techMain()
{
    string username = getUserName(eid);
    string prompt = "Welcome to the Irrigation Billing 5000 application\n\n";
    prompt += "Logged in as: " + username + "\n\n";
    prompt += "Press:\n";
    prompt += "[C] To see customer options\n";
    prompt += "[I] To see invoice options\n";
    prompt += "[Q] To quit\n";

    const int P = 3;
    const struct stateMap map[P] = {
        {'C', 6},
        {'I', 5},
        {'Q', -1}
    };

    createInterface(prompt, map, P);
}

// Display interface 5
void Interface::techInvoice()
{
    string prompt = "Invoice Options:\n\n";
    prompt += "Press:\n";
    prompt += "[P] List all parts used for invoice\n";
    prompt += "[S] To view invoices for a specific customer\n";
    prompt += "[B] To go back to main menu\n";

    const int P = 3;
    const struct stateMap map[P] =
    {
        {'P', 10},
        {'S', 8},
        {'B', mainMenu}
    };

    createInterface(prompt, map, P);

    if (state == 10) partsList(getPo());
    else if (state == 8) invoiceList(getCustomerNum());
}

// Display interface 6
void Interface::customerOptions()
{
    string prompt = "Customer Options:\n\n";
    prompt += "Press:\n";
    prompt += "[A] To add a new customer\n";
    prompt += "[S] To list all invoices for a customer by id\n";
    prompt += "[L] To list all customers\n";
    prompt += "[B] To go back to main menu\n";

    const int P = 4;
    const struct stateMap map[P] =
    {
        {'A', 6},
        {'S', 8},
        {'L', 7},
        {'B', mainMenu}
    };

    createInterface(prompt, map, P);

    if (state == 6) createClient();
    else if (state == 8) invoiceList(getCustomerNum());
    else if (state == 7) customerList();
}


// Display interface 7
void Interface::customerList()
{
    string prompt = "Customer List:\n\n";
    prompt += "Press:\n";
    prompt += "[B] To return to customer options\n\n";
    prompt += "first_name\tlast_name\taddress\t\temail\tphone\n";
    prompt += "----------\t---------\t-------\t\t-----\t-----\n";

    cout << prompt << endl;

    ResultSet *rs = stmt[AllClient]->executeQuery();

    while(rs->next())
    {
        for (int i = 1; i < 6; i++)
            cout << rs->getString(i) << "\t";
        cout << endl;
    }
    cout << endl;

    const int P = 1;
    const struct stateMap map[P] =
    {
        {'B', 6}
    };

    char selection;
    cin >> selection;
    selection = toupper(selection);

    checkSelection(selection, map, P);
}

// Display interface 8
void Interface::invoiceList(string cno)
{
    string prompt = "Invoice list:\n\n";
    prompt += "Press:\n";
    prompt += "[B] To go back to invoice options\n\n";
    prompt += "po\tclient\tstatus\tdescription\t\t\tlabour_hours\t\n\n";
    prompt += "--\t------\t------\t-----------\t\t\t------------\n";

    const int P =1;
    const struct stateMap map[P] =
    {
        {'B', 5}
    };

    cout << prompt << endl;

    stmt[GetInvoice]->setString(1, cno);
    ResultSet *rs = stmt[GetInvoice]->executeQuery();

    while(rs->next())
        for (int i = 1; i <= 5; i++)
            cout << rs->getString(i) << "\t";

    cout << endl;

    stmt[GetInvoice]->closeResultSet(rs);

    char selection;
    cin >> selection;
    selection = toupper(selection);

    checkSelection(selection, map, P);
}

// Display interface 9
void Interface::partsOptions()
{
    string prompt = "Parts Options:\n\n";
    prompt += "Press:\n";
    prompt += "[A] To Add parts to an invoice\n";
    prompt += "[P] To add a new part\n";
    prompt += "[B] To go back to main menu\n";

    const int P = 3;
    const struct stateMap map[P] =
    {
        {'A', 9},
        {'P', 9},
        {'B', mainMenu}
    };

    char selection = createInterface(prompt, map, P);

    if(selection == 'A')
        addPart(getPo());
    else if (selection == 'P')
        createPart();
}

// Display interface 10
void Interface::partsList(string po)
{
    string prompt = "List of parts used on po: " + po + "\n\n";
    prompt += "Press:\n";
    prompt += "[B] To return to parts options\n\n";
    prompt += "part_id\tdescription\t\tunit\tused\tcost\ttotal\n";
    prompt += "-------\t-----------\t\t----\t----\t----\t-----\n\n";
    const int P = 1;
    const struct stateMap map[P] =
    {
        {'B', 9}
    };

    stmt[GetInvoiceParts]->setString(1, po);
    ResultSet *rs = stmt[GetInvoiceParts]->executeQuery();

    while(rs->next())
    {
        for (int i = 1; i <= 6; i++)
        {
            prompt += rs->getString(i) + "\t";

            if(i == 3) prompt += "\t";
        }

        prompt += "\n";
    }

    stmt[GetInvoiceParts]->closeResultSet(rs);

    createInterface(prompt, map, P);
}

// Display interface 11
void Interface::editEmployeeDetails(string eid)
{
    stmt[GetEmpDetails]->setString(1, eid);
    ResultSet *rs = stmt[GetEmpDetails]->executeQuery();
    rs->next();

    string prompt = "Edit employee details\n\n";
    prompt += "  Name: " + rs->getString(3) + " " + rs->getString(4) + "\n";
    prompt += "eid: " + rs->getString(1) + "\n";
    prompt += "Status: " + rs->getString(2) + "\n";
    prompt += "Rate: " + rs->getString(5) + "\n\n";
    prompt += "Press:\n";
    prompt += "[S] To edit status\n";
    prompt += "[R] To edit rate\n";
    prompt += "[B] To go back to employee options\n";

    const int P = 3;
    const struct stateMap map[P] =
    {
        {'S', 12},
        {'R', 11},
        {'B', 2},
    };

    stmt[GetEmpDetails]->closeResultSet(rs);

    createInterface(prompt, map, P);

    if (state == 12) editEmployeeStatus(eid);
    else if (state == 11)
    {
        stmt[UpdateEmpRate]->setString(1, getRate());
        stmt[UpdateEmpRate]->setString(2, eid);
    }
}

// Display interface 12
void Interface::editEmployeeStatus(string empId)
{
    stmt[GetEmpNameStatus]->setString(1, empId);
    ResultSet *rs = stmt[GetEmpNameStatus]->executeQuery();
    rs->next();

    string prompt = "Edit employee status:\n\n";
    prompt += "Current employee: " + rs->getString(1) + "\n";
    prompt += "Current status: " + rs->getString(2) + "\n\n";
    prompt += "Press:\n";
    prompt += "[A] To set active\n";
    prompt += "[I] To set Inactive\n";
    prompt += "[L] To set on leave\n";
    prompt += "[T] To set terminated\n";
    prompt += "[B] To go back to employee options\n";

    const int P = 5;
    const struct stateMap map[P] =
    {
        {'A', 112},
        {'I', 113},
        {'L', 114},
        {'T', 115},
        {'B', 2}
    };

    createInterface(prompt, map, P);

    string status = "";

    switch(state) {
        case 112:
            status = "active"; break;
        case 113:
            status = "inactive"; break;
        case 114:
            status = "leave"; break;
        case 115:
            status = "terminated"; break;
        default: break;
    }

    stmt[UpdateEmpStatus]->setString(1, status);
    stmt[UpdateEmpStatus]->setString(2, empId);
    stmt[UpdateEmpStatus]->executeUpdate();

    stmt[GetEmpNameStatus]->closeResultSet(rs);
    state = 2;
}
