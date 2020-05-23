#include <iostream>
#include <fstream>
#include <string>
#include <sqlite3.h>

using namespace std;

//creating seperate objects to buy books

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
        void addBook() {

            string bookTitle, bookAuthor, bookISBN, bookPubName, bookPubDOB;
            int bookVolNumber, bookPrice;
            
            cout << "Enter the title of the book: ";
            cin.ignore();
            getline(cin, bookTitle);

            cout << "Enter the author of the book: ";
            cin.ignore();
            getline(cin, bookAuthor);

            cout << "Enter the ISBN of the book: ";
            cin.ignore();
            getline(cin, bookISBN);

            cout << "Enter the publisher name of the book: ";
            cin.ignore();
            getline(cin, bookPubName);

            cout << "Enter the publication date (DD MONTH, YYYY) of the book: ";
            cin.ignore();
            getline(cin, bookPubDOB);

            while (cout << "Enter the volume number of the book: " && !(cin >> bookVolNumber)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input of volume number! Enter integers only.\n";
            }

            while (cout << "Enter the price of the book: " && !(cin >> bookPrice)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input of price value! Enter integers only.\n";
            }

            sqlite3* database; 
            char* errorMSG;
            int exit = sqlite3_open("includes/database.db", &database);
        
            string sqlInsert = "INSERT INTO books(title, author, ISBN, pubName, pubDOB, volNumber, price)"
                              "VALUES ( '" + bookTitle + "', '" + bookAuthor + "', '" + bookISBN + "', '" + bookPubName + "', '" + bookPubDOB + "', " + to_string(bookVolNumber) + ", " + to_string(bookPrice) + ");";

            exit = sqlite3_exec(database, sqlInsert.c_str(), NULL, 0, &errorMSG);

            if (exit != SQLITE_OK) { 
                cerr << "\n\nError inserting into the database!\n\n"; 
                sqlite3_free(errorMSG); 
            } else {
                cout << "\n\nBook added into database without any erros!\n\n";
            }

            sqlite3_close(database);

        }

        void editBook() {

            int tableID;
            string newTitle, newAuthor, newISBN, newPubName, newPubDOB;
            int newVolNumber, newPrice;

            while (cout << "Enter id of the book you want to edit: " && !(cin >> tableID)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input of table ID! Enter integers only.\n";
            }

            cout << "Enter the new title of the book: ";
            cin.ignore();
            getline(cin, newTitle);

            cout << "Enter the new author of the book: ";
            cin.ignore();
            getline(cin, newAuthor);

            cout << "Enter the new ISBN of the book: ";
            cin.ignore();
            getline(cin, newISBN);

            cout << "Enter the new publisher name of the book: ";
            cin.ignore();
            getline(cin, newPubName);

            cout << "Enter the new publication date (DD MONTH, YYYY) of the book: ";
            cin.ignore();
            getline(cin, newPubDOB);

            while (cout << "Enter the new volume number of the book: " && !(cin >> newVolNumber)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input of volume number! Enter integers only.\n";
            }

            while (cout << "Enter the new price of the book: " && !(cin >> newPrice)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input of price value! Enter integers only.\n";
            }

            sqlite3* database; 
            char* errorMSG;
            int exit;
            string data;
            
            sqlite3_open("includes/database.db", &database);

            cout << "Before changing values: \n";
            string sqlShowQuery = "SELECT * FROM books WHERE id = " + to_string(tableID) + ";";

            sqlite3_exec(database, sqlShowQuery.c_str(), callback, (void*)data.c_str(), NULL);
        
            string sqlUpdate = "UPDATE books SET "
                               "'title' = '" + newTitle + "', "
                               "'author' = '" + newTitle + "', "
                               "'ISBN' = '" + newISBN + "', "
                               "'pubName' = '" + newPubName + "', "
                               "'pubDOB' = '" + newPubDOB + "', "
                               "'volNumber' = '" + to_string(newVolNumber) + "', "
                               "'price' = '" + to_string(newPrice) + "' "
                               "WHERE id = " + to_string(tableID) + ";";

            exit = sqlite3_exec(database, sqlUpdate.c_str(), NULL, 0, &errorMSG);

            if (exit != SQLITE_OK) { 
                cerr << "\n\nError updating from the database!\n\n"; 
                sqlite3_free(errorMSG); 
            } else {
                cout << "\n\nBook updated from database without any errors!\n\n";
            }

            cout << "After changing values: \n";
            sqlite3_exec(database, sqlShowQuery.c_str(), callback, (void*)data.c_str(), NULL);

            sqlite3_close(database);

        }

        void editBook(string editColumnName) {

            int tableID;
            string newEdit;

            while (cout << "Enter id of the book you want to edit: " && !(cin >> tableID)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input of table ID! Enter integers only.\n";
            }

            cout << "Enter the value you want to replace with: ";
            if(editColumnName == "pubDOB") cout << "(DD MONTH, YYYY)";
            cin.ignore();
            getline(cin, newEdit);

            sqlite3* database; 
            char* errorMSG;
            int exit;
            string data;
            
            sqlite3_open("includes/database.db", &database);

            cout << "Before changing values: \n";
            string sqlShowQuery = "SELECT * FROM books WHERE id = " + to_string(tableID) + ";";

            sqlite3_exec(database, sqlShowQuery.c_str(), callback, (void*)data.c_str(), NULL);
        
            string sqlUpdate = "UPDATE books SET '" + editColumnName + "' = '" + newEdit + "' WHERE id = " + to_string(tableID) + ";";

            exit = sqlite3_exec(database, sqlUpdate.c_str(), NULL, 0, &errorMSG);

            if (exit != SQLITE_OK) { 
                cerr << "\n\nError updating from the database!\n\n"; 
                sqlite3_free(errorMSG); 
            } else {
                cout << "\n\nBook updated from database without any errors!\n\n";
            }

            cout << "After changing values: \n";
            sqlite3_exec(database, sqlShowQuery.c_str(), callback, (void*)data.c_str(), NULL);

            sqlite3_close(database);

        }

        void editBook(int editBookColumnID) {

            int tableID, newEdit;
            string editColumnName;

            if(editBookColumnID == 6) {
                editColumnName = "volNumber";
            } else {
                editColumnName = "price";
            }

            while (cout << "Enter id of the book you want to edit: " && !(cin >> tableID)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input of table ID! Enter integers only.\n";
            }

            while (cout << "Enter the value you want to replace with: " && !(cin >> newEdit)) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input of the value! Enter integers only.\n";
            }

            sqlite3* database; 
            char* errorMSG;
            int exit;
            string data;
            
            sqlite3_open("includes/database.db", &database);

            cout << "Before changing values: \n";
            string sqlShowQuery = "SELECT * FROM books WHERE id = " + to_string(tableID) + ";";

            sqlite3_exec(database, sqlShowQuery.c_str(), callback, (void*)data.c_str(), NULL);
        
            string sqlUpdate = "UPDATE books SET '" + editColumnName + "' = " + to_string(newEdit) + " WHERE id = " + to_string(tableID) + ";";

            exit = sqlite3_exec(database, sqlUpdate.c_str(), NULL, 0, &errorMSG);

            if (exit != SQLITE_OK) { 
                cerr << "\n\nError updating from the database!\n\n"; 
                sqlite3_free(errorMSG); 
            } else {
                cout << "\n\nBook updated from database without any errors!\n\n";
            }

            cout << "After changing values: \n";
            sqlite3_exec(database, sqlShowQuery.c_str(), callback, (void*)data.c_str(), NULL);

            sqlite3_close(database);
        }

        void deleteBook() {
            int bookID;

            while (cout << "Enter the ID of the book you want to delete: " && !(cin >> bookID)) {
                cin.clear();
                cin.ignore();
                cout << "\n\nInvalid input of book ID! Enter integers only.\n\n";
            }

            sqlite3* database; 
            char* errorMSG;
            int exit;
            
            sqlite3_open("includes/database.db", &database);
        
            string sqlDelete = "DELETE FROM books WHERE id = " + to_string(bookID) + ";";

            exit = sqlite3_exec(database, sqlDelete.c_str(), NULL, 0, &errorMSG);

            if (exit != SQLITE_OK) { 
                cerr << "\n\nError deleting from the database!\n\n"; 
                sqlite3_free(errorMSG); 
            } else {
                cout << "\n\nBook deleted from database without any errors!\n\n";
            }

            sqlite3_close(database);
        }   

        void displaySearch(string searchColumn) {
            sqlite3* database;
            sqlite3_open("includes/database.db", &database); 
            string searchQuery;
            string data;

            cout << "Enter " + searchColumn + " to search: ";
            cin >> searchQuery;          
        
            string sqlQuery = "SELECT * FROM books WHERE " + searchColumn + " like '%" + searchQuery + "%';"; 

            sqlite3_exec(database, sqlQuery.c_str(), callback, (void*)data.c_str(), NULL); 
            
            sqlite3_close(database);
        }

        static int callback(void* data, int argc, char** argv, char** azColName) { 
            int i;

            cout << "\n\n";
            for (i = 0; i < argc; i++) {
                if(i == 0) cout << "ID: ";
                if(i == 1) cout << "Title: ";
                if(i == 2) cout << "Author: ";
                if(i == 3) cout << "ISBN: ";
                if(i == 4) cout << "Publisher: ";
                if(i == 5) cout << "Publishing Date: ";
                if(i == 6) cout << "Volume Number: ";
                if(i == 7) cout << "Book Price: ";

                cout << argv[i] << endl;
            }
            cout << "\n\n"; 

            return 0; 
        } 
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

