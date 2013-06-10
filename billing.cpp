/*
 *    James Mead Dagres
 *    jdagres@vt.edu
 *
 *    02-06-13
 *
 *    Billing Class Implementation File
 */

#include "billing.h" // Includes all of the classes we need
#include <iostream>
#include <iomanip>

// Static variables
QFile Billing::sm_fileData("myBillings.dat");
QTextStream Billing::sm_cout(stdout);

Billing::Billing()
{
    sm_fileData.open(QIODevice::ReadOnly);

    QTextStream readFile(&sm_fileData);

    // read line by line and insert into a QStringList
    // from QFile documentation
    while (!readFile.atEnd())
    {
        m_listTransactionEntries << readFile.readLine();
    }

    sm_fileData.close();
}

Billing::~Billing()
{
    sm_fileData.open(QIODevice::WriteOnly);

    QTextStream writeFile(&sm_fileData);

    // Write every line in the QStringList to the file sm_fileData by
    // reading and popping the top of the list each time.
    while ( !m_listTransactionEntries.isEmpty() )
    {
        writeFile << m_listTransactionEntries.front() << endl;
        m_listTransactionEntries.pop_front();
    }

    conNumb = 999999; // Sets the initial confirmation number
    // that will increment for ever transaction

    sm_fileData.close();
}

void Billing::addTransactionEntry(QString name, QString date, QString startHour, QString endHour)
{

    // convert the QString date into a QDate object
    QTime tendTime = QTime::fromString(endHour, "hh:mm");
    QTime tstartTime = QTime::fromString(startHour, "hh:mm");
    QDate givenDate = QDate::fromString(date, "MM/dd/yy");

    name = name.toUpper(); // Ensures that the name is always uppercasemy

    // Start of Error Checking
    if (!givenDate.isValid())   // If the date entered is of valid year/month/date
    {
        sm_cout << "The date " << date << " is invalid, please try again." << endl;
        return;
    }
    // Ensures the start and end times are correct
    else if(!tendTime.isValid())
    {
        sm_cout << "The end time: " << endHour << " is invalid, please try again." << endl;
        return;
    }
    else if(!tstartTime.isValid())
    {
        sm_cout << "The start time " << startHour << " is invalid, please try again." << endl;
        return;
    }
    else if (tstartTime >= tendTime) // Checks to see if the start time comes after the end time
    {
        sm_cout << "Your start time has to come before your end time." << endl;
        return;
    }
    else if( (givenDate.addYears(100) > QDate::currentDate()) ) //Check to see if date entered is not in the future
    {
        sm_cout << "You can't enter a billing date in the future." << endl;
        return;
    }
    else if( (givenDate.addYears(100) >= QDate::currentDate()) && ( tendTime >= QTime::currentTime()) )
    {
        sm_cout << "You can't enter a billing date in the future." << endl;
        return;
    }
    else // All passed parameter entries are proper
    {
        int posInsert = m_listTransactionEntries.size();
        conNumb = 999999 - m_listTransactionEntries.size(); // Sets the initial confirmation number

        QString configString = QString::number(conNumb);

        for(int j = 0; j < m_listTransactionEntries.size(); j++)
        {
            QString component = m_listTransactionEntries[j];

            // Parses the name, dates and times from the string
            QString comp = component.split('"')[2];
            QString compDate = comp.split(" ")[1];
            QString compTimes = comp.split(" ")[2]; // Splits the time
            QString compStime = compTimes.split("-")[0]; // Splits the start time
            QString compEtime = compTimes.split("-")[1]; // Splits the end time

            // Convert string to QDate in correct format
            QTime begTime = QTime::fromString(compStime, "hh:mm");
            QTime finalTime = QTime::fromString(compEtime, "hh:mm");
            QDate prevDate = QDate::fromString(compDate, "MM/dd/yy");

            // Start of overlap error checking
            if ( (givenDate == prevDate) && (// Checks to see if the new billing time overlaps a previous transaction
                                             (   tstartTime >= begTime && tendTime <= finalTime) // Inside overlap
                                             || (tstartTime <= begTime && tendTime <= finalTime) // Outside overlap
                                             || (tstartTime <= begTime && tendTime >= begTime)
                                             || (tstartTime <= finalTime && tendTime >= finalTime) ) )
            {
                sm_cout << "The time period entered overlaps a previously recorded billing transaction." << endl;
                return;
            }
        } // End of the for loop

        QString newTransactionEntry = configString + " " + '"' + name + '"' + " " + date + " " + startHour + "-" + endHour;
        m_listTransactionEntries.insert(posInsert, newTransactionEntry);
        sm_cout << "The Billing entry for " << name << " has been added." << endl;

        conNumb--;
    }
}

void Billing::deleteTrans(QString conNumb)
{
    bool conNumFound = false;
    for(int j=0; j< m_listTransactionEntries.size(); j++)
    {
        QString component = m_listTransactionEntries[j];
        QString comp = component.split(" ")[0];
        int compNum = comp.toInt();
        int number = conNumb.toInt();
        if(number == compNum) // If the comp number is the current line being traversed then delete
        {
            sm_cout << "The Billing entry for transaction: " << comp << " has been deleted." << endl;
            m_listTransactionEntries.removeAt(j); // Calls a remove at function to get rid of the transaction
            conNumFound = true;
        }
    }

    if (!conNumFound)
    {
        sm_cout << "Confirmation number doesn't exist: " << conNumb << endl;
    }
}

