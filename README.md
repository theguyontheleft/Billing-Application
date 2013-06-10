Billing-Application
===================

James Dagres

DESCRIPTION:
=============

This software is an application that manages and stores billings for employees. It runs with a command line interface defined in the instructions below. 

FEATURES:
=============
* Can store any number of employee’s hours
* Can list total hours for all employees
* Can list hours for any job number
* Can list hours for any day or time

NOTES:
=============
A testing file has also been uploaded

ADDITIONAL PROGRAMS NEEDED:
=======================================
QT
* The program can be made and executed from the terminal as well 
as from QT.
For references on how to install Qt on various OS, please go to
http://qt-project.org/doc/qt-4.8/installation.html
* To install QT on a Linux OS the following terminal instruction 
will download everything needed.
Be warned it is a massive download (174 MB):

        $ sudo apt-get install qt-sdk

INSTRUCTIONS:
=======================================
* From the terminal once in the project directory run the following commands to make and build the project:

        $ qmake -project
		$ qmake
		$ make

* There are some test files to try the project in the TestFiles 
directory.
* You can open any of those file with the open button pinned to 
the quick access toolbar 
* Once the file has been loaded the GUI's interface should be 
pretty straight forward.

* To add a billing the command line argument format is:

        $ ./mybillings –add  –n namespec  –d datespec –s  timespec  –e  timespec

* To delete a billing entry the command line argument format is:

        $ ./mybillings –del confnumspec

* To display a list all of the billings on a certain day the command line argument format is:

        $ ./mybillings –list -d datespec

* To display a list all of the billings for a particular name the command line argument format is:

        $ ./mybillings –list -n namespec

* To display a list the total time accumulated by each employee in the database the command line argument format is:

        $ ./mybillings –total
        
* To display the help menu the command line argument format is:

        $ ./mybillings –h -e -l -p       
        
Where
* “myBillings” is the name of the program.
* “namespec”  is a string containing the name of the employee
* “datespec” is the date of which the employee worked in following format: "mm/dd/yy"
* “timespec” is the time in the format “hh:mm”. “-s” comes before the time clocked in and “-e” comes before the time clocked out
* “confnumspec” is the confirmation number of the entry which is in “quotes”.
* “total” prints out the total time accumulated by each employee in the database
* Every entry should be written inside "quotation marks"
