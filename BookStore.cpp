#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>

using namespace std;

class Book {
    private:
        int id;
        string title;
        string author;
        string ISBN;
        string pubName;
        string pubDOB;
        int volNumber;
        int price;

    public:

        //setters
        void setID(int id) {
            this->id = id;
        }
        
        void setTitle(string title) {
            this->title = title;
        }

        void setAuthor(string author) {
            this->author = author;
        }

        void setISBN(string ISBN) {
            this->ISBN = ISBN;
        }

        void setPubName(string pubName) {
            this->pubName = pubName;
        }

        void setPubDOB(string pubDOB) {
            this->pubDOB = pubDOB;
        }

        void setVolNumber(int volNumber) {
            this->volNumber = volNumber;
        }

        void setPrice(int price) {
            this->price = price;
        }

        //methods
        // int id;
        // string title;
        // string author;
        // string ISBN;
        // string pubName;
        // string pubDOB;
        // int volNumber;
        // int price;
        // void addBook() {
        //     cout << "Enter the ID of the book"
        // }

        



        
        
};

class Person {
    protected: 
        string fName;
        string lName;
        string username;
        string password;
        bool adminStatus;

    public:

        //setters
        void setFName(string fName) {
            this->fName = fName;
        }
        void setLName(string lName) {
            this->lName = lName;
        }
        void setUsername(string username) {
            this->username = username;
        }
        void setPassword(string password) {
            this->password = password;
        }
        void setAdminStatus(bool Adminstatus) {
            this->adminStatus = adminStatus;
        }
        
        void setLogin(string username, string password, bool adminStatus) {
            setUsername(username);
            setPassword(password);
            setAdminStatus(adminStatus);
        }

};

class Customer : public Person {
    public:
        void cusMenu() {
            cout << "Welcome to the Store";
        }

};

class Admin : public Person{
    public:

        bool adminLoginVerify() {
            if(!(username == "1" && password == "1")) {
                return 0;
            } else {
                return 1;
            }
        }

        void adminMenu() {
            int menuChoice;

            do {

                cout << "Welcome to Book Store's Admin Login\n";
                cout << "What would you like to do?\n";
                cout << "1. Search Books\t2. Add Book\n3. Delete Book\t4. Update Book\n5. Log Out";
                cin >> menuChoice;

                if(menuChoice == 1) {
                    cout << "1";
                } else if(menuChoice == 2) {
                    cout << "2";
                } else if(menuChoice == 3) {
                    cout << "4";
                } else if(menuChoice == 4) {
                    cout << "4";
                } else if(menuChoice == 5) {
                    break;
                } else {
                    cout << "You entered a wrong option! Try agian!\n";
                    continue;
                }
            } while(menuChoice);
            
        }

};

int main() {

    int mainMenuChoice;
    string username, password;
    ifstream dbCheck("includes/database.db");
    sqlite3* database;
    int exit = sqlite3_open("includes/database.db", &database);

    if(!(dbCheck)) {
        
        char* errorMSG;

        if(exit) {
            cerr << "Error opening database: " << sqlite3_errmsg(database) << endl;
            return -1;
        } else {

            string sqlCreate =  "CREATE TABLE users ("
                                "id	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                                "firstName	TEXT NOT NULL,"
                                "lastName	TEXT NOT NULL,"
                                "username	TEXT NOT NULL UNIQUE,"
                                "password	TEXT NOT NULL UNIQUE,"
                                "adminStatus	INTEGER NOT NULL);"

                                "CREATE TABLE books ("
                                "id	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                                "title	TEXT NOT NULL,"
                                "author	TEXT NOT NULL,"
                                "ISBN	TEXT NOT NULL UNIQUE,"
                                "pubName	TEXT NOT NULL,"
                                "pubDOB	TEXT NOT NULL,"
                                "volNumber	INTEGER NOT NULL,"
                                "price	INTEGER NOT NULL);";

            exit = sqlite3_exec(database, sqlCreate.c_str(), NULL, 0, &errorMSG);

            if (exit != SQLITE_OK) { 
                cerr << "Error while creating table!" << endl; 
                sqlite3_free(errorMSG); 
            } else {

                string sqlInsert =  "INSERT INTO books"
                                    "(title, author, ISBN, pubName, pubDOB, volNumber, price)"
                                    "VALUES ('Lies of Locke Lamora', 'Scott Lynch', '9780553588941', 'Bantam Spectra', 'June 27, 2006', 1, 1000),"
                                    "       ('The Blade Itself', 'Joe Abercrombie', '9780575091504', 'Orion Publishing Group', 'June 18, 2009', 1, 1000),"
                                    "       ('All the Light We Cannot See', 'Anthony Doerr', '9781476746586', 'Scribner', '12 August, 2014', 1, 800),"
                                    "       ('A Feast for Crows', 'George R.R. Martin', '9780553582024', 'Bantam Books', '17 September, 2011', 1, 1200),"
                                    "       ('Circe', 'Madeline Miller', '9780316556347', 'Little, Brown and Company', '10 April, 2018', 1, 800);";
                
                exit = sqlite3_exec(database, sqlInsert.c_str(), NULL, 0, &errorMSG);

                if (exit != SQLITE_OK) { 
                    cerr << "Error inserting into the database!" << endl; 
                    sqlite3_free(errorMSG); 
                } 
            }
        }   
    }

    dbCheck.close();

    cout << "Welcome to Mooney's Book Store!\n";
    cout << "-------------------------------\n";
    cout << "Are you a customer or an admin?\n";
    cout << "1. Customer \t 2. Admin\n";
    cin >> mainMenuChoice;

    if(mainMenuChoice == 1) {
        cout << "TDC";
    } else if (mainMenuChoice == 2) {

        Admin admin;

        do {
            cout << "Pleaes Enter your admin login:\n";
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;

            
            admin.setLogin(username, password, 1);

            if(admin.adminLoginVerify()) {
                admin.adminMenu();
            } else {
                cout << "Your login was wrong! Try again!\n";
            }

        } while(!(admin.adminLoginVerify()));

    }

    sqlite3_close(database);

    return 0;
}