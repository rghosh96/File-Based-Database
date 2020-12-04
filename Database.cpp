/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Database.cpp
 * Author: rghosh
 * 
 * Created on February 1, 2020, 10:17 AM
 */

#include "Database.h"
#include "Records.h"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

Database::Database() {
    RECORD_SIZE = 101;
    NUM_RECORDS = 0;
    overflowCount = 0;
}

Database::Database(const Database& orig) {
    RECORD_SIZE = 0;
    NUM_RECORDS = 0;
    overflowCount = 0;
}

Database::~Database() {
}

void Database::createDatabase() {

    if (dataFile.is_open()) {
        cout << "Another database is already open!!! Must close current database before proceeding ):" << endl;
    }
    else {
    cout << "Please enter the filename of your csv file (without csv extension):\n";
    cin >> CSV_FILE;

    DATAFILE = CSV_FILE;
    DATAFILE.append(".data");

    OVERFLOW = CSV_FILE;
    OVERFLOW.append(".overflow");

    CONFIG = CSV_FILE;
    CONFIG.append(".config");

    CSV_FILE.append(".csv");
    ifstream data(CSV_FILE); //csv file
    
    system("rm FORTUNE_500_HQ.overflow");
    ofstream config, overflow;
    config.open(CONFIG.c_str(), ios::out | ios::in | ios::trunc);
    overflow.open(OVERFLOW.c_str(), ios::app | ios::in);
    dataFile.open(DATAFILE.c_str(), ios::out | ios::in | ios::trunc);

    if (dataFile.is_open()) {
        cout << "successfully opened db!" << endl;
        NUM_RECORDS = 0;
    }
    else {
        cout << "error opening db ):" << endl;
    }
    
    string name, rank, city, state, zip, employees;

    while(getline(data, name, ',')) {
        getline(data, rank, ',');
        getline(data, city, ',');  
        getline(data, state, ',');
        getline(data, zip, ',');
        getline(data, employees);

        // to keep from skipping spaces in the name
        replace(name.begin(), name.end(), ' ', '_');
        replace(city.begin(), city.end(), ' ', '_');
        replace(state.begin(), state.end(), ' ', '_');

        dataFile << setw(40) << left << name;
        dataFile << setw(10) << left << rank;
        dataFile << setw(20) << left << city;
        dataFile << setw(10) << left << state;
        dataFile << setw(10) << left << zip;
        dataFile << setw(10) << left << employees << endl;
        
        NUM_RECORDS++;

    }
    
    RECORD_SIZE = 40+10+20+10+10+10+1;
    
    cout << "Num recs: " << NUM_RECORDS << " & rec size: " << RECORD_SIZE;
    config << NUM_RECORDS << endl;
    config << RECORD_SIZE << endl;
    config << 0 << endl;
    
    config.close();
    overflow.close();
    
    data.close();   //close the file when done

    
    cout << "Successfully created database in " << DATAFILE << "!!!" << endl;

    //dataFile.close();
    }
    
    
}

void Database::openDatabase() {
    if (dataFile.is_open()) {
        cout << "Another database is already open!! Please close before proceeding." << endl;
    }
    else {
        cout << "Please enter name of database you would like to open: " << endl;
        cin >> DATAFILE;
        OVERFLOW = DATAFILE;
        OVERFLOW.append(".overflow");

        CONFIG = DATAFILE;
        CONFIG.append(".config");

        DATAFILE = DATAFILE.append(".data");

        dataFile.open(DATAFILE.c_str(), ios::out | ios::in);
        if (dataFile.is_open()) {
            cout << "Successfully opened the database, " << DATAFILE << "!!!" << endl;
            fstream config;
            cout << CONFIG << endl;
            config.open(CONFIG.c_str());
            config >> NUM_RECORDS;
            config >> RECORD_SIZE;
            config >> overflowCount;
            config.close();
            cout << "num recs: " << NUM_RECORDS << "; rec size: " << RECORD_SIZE << "; overflow count: " << overflowCount << endl;

        }
        else {
            cout << "Sorry, there was an error opening the database requested ):" << endl;
        }
    }
    //dataFile.open(FILENAME.c_str(), ios::in | ios::out);
}

