/*
 *    James Mead Dagres
 *    jdagres@vt.edu
 *
 *    02-06-13
 *
 *    Main File
 */

using namespace std;

#include <QTextStream>
#include <QtCore>
#include <QCoreApplication>
#include "billing.h"

int main(int argc, char *argv[])
{
    Billing myTrans;

    // QTextStream Billing::sm_cout(stdout);
    QCoreApplication play(argc, argv);
    QStringList argumnts = play.arguments();
    QTextStream cout (stdout);

    enum inputs { // argc starts at 1
        UserAll = 2, // all transactions for a user
        Delete = 3,
        Print = 4, // four inputs needed
        Helper = 5,
        Add = 10 // ten inputs are needed for adding
    };

    switch(argc) // Switch statements filter through possible inputs
    {

    case UserAll:
    {
        if(argumnts[1] == "-total")
        {
            cout << "Total Transactions Initialized" << endl; // For debugging purposes
            myTrans.userTransactions();
        }
        else myTrans.formatError(); // Calls a function to prompt the user of the format error

        break;
    }

    case Delete:
    {
        if(argumnts[1] == "-del")
        {
            cout << "Delete Initialized" << endl;
            QString confNumber = argumnts[2]; //
            bool nameIsValid = true;
            int j=0;
            while (j < confNumber.size()) // Error checks the size of the name
            {
                if (!confNumber[j].isNumber()) // Ensures that every digit in the confirmation number is a number
                    nameIsValid = false;
                j++;
            }

            if(nameIsValid)
            {
                myTrans.deleteTrans(confNumber);
            }
            else myTrans.formatError();
        }

        break;
    }

    case Print:
    {
        if(argumnts[1] == "-list")
        {
            cout << "Print Initialized" << endl; // For debugging purposes

            // Can print by name or by date
            if(argumnts[2] == "-n") // Print by name
            {
                cout << "Printing by name" << endl;
                bool nameIsValid = true;
                QString nameString = argumnts[3];
                int j=0;
                while (j < nameString.size()) // Error checks the size of the name
                {
                    if (nameString[j].isNumber())
                        nameIsValid = false;
                    j++;
                }

                if( nameIsValid && (nameString.size() > 2) ) // Makes sure the name is valid
                {
                    myTrans.printTransactionName(nameString); // print the string
                }
                else myTrans.formatError();// Calls a function to prompt the user of the format error

            }
            else if(argumnts[2] == "-d") // Print by date
            {
                cout << "Printing by date" << endl;
                QString dateString = argumnts[3];
                QDate newDate = QDate::fromString(dateString, "MM/dd/yy");
                if( newDate.isValid())
                {
                    myTrans.printTransactionDate(dateString); // Calls the function to print the name
                }
                else myTrans.formatError();
            }
            else myTrans.formatError();
        }
        break;
    }

    case Helper:
    {
        if( argumnts[1] == "-h" &&  argumnts[2] == "-e" && argumnts[3] ==  "-l" && argumnts[4] == "-p" )
        {
           myTrans.printTransactionHelp();
        }
    }

    case Add:
    {
        if(argumnts[1] == "-add")
        {
            cout << "Add Initialized" << endl; // For debugging purposes

            // Ensures that the correct format has been followed
            if (argumnts[2] == "-n" && argumnts[4] == "-d" && argumnts[6] == "-s" && argumnts[8] == "-e")
            {
                bool nameIsValid = true;
                QString nameString = argumnts[3];
                QString dateString = argumnts[5];
                QString startTimeString = argumnts[7];
                QString endTimeString = argumnts[9];

                QDate newDate = QDate::fromString(dateString, "MM/dd/yy");
                QTime newStartTime = QTime::fromString(startTimeString, "hh:mm");
                QTime newEndTime = QTime::fromString(endTimeString, "hh:mm");
                int j = 0;
                while (j < nameString.size()) // Checks to ensure that the name has no numbers in it
                {
                    if (nameString[j].isNumber())
                        nameIsValid = false;
                    j++;
                }

                if ( newStartTime.isValid()
                     && newEndTime.isValid()
                     && newDate.isValid()
                     && nameIsValid
                     && (nameString.size() > 2) )
                {
                    cout << nameString << " " << dateString << " " << startTimeString << " "<< endTimeString << endl;
                    myTrans.addTransactionEntry(nameString, dateString, startTimeString, endTimeString);
                    // cout << "break add case" << endl; // For debugging purposes
                    break;
                }
                else {
                    myTrans.formatError();
                }
                break;
            }
            else myTrans.formatError();
            break;
        }
    }

    }

    return 0;
}