class Admin : public Person, public Book{
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

                cout << "\n\n";
                cout << "Welcome to Book Store's Admin Login\n";
                cout << "What would you like to do?\n";
                cout << "1. Search Books\t2. Add Book\n3. Edit Book\t4. Delete Book\n5. Log Out\n";
                cin >> menuChoice;

                if(menuChoice == 1) {

                    int searchOption;
                    cout << "Would you like to search via: \n";
                    cout << "1. Book Title\t2. Book Author\n3. Book ISBN\n";
                    cin >> searchOption;

                    if(searchOption == 1) displaySearch("title");
                    else if(searchOption) displaySearch("author");
                    else if(searchOption) displaySearch("ISBN");
                    else cout << "You entered the wrong option!";

                } else if(menuChoice == 2) {
                    addBook();
                } else if(menuChoice == 3) {
                    
                    int editOption;
                    cout << "What would you like to edit: \n";
                    cout << "1. Title \t2. Author \t3. ISBN \t4. Publisher Name\n5. Publishing Date \t\t6. Volume \t7.Price \t8.Complete Entry";
                    cin >> editOption;

                    if(editOption == 1) editBook("title");
                    else if(editOption == 2) editBook("author");
                    else if(editOption == 3) editBook("ISBN");
                    else if(editOption == 4) editBook("pubName");
                    else if(editOption == 5) editBook("pubDOB");
                    else if(editOption == 6) editBook(6);
                    else if(editOption == 7) editBook(7);
                    else if(editOption == 8) editBook();
                    else cout << "You entered the wrong option!";

                } else if(menuChoice == 4) {
                    deleteBook();
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
    sqlite3* database;
    int mainMenuChoice;
    string username, password;
    ifstream dbCheck("includes/database.db");
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
                                    "VALUES ('Lies of Locke Lamora', 'Scott Lynch', '9780553588941', 'Bantam Spectra', '27 June, 2006', 1, 1000),"
                                    "       ('The Blade Itself', 'Joe Abercrombie', '9780575091504', 'Orion Publishing Group', '18 June, 2009', 1, 1000),"
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

        cout << "Database created successfuly!\n"; 
    }

    dbCheck.close();
    sqlite3_close(database);

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

    return 0;
}