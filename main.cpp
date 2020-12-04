//----------------------------------------------------
// Author:     Susan Gauch
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
    
//    string Rank = "RANK";
//    string Name = "NAME";
//    string City = "CITY";
//    string State = "STATE";
//    int Zip = -1;
//    int Employees = -1;
//    int Location = -1;
//
//    Name = "FACEBOOK";
//    Rank = "RANK";
//    City = "CITY";
//    State = "STATE";
//    Zip = -1;
//    Employees = -1;
//    Location = -1;
//    if (db.binarySearch(Name, Rank, City, State, Zip, Employees, Location))
//    {
//       cout << "binarySearch(" << Name << "): " 
//               << Name << ", " << Rank << ", " << City << ", " << 
//               State << ", " << Zip <<  ", " << Employees << "\n\n";
//    }
//    else
//       cout << Name << " not found.\n\n";
//    
//    Name = "GENERAL ELECTRIC";
//    Rank = "RANK";
//    City = "CITY";
//    State = "STATE";
//    Zip = -1;
//    Employees = -1;
//    Location = -1;
//    if (db.binarySearch(Name, Rank, City, State, Zip, Employees, Location))
//    {
//       cout << "binarySearch(" << Name << "): " 
//               << Name << ", " << Rank << ", " << City << ", " << 
//               State << ", " << Zip <<  ", " << Employees << "\n\n";
//    }
//    else
//       cout << Name << " not found.\n\n";
//    
//    
//    Name = "WESTERN & SOUTHERN FINANCIAL GROUP" ;
//    Rank = "RANK";
//    City = "CITY";
//    State = "STATE";
//    Zip = -1;
//    Employees = -1;
//    Location = -1;
//    if (db.binarySearch(Name, Rank, City, State, Zip, Employees, Location))
//    {
//       cout << "binarySearch(" << Name << "): " 
//               << Name << ", " << Rank << ", " << City << ", " << 
//               State << ", " << Zip <<  ", " << Employees << "\n\n";
//    }
//    else
//       cout << Name << " not found.\n\n";
//
//    Name = "D.R. HORTON" ;
//    Rank = "RANK";
//    City = "CITY";
//    State = "STATE";
//    Zip = -1;
//    Employees = -1;
//    Location = -1;
//    if (db.binarySearch(Name, Rank, City, State, Zip, Employees, Location))
//    {
//       cout << "binarySearch(" << Name << "): " 
//               << Name << ", " << Rank << ", " << City << ", " << 
//               State << ", " << Zip <<  ", " << Employees << "\n\n";
//    }
//    else
//       cout << Name << " not found.\n\n";
//    
    
//    Name = "3M";
//    Rank = "2435";
//    City = "CITY";
//    State = "STATE";
//    Zip = -1;
//    Employees = -1;
//    Location = -1;
//    db.updateRecord(Name, Rank, City, State, Zip, Employees);
//    
//    Name = "APPLE";
//    Rank = "2435";
//    City = "CITY";
//    State = "STATE";
//    Zip = -1;
//    Employees = -1;
//    Location = -1;
//    db.updateRecord(Name, Rank, City, State, Zip, Employees);
    
//    
//    db.createReport();
//    
//    
    
//    db.deleteRecord("3M");
//    db.deleteRecord("WHOLE FOODS MARKET");
//    
//    
//    Name = "SKRT";
//    Rank = "98";
//    City = "fayville";
//    State = "ar";
//    Zip = 72701;
//    Employees = 1;
//    db.addRecord(Name, Rank, City, State, Zip, Employees);
//    
//    
//    Name = "BEEP";
//    Rank = "0";
//    City = "blip";
//    State = "boop";
//    Zip = 2424;
//    Employees = 242;
//    db.addRecord(Name, Rank, City, State, Zip, Employees);
//    
//    
//    
//    Name = "TALALASHSHS";
//    Rank = "2342";
//    City = "sfrgvs";
//    State = "ar";
//    Zip = 72701;
//    Employees = 1;
//    db.addRecord(Name, Rank, City, State, Zip, Employees);
    

//    Name = "RASHSISISIS";
//    Rank = "0";
//    City = "blip";
//    State = "boop";
//    Zip = 2424;
//    Employees = 242;
//    db.addRecord(Name, Rank, City, State, Zip, Employees);
    
    
//    
//    Name = "beep" ;
//    Rank = "RANK";
//    City = "CITY";
//    State = "STATE";
//    Zip = -1;
//    Employees = -1;
//    Location = -1;
//    if (db.binarySearch(Name, Rank, City, State, Zip, Employees, Location))
//    {
//       cout << "binarySearch(" << Name << "): " 
//               << Name << ", " << Rank << ", " << City << ", " << 
//               State << ", " << Zip <<  ", " << Employees << "\n\n";
//    }
//    else
//       cout << Name << " not found.\n\n";
    
    
//DB Universities;
//int Choice;
//
//   Choice = menuOptions();
//   cout << "You picked " << Choice << endl;
//   while(Choice != 7)
//   {
//      switch (Choice)
//      {
//         case 1:   Universities.Open(); break;
//         case 2:   Universities.DisplayRecord(); break;
//         case 3:   Universities.UpdateRecord(); break;
//         case 4:   Universities.CreateReport(); break;
//         case 5:   Universities.AddRecord(); break;
//         case 6:   Universities.DeleteRecord(); break;
//      }
//      // Ask for next choice
//      Choice = getChoice();
//      cout << "You picked " << Choice << endl;
//   }
//   Universities.Quit(); 
//   return 0;
}