void Billing::printTransactionDate(QString dateString)
{
    bool dateFound = false;
    sm_cout << "PrintTransactionDate Initialized" << endl;
    for(int j=0; j< m_listTransactionEntries.size(); j++)
    {
        QString component = m_listTransactionEntries[j];
        QString compDate = component.split('"')[2]; // Splits the date
        compDate = compDate.trimmed();
        QString myDate = compDate.split(" ")[0];
        sm_cout << "date is: " << compDate << endl;

        if(myDate == dateString) // If the comp number is the current line being traversed then delete
        {
            sm_cout << m_listTransactionEntries[j] << endl;
            dateFound = true;
        }
    }

    if(!dateFound)
    {
        sm_cout << "Date Not Found" << endl;
    }
}

void Billing::printTransactionName(QString nameString)
{
    bool nameFound = false;
    sm_cout << "PrintTransaction Name Initialized" << endl;
    for(int j=0; j< m_listTransactionEntries.size(); j++)
    {
        QString component = m_listTransactionEntries[j];
        QString compName = component.split('"')[1]; // Splits the name
        compName = compName.trimmed();

        // If the comp number is the current line being traversed then mark is as found
        if(compName.toUpper() == nameString.toUpper())
        {
            sm_cout << m_listTransactionEntries[j] << endl;
            nameFound = true;
        }
    }

    if(!nameFound)
    {
        sm_cout << "Name Not Found" << endl;
    }
}

void Billing::printTransactionHelp()
{
    cout << "Help Initialized" << endl << endl
         << "The date should be in the \"mm/dd/yy\"' format " << endl
         << "The times should be in the \"hh:mm\" format" << endl
         << "If you're entering more than one name seperate the names by comma's ',' " << endl
         << "The confimation number can only consist of numbers " << endl
         << "Every entry should be written inside \"quotation marks\" " << endl
         << "The following outputs are accepted: " << endl
         << "-add -n \"name\" -d \"date\" -s \"time in\" -e \"time out\" " << endl
         << "-list -d \"date\" " << endl
         << "-list -n \"name\" " << endl
         << "-del \"confirmation number\" " << endl
         << "-total" << endl
         << "-h -h -h -h (currently running help application) " << endl;
}

void Billing::formatError() // Prompts the user they had a format error and alerts them of the help class
{
    sm_cout << "Incorrect format, for help type four -h's: \n '-h -h -h -h'" << endl;
    return;
}

QString Billing::formatLine(QString nameDateHour)
{
    QStringList compent = nameDateHour.split(":");
    QString name = compent[0]; // Extract name
    QString date = compent[1];
    QString hour = compent[2];

    QString output;
    QTextStream os(&output);

    os << "The Transaction entry is for " << name << " at date " << date
       << " for hour " << hour;

    return output;
}

void Billing::userTransactions()
{
    QStringList m_backUpList = m_listTransactionEntries; // Creates a backup list
    for(int i = 0; i < m_backUpList.size(); i++) // Traverse through back up list
    {
        QString component1 = m_backUpList[i];

        // Parses the name, dates and times from the string
        QString comp1 = component1.split('"')[2];
        QString compTimes1 = comp1.split(" ")[2]; // Splits the time
        QString compStime1 = compTimes1.split("-")[0]; // Splits the start time
        QString compEtime1 = compTimes1.split("-")[1]; // Splits the end time
        QString name1 = component1.split('"')[1]; // Splits the name

        // Convert string to QDate in correct format
        QTime begTime = QTime::fromString(compStime1, "hh:mm");
        QTime finalTime = QTime::fromString(compEtime1, "hh:mm");

        double totalTime = begTime.secsTo(finalTime); // Resets during every loop

        for(int j = i+1; j < m_backUpList.size();) // Traverse through entire list
        {
            QString component2 = m_backUpList[j];
            QString comp2 = component2.split('"')[2];
            QString compTimes2 = comp2.split(" ")[2]; // Splits the time
            QString compStime2 = compTimes2.split("-")[0]; // Splits the start time
            QString compEtime2 = compTimes2.split("-")[1]; // Splits the end time
            QString name2 = component2.split('"')[1]; // Splits the name

            QTime begTime = QTime::fromString(compStime2, "hh:mm");
            QTime finalTime = QTime::fromString(compEtime2, "hh:mm");

            if (name1 == name2)
            {
                sm_cout << "names match" << endl;
                totalTime = totalTime + begTime.secsTo(finalTime);
                m_backUpList.removeAt(j);
            }
            else  // If the names aren't the same then increment
            {
                j++;
            }
        }
        totalTime /= 3600;

        cout.precision(2); // Ensure that two significant figures are displayed
        cout << endl << name1.toStdString() // Converts the string to standard in order to cout
             << " has a Total Billing Time of: " << fixed << totalTime << " hours." << endl;
    }
}
