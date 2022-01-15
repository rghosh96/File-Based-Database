
# File Based Database
A file-based data system that will read in a csv file and convert it to a database system written in C++.

## Overview of Database Operations
The user can either create a new database or open a preexisting database. Upon creation of a database, three files are created: 
1. A data file, with fixed length records, with all the data from the input csv
2. A config file, which has three pieces of information: number of records, record size, and the number of records in the overflow
3. An overflow file, which holds added records (up to 4), which are then merged into the main data file automatically.

The user can then update, delete, search, or add a record, create a report, close the database, or quit the program. If any of these operations are tried to access without a database already open, an error is thrown. If a database is already open, and another is tried to be opened, an error is thrown once again (asking the user to close the current database before proceeding).

When adding records, it is first added to the overflow file. If the overflow file count exceeds 4, then it is automatically merged to the main data file. This is done by loading each record in the overflow into an array called memory[]. Then a function is called to sort these records, and then a function is called to rewrite the database with the new records merged in. If any records were deleted (marked “BLANK”), then they are passed over during the merge. System calls are invoked at the end in order to overwrite the original data file with the new database with the new records. Finally, the config file is also updated with the new number of records.

Some interesting things to note during the development of this program: the config file also keeps track of how many records are in the overflow. This is so that if the database is closed and reopened, the program “remembers” how many records were in the database. Another interesting thing was, when displaying, updating, or deleting a record from overflow, binary search could not be used. This is because the records in overflow are not sorted. Hence, they are looped over, which is not too detrimental to performance since there are only 4 maximum at a time.

Finally, a quick comment on file I/O: a lot was learned during the development of this program about C++ file I/O. Fstreams have different calls from ofstreams and ifstreams, especially when opening them. There are different flags that can be set to specify how it should be accessed. There are also different calls (from ofstream and ifstream) when checking whether or not the file is open. This caused many errors when first checking if the files were correctly being accessed and associated with a stream.
