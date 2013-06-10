/*
 *    James Mead Dagres
 *    jdagres@vt.edu
 *
 *    02-07-13
 *
 *    Billing Header File
 */

#ifndef BILLING_H
#define BILLING_H

#include <QMap>
#include <QDate>
#include <QString>
#include <qstringlist.h>
#include <QTextStream>
#include <QFile>
#include <QList>

using namespace std;

/*
 *   This class stores a list of Transaction entries.
 *   It can add new entries, delete existing ones, and list them.
 */

class Billing
{

private:
    // encapsulate the confirmation number
    int conNumb;

    //file which the constructor reads and destructor writes to
    static QFile sm_fileData;

    //directs all output streamed into here, to stdout
    static QTextStream sm_cout;

    //keeps a list of all entries read from the sm_fileData
    QStringList	m_listTransactionEntries;

    /*	This is a helper function which takes in a QString containing the
     *  name/date/hour as formatted within the saved file (sm_fileData) and
     *  formats it to the correct format.
     */
    QString formatLine(QString nameDateHour);

public:
    /*	The  construtor Reads the content from the sm_fileData
     *	and stores it into a QStringList
     */
    Billing();

    //	The deconstructor writes content from the QStringList back into the sm_fileData
    ~ Billing();

    // This function will display the total billing time for each user
    void userTransactions();

    /*	 This function adds entries to the Transaction
     *   private string list in chrnological order.
     */
    void addTransactionEntry(QString name, QString date, QString startHour, QString endHour);

    /*	This function takes in either a name/date/hour
     *   and removes the matching entry in the string list.
     */
    void deleteTrans(QString combNum); // Function that deletes the transaction

    /*  This function takes in a date from the command line.
     *  It should print out entries.
     */
    void printTransactionDate(QString date);

    /* the printTransactionName function takes in a employee name and
     * prints every transaction for the given name
     */
    void printTransactionName(QString name);

    // Prints the help menu
    void printTransactionHelp();

    // The formatError function prompts the user there was a format error
    void formatError();
};

#endif // BILLING_H
