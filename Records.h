/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Records.h
 * Author: rghosh
 *
 * Created on February 1, 2020, 1:04 PM
 */

#include <string>
#include <fstream>
#include <algorithm>

#ifndef RECORDS_H
#define RECORDS_H

using namespace std;

class Records {
public:
    Records();
    Records(const Records& orig);
    virtual ~Records();
    
    void readRecord(fstream &file);
    void writeRecord(fstream &file, string name);
    void writeNewRec(fstream &file);
    void writeBlank(fstream &file);
    void setRecord(fstream &file);
    
    string getName();
    string getRank();
    string getCity();
    string getState();
    string getZip();
    string getEmployees();
    
    void printRecord();
    
private:
    string Name, Rank, City, State, Zip, Employees;
};

#endif /* RECORDS_H */