Records Database::getRecord(fstream &Din, const int RecordNum)
    {
        Records target;
       if ((RecordNum > 0) && (RecordNum <= NUM_RECORDS))
       {
          // start at beginning, multiply record length x which record to get there
          Din.seekg(RecordNum * RECORD_SIZE, ios::beg);
          target.readRecord(Din);
       }
       else
          cout << "Record requested out of range.\n";
        return target;
    }

void Database::displayRecord() {
    if (dataFile.is_open()) {
        string Name;
        Records rec;
        cout << "Please enter the name of the record you would like to display! ";
        cin.ignore();
        getline(cin, Name);
        replace(Name.begin(), Name.end(), ' ', '_');

        fstream overflow(OVERFLOW.c_str());
        Records targetRec;
        bool inO = false;
        for (int i = 1; i < overflowCount+1; i++){
            overflow.seekg(i * RECORD_SIZE, ios::beg);
            targetRec.readRecord(overflow);
            if (targetRec.getName() == Name) {
                cout << "Found requested record! ";
                targetRec.printRecord();
                inO = true;
            }
        }

        if (!inO) {
            int RecordNum = binarySearch(Name, dataFile, NUM_RECORDS-1);
            if (RecordNum) {
                dataFile.seekg(RecordNum * RECORD_SIZE, ios::beg);
                targetRec.readRecord(dataFile);
                cout << "Found requested record! ";
                targetRec.printRecord();
            }
            else {
                cout << "Sorry, the record you requested could not be found ): " << endl;
            }
        }
        overflow.close();
    }
    else {
        cout << "Error: no database is currently open ):" << endl;
    }
}

int Database::binarySearch (const string nameIn, fstream &file, int high)
{
    Records targetRec;
    int Low = 0;
    int High = high;
    int Middle;
    string n;

    // txt file uses '_' instead of spaces so convert;
    string Name = nameIn;
    replace(Name.begin(), Name.end(), ' ', '_');

    bool Found = false;
    
    while (!Found && (High >= Low))
    {
        Middle = (Low + High) / 2;
        targetRec = getRecord(file, Middle+1);

        if (targetRec.getName() == Name) {
            Found = true;
        }
        else if (targetRec.getName() < Name)
            Low = Middle + 1;
        else 
            High = Middle -1;
    }
    
    if (Found) {
        return Middle +1;
    }
    else {
        return 0;
    }
}

void Database::updateRecord() {
    if (dataFile.is_open()) {

        string Name, input;
        int field;
        cout << "Please enter the name of the record you would like to update! ";
        cin.ignore();
        getline(cin, Name);

        replace(Name.begin(), Name.end(), ' ', '_');
        
        fstream overflow(OVERFLOW.c_str(), ios::in | ios::out);
        Records targetRec;
        bool inO = false;
        for (int i = 1; i < overflowCount+1; i++){
            overflow.seekg(i * RECORD_SIZE, ios::beg);
            targetRec.readRecord(overflow);
            if (targetRec.getName() == Name) {
                targetRec.printRecord();
                targetRec.writeRecord(overflow, Name);
                cout << "Successfully updated record: ";
                inO = true;
            }
        }

        if (!inO) {
            int RecordNum = binarySearch(Name, dataFile, NUM_RECORDS-1);
            if (RecordNum != 0) {
                dataFile.seekg(RecordNum * RECORD_SIZE, ios::beg);
                targetRec.printRecord();
                targetRec.writeRecord(dataFile, Name);
                cout << "Successfully updated record: ";
            }
            else {
                cout << "Sorry, the record you requested could not be found ): " << endl;
            }
        }
        overflow.close();

    }
    else {
        cout << "Error: no database is currently open ):" << endl;
    }
}

