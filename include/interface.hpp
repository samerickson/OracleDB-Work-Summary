#pragma once

#include <occi.h>
#include <iostream>

using namespace std;
using namespace oracle::occi;

struct stateMap{
    char key;
    int value;
};

class Interface
{
    private:
        bool checkSelection(char, const stateMap*, int);
        char createInterface(string, const stateMap*, int);
        void errorMsg(string);
        void successMsg(string);

        bool dataChanged;

        // Database query functions
        string getUserName(int);

        // The bool is true when the statement is supposed to have a result,
        //  and false when the statement does not produce any results
        string makePrompt(string, Statement*, bool);

        int state;
        int eid;

        // States that vary depending on admin or tech
        int mainMenu;
        int invoiceOpt;

        Connection *conn;
        Statement **stmt;

        // Used to get values from the user
        string getValue(string);

        // Prompts
        string getEid();
        bool createInvoice();
        string getPo();
        string getCustomerNum();
        bool createClient();
        bool addPart(string);
        bool createPart();
        string getRate();

    public:
        Interface(Connection*, Statement *[]);
        ~Interface();

        void makeAdmin();           // Allows user to be admin for prototyping
        int getState();             // Get the current state of the interface
        void setState(int);         // Set the current state
        void selectGroup();         // Choose admin or tech for prototyping
        bool madeChanges();         // Returns true if database was changed

        // Admin interfaces
        void adminMain();
        void adminEmployeeOptions();
        void adminInvoiceOptions();

        // Technician Interfaces
        void techMain();
        void techInvoice();

        // Main interfaces
        void customerOptions();
        void customerList();
        void invoiceList(string);
        void partsOptions();
        void partsList(string);
        void editEmployeeDetails(string);
        void editEmployeeStatus(string);
};

