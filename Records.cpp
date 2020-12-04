/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Records.cpp
 * Author: rghosh
 * 
 * Created on February 1, 2020, 1:04 PM
 */
#include "Records.h"
#include <iostream>

using namespace std;

Records::Records() {
}

Records::Records(const Records& orig) {
    Name = orig.Name;
    Rank = orig.Rank;
    City = orig.City;
    State = orig.State;
    Zip = orig.Zip;
    Employees = orig.Employees;
}

Records::~Records() {
}

void Records::writeRecord(fstream &file, string name)
{
    cout << "Please enter what you would like to update (re-enter same data if you wish to leave it as is):" << endl;
    cout << "Rank: ";
    cin >> Rank;
    if (Rank.length() > 10) {
        Rank = Rank.substr(0,10);
    }

    cout << "City: ";
    cin.ignore();
    getline(cin, City); 
    if (City.length() > 20) {
        City = City.substr(0,20);
    }
    replace(City.begin(), City.end(), ' ', '_');
    
    cout << "State: ";
    getline(cin, State);
    if (State.length() > 10) {
        State = State.substr(0,10);
    }
    replace(State.begin(), State.end(), ' ', '_');

    cout << "Zip: ";
    cin >> Zip;
    if (Zip.length() > 10) {
        Zip = Zip.substr(0,10);
    }

    cout << "Employees: ";
    cin >> Employees;
    if (Employees.length() > 10) {
        Employees = Employees.substr(0,10);
    }
  
    file << setw(40) << left << name;
    file << setw(10) << left << Rank;
    file << setw(20) << left << City;
    file << setw(10) << left << State;
    file << setw(10) << left << Zip;
    file << setw(10) << left << Employees << endl;
}

void Records::writeNewRec(fstream &file)
{ 
    file << setw(40) << left << Name;
    file << setw(10) << left << Rank;
    file << setw(20) << left << City;
    file << setw(10) << left << State;
    file << setw(10) << left << Zip;
    file << setw(10) << left << Employees << endl;
}

void Records::writeBlank(fstream &file)
{
    file << setw(40) << left << "BLANK";
    file << setw(10) << left << "BLANK";
    file << setw(20) << left << "BLANK";
    file << setw(10) << left << "BLANK";
    file << setw(10) << left << "BLANK";
    file << setw(10) << left << "BLANK" << endl;
}

void Records::readRecord(fstream &file)
{
   file >> Name >> Rank >> City >> State >> Zip >> Employees;
}

string Records::getName() {
    return Name;
}

string Records::getRank() {
    return Rank;
}

string Records::getCity() {
    return City;
}

string Records::getState() {
    return State;
}

string Records::getZip() {
    return Zip;
}

string Records::getEmployees() {
    return Employees;
}

void Records::setRecord(fstream &file) {
    file >> Name >> Rank >> City >> State >> Zip >> Employees;
}

void Records::printRecord() {
    cout << Name << " " << Rank << " " << City << " " << State << " " << Zip << " " << 
            Employees << endl;
}