void Database::createReport() {
    if (dataFile.is_open()) {
        cout << "Creating a report of the first 10 records..." << endl;

        ofstream report;
        report.open("report.txt");
        
        
        int Zip, Employees;
        string Name, Rank, City, State;
        
        report << "Database Report" << endl;
        
        report << endl;
        for (int i = 0; i < 100; i++) {
            report << "*";
        }
        report << endl;
        report << endl;
        
        report << setw(40) << left << "NAME";
        report << setw(10) << left << "RANK";
        report << setw(20) << left << "CITY";
        report << setw(10) << left << "STATE";
        report << setw(10) << left << "ZIP";
        report << setw(10) << left << "EMPLOYEES" << endl;
        
        report << endl;
        Records rec;
        
        for (int i = 1; i < 11; i++) {
            rec = getRecord(dataFile, i);
        
            report << setw(40) << left << rec.getName();
            report << setw(10) << left << rec.getRank();
            report << setw(20) << left << rec.getCity();
            report << setw(10) << left << rec.getState();
            report << setw(10) << left << rec.getZip();
            report << setw(10) << left << rec.getEmployees() << endl;
        }
        
        report << endl;
        for (int i = 0; i < 100; i++) {
            report << "*";
        }
        report << endl;
        report << endl;
        
        report << "Thank u for using my database!!! :) <3";
        cout << "Report with top 10 records created in report.txt!" << endl;
        report.close();
    }
    else {
        cout << "Error: no database is currently open ):" << endl;
    }
    
}

void Database::addRecord() {
    if (dataFile.is_open()) {

        string Name, Rank, City, State, Zip, Employees;
        
        cout << "Please enter the name of the record you wish to add: ";
        cin.ignore();
        getline(cin, Name);
        if (Name.length() > 24) {
            Name = Name.substr(0,40);
        }
        replace(Name.begin(), Name.end(), ' ', '_');

        cout << "And the rank? ";
        cin >> Rank;
        if (Rank.length() > 10) {
            Rank = Rank.substr(0,10);
        }

        cout << "The city? ";
        cin.ignore();
        getline(cin, City);
        if (City.length() > 20) {
            City = City.substr(0,20);
        }
        replace(City.begin(), City.end(), ' ', '_');

        cout << "Please enter the state: ";
        getline(cin, State);
        if (State.length() > 10) {
            State = State.substr(0,10);
        }
        replace(State.begin(), State.end(), ' ', '_');

        cout << "...And the zip? ";
        cin >> Zip;
        if (Zip.length() > 10) {
            Zip = Zip.substr(0,10);
        }

        cout << "Finally, how many employees? ";
        cin >> Employees;
        if (Employees.length() > 10) {
            Employees = Employees.substr(0,10);
        }

        fstream overflow;
        overflow.open(OVERFLOW.c_str(), ios::in | ios::app);

        if (overflowCount == 0) {
            overflow << setw(40) << left << "NAME";
            overflow << setw(10) << left << "RANK";
            overflow << setw(20) << left << "CITY";
            overflow << setw(10) << left << "STATE";
            overflow << setw(10) << left << "ZIP";
            overflow << setw(10) << left << "EMPLOYEES" << endl;
        }

        replace(Name.begin(), Name.end(), ' ', '_');
        replace(City.begin(), City.end(), ' ', '_');
        replace(State.begin(), State.end(), ' ', '_');

        overflow << setw(40) << left << Name;
        overflow << setw(10) << left << Rank;
        overflow << setw(20) << left << City;
        overflow << setw(10) << left << State;
        overflow << setw(10) << left << Zip;
        overflow << setw(10) << left << Employees << endl;
        
        overflowCount++;
        if (overflowCount == 5) {
            int l = 0;
            for (int i = 1; i < overflowCount+1; i++) {
                overflow.seekg(i * RECORD_SIZE, ios::beg);
                memory[l].setRecord(overflow);
                l++;
            }

            sortRecords();
            rewriteDB();
            overflow.close();
            system("rm FORTUNE_500_HQ.overflow");
            overflow.open(OVERFLOW.c_str(), ios::in | ios::app);
        }
        overflow.close();
    }
    else {
        cout << "Error: no database is currently open ):" << endl;
    }
}


