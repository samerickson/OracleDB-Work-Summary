#include <iostream>
#include <occi.h>
#include <termios.h>
#include <unistd.h>

#include <cstdlib>

#include "interface.hpp"
#include "statementKeys.hpp"

using namespace std;
using namespace oracle::occi;

// read database password from user input
// without showing the password on the screen
string readPassword()
{
    struct termios settings;
    tcgetattr( STDIN_FILENO, &settings );
    settings.c_lflag =  (settings.c_lflag & ~(ECHO));
    tcsetattr( STDIN_FILENO, TCSANOW, &settings );

    string password = "";
    getline(cin, password);

    settings.c_lflag = (settings.c_lflag |   ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &settings );
    return password;
}

// Sanitize strings for SQL queries
string sanitize(string s)
{
    string ns = "";
    for(int i = 0; i < s.length(); i++) {
        if (s[i] == '\'' || s[i] == '\\' || s[i] == ';')
            ns = ns + '\\';
        ns = ns + s[i];
    }
    return ns;
}

void initialize(Connection *conn, Statement *stmt[])
{
    stmt[GetEmpName] = conn->createStatement
        ("select first_name || ' ' || last_name from employee where eid = :1");

    stmt[GetEmpDetails] = conn->createStatement
        ("select * from employee where eid = :1");

    stmt[GetEmpNameStatus] = conn->createStatement
        ("select first_name || ' ' || last_name, status from employee where eid = :1");

    stmt[UpdateEmpStatus] = conn->createStatement
        ("update employee set status = :1 where eid = :2");

    stmt[UpdateEmpRate] = conn->createStatement
        ("update employee set rate = :1 where eid = :2");

    stmt[CheckEid] = conn->createStatement
        ("select eid from employee where eid = :1");

    stmt[CheckPo] = conn->createStatement
        ("select po from invoices where po = :1");

    stmt[CreateInvoice] = conn->createStatement
        ("insert into invoices VALUES (:1, :2, :3, sysdate, null, null, :4)");

    stmt[CheckCID] = conn->createStatement
        ("select cid from clients where cid = :1");

    stmt[CreateClient] = conn->createStatement
        ("insert into clients VALUES (:1, :2, :3, :4, :5, :6)");

    stmt[AddPart] = conn->createStatement
        ("insert into partsused values (:1, :2, :3)");

    stmt[CheckPartUsed] = conn->createStatement
        ("select quantity from partsused where pid = :1 and po = :2");

    stmt[UpdatePart] = conn->createStatement
        ("update partsused set quantity = :1 where pid = :2 and po = :3");

    stmt[CheckPart] = conn->createStatement
        ("select pid from parts where pid = :1");

    stmt[CreatePart] = conn->createStatement
        ("insert into parts values (:1, :2, :3, :4, :5)");

    string sql = "select po, client, status, description, hours ";
    sql += "from invoices natural join";
    sql += "(select job, sum(extract(hour from ";
    sql += "((clockout - endlunch) + (startlunch -clockin)))) ";
    sql += "as hours from clockinout where job = :1) join clients ";
    sql += "on client = cid where po = :1";
    stmt[GetInvoice] = conn->createStatement(sql);

    stmt[AllClient] = conn->createStatement
        ("select first_name, last_name, address, email, phone_number from clients");

    sql = "select pid, description, unit, quantity as used, retail as cost, ";
    sql += "(quantity * retail) as total from partsused natural join parts ";
    sql += "where po = :1";
    stmt[GetInvoiceParts] = conn->createStatement
        (sql);
}

void cleanUp(Connection *conn, Statement *stmt[])
{
    for(int i = 0; i < N; i++)
        conn->terminateStatement(stmt[i]);
}

int main ()
{
    const string connectString = "sunfire.csci.viu.ca";
    string userName = getenv("ORACLE_USER");
    string password = getenv("ORACLE_PASS");

    if(userName.empty())
    {
        cout << "Please enter your oracle username:" << endl;
        getline(cin, userName);
    }

    if(password.empty())
    {
        cout << "Please enter your oracle password:" << endl;
        password = readPassword();
    }

    try
    {
        Environment *env = Environment::createEnvironment();
        Connection *conn = env->createConnection
            (userName, password, connectString);
        Statement *stmt[N];

        initialize(conn, stmt);

        Interface ui(conn, stmt);
        int state = ui.getState();

        while(state != -1)
        {
            switch(state) {
                case 0:
                    ui.selectGroup();
                    break;
                case 1:
                    ui.adminMain();
                    break;
                case 2:
                    ui.adminEmployeeOptions();
                    break;
                case 3:
                    ui.adminInvoiceOptions();
                    break;
                case 4:
                    ui.techMain();
                    break;
                case 5:
                    ui.techInvoice();
                    break;
                case 6:
                    ui.customerOptions();
                    break;
                case 9:
                    ui.partsOptions();
                    break;
                default:
                    // If the state does not exist, quit
                    ui.setState(-1);
            }
            state = ui.getState();
        }

        if(ui.madeChanges())
        {
            cout << "Would you like to save changes (yes/no): ";
            cin.ignore();
            string res;
            getline(cin, res);
            if(res == "yes")
            {
                conn->commit();
                cout << "\033[1;32" << '\n' << "Saved Changes" << '\n' << "\033[0m\n";
            }
            else
            {
                conn->rollback();
                cout << "\033[1;31" << '\n' << "Reverted Changes" << '\n' << "\033[0m\n";
            }
        }

        cleanUp(conn, stmt);
        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);
    } catch (SQLException & e)
    {
        cerr << e.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
