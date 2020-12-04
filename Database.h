/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Database.h
 * Author: rghosh
 *
 * Created on February 1, 2020, 10:17 AM
 */
#include <string>
#include <fstream>
#include <algorithm>
#include "Records.h"

using namespace std;

#ifndef DATABASE_H
#define DATABASE_H

const int MEM_SIZE = 5;

class Database {
public:
    Database();
    Database(const Database& orig);
    virtual ~Database();
    
    void createDatabase();
    void openDatabase();
    void closeDatabase();
    void createReport();
    Records getRecord(fstream &Din, const int RecordNum);
    int binarySearch(const string nameIn, fstream &file, int high);
    void updateRecord();
    void addRecord();
    void displayRecord();
    void deleteRecord();
    void sortRecords();
    void mergeOverflow();
    void rewriteDB();
    
private:
    string DATAFILE;
    string OVERFLOW;
    string CONFIG;
    string CSV_FILE;
    int RECORD_SIZE;
    int NUM_RECORDS;
    fstream dataFile;
    Records memory[MEM_SIZE];
    int overflowCount;
};

#endif /* DATABASE_H */

