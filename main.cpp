//----------------------------------------------------
// Author:     Rashi Ghosh
//----------------------------------------------------
#include <iostream>
#include <string>
#include "Database.h"
using namespace std;

//----------------------------------------------------
// Purpose: Find out what the user wants to do.
// Arguments: None.
// Returns: A number that indicates the users choice.
//----------------------------------------------------
int menuOptions()
{
int Choice;
   do 
   {
      cout << "\nEnter '1' to create a database\n"
           << "      '2' to open an existing database\n"
           << "      '3' to display a record\n"
           << "      '4' to update a record\n"
           << "      '5' to add a record\n"
           << "      '6' to delete a record\n"
           << "      '7' to create a report\n"
           << "      '8' to close the database\n"
           << "      '9' to quit the program\n"
           << "Selection: ";
      cin >> Choice;
   } while (Choice < 1 || Choice > 9);
   return Choice;
}

int main()
{
    cout << "Welcome to this database program! Please choose from the following: " << endl;
    Database db;
    //db.createDatabase();

    int Choice;

       Choice = menuOptions();
       cout << "You picked " << Choice << endl;
       while(Choice != 9)
       {
          switch (Choice)
          {
             case 1:   db.createDatabase(); break;
             case 2:   db.openDatabase(); break;
             case 3:   db.displayRecord(); break;
             case 4:   db.updateRecord(); break;
             case 5:   db.addRecord(); break;
             case 6:   db.deleteRecord(); break;
             case 7:   db.createReport(); break;
             case 8:   db.closeDatabase(); break;
          }
          // Ask for next choice
          Choice = menuOptions();
          cout << "You picked " << Choice << endl;
       }
       db.closeDatabase(); 
       return 0;
}