void Database::sortRecords() {
    Records temp;
    for (int i = 0; i < overflowCount; i++) {
        for (int j = i+1; j < overflowCount; j++) {
            if (memory[j].getName() < memory[i].getName()) {
                temp = memory[i];
                memory[i] = memory[j];
                memory[j] = temp;
            }
        }
    }
}


void Database::rewriteDB() {
    fstream newDB, newConfig;
    newDB.open("newDB.data", ios::out);
    newConfig.open("newConfig.config", ios::out);
    Records rec;
    int n = 0;
    int newNumRecs = NUM_RECORDS;

    
    newDB << setw(40) << left << "NAME";
    newDB << setw(10) << left << "RANK";
    newDB << setw(20) << left << "CITY";
    newDB << setw(10) << left << "STATE";
    newDB << setw(10) << left << "ZIP";
    newDB << setw(10) << left << "EMPLOYEES" << endl;
    
    //rec.readRecord(dataFile);
    for (int i = 1; i < NUM_RECORDS; i++) {
        dataFile.seekg(i * RECORD_SIZE, ios::beg);
        rec.readRecord(dataFile);
        if (rec.getName() == "BLANK") {
            newNumRecs--;
            continue;
        }
        if (n != 5 && memory[n].getName() == "BLANK") {
            n++;
        }
        if ((n < 5) && (memory[n].getName() < rec.getName())) {    //ex, if cat < beep < blip
                memory[n].writeNewRec(newDB);
                newNumRecs++;
                i--;
                n++;
        }
        else {
            rec.writeNewRec(newDB);
        } 
    }
    if (n < 5) {
        for (int i = n; i < 5; i++) {
            memory[i].writeNewRec(newDB);
        }
    }    
    
    cout << "Now db has: " << newNumRecs << " records" << endl;
    NUM_RECORDS = newNumRecs;
    newConfig << newNumRecs << endl;
    newConfig << RECORD_SIZE << endl;
    overflowCount = 0;
    newConfig << overflowCount << endl;
    newConfig.close();
    newDB.close();
    
    dataFile.close();
    system ("mv newDB.data FORTUNE_500_HQ.data");
    system ("mv newConfig.config FORTUNE_500_HQ.config");
    dataFile.open("FORTUNE_500_HQ.data", ios::in | ios::out);
}

void Database::deleteRecord() {
    if (dataFile.is_open()) {

        string Name;
        
        cout << "What is the name of the record you wish to delete? ";
        cin.ignore();
        getline(cin, Name);
        
        
        replace(Name.begin(), Name.end(), ' ', '_');
        
        fstream overflow(OVERFLOW.c_str());
        Records targetRec;
        bool inO = false;
        for (int i = 1; i < overflowCount+1; i++){
            overflow.seekg(i * RECORD_SIZE, ios::beg);
            targetRec.readRecord(overflow);
            if (targetRec.getName() == Name) {
                targetRec.writeBlank(overflow);
                inO = true;
            }
        }

        if (!inO) {
            int RecordNum = binarySearch(Name, dataFile, NUM_RECORDS-1);
            if (RecordNum) {
                dataFile.seekg(RecordNum * RECORD_SIZE, ios::beg);
                targetRec.writeBlank(dataFile);
            }
            else {
                cout << "Sorry, the record you requested could not be found ): " << endl;
            }
        }
        overflow.close();
    }
    else {
        cout << "Error: no database is currently open ):" << endl;
    }
}

void Database::closeDatabase() {
    ofstream config;
    config.open(CONFIG.c_str());
    config << NUM_RECORDS << endl;
    config << RECORD_SIZE << endl;
    config << overflowCount << endl;
    config.close();
    dataFile.close();  
    if (!dataFile.is_open()) {
        cout << "Successfully closed database! Thank u for your time :)" << endl;
    }
    else {
        cout << "Sorry, there was an error closing the file ):" << endl;
    }
}

