#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sqlite3.h>

//TODO change/update the output/cout look

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

        Book() {
            setID(0);
            setTitle("NULL");
            setAuthor("NULL");
            setISBN("NULL");
            setPubName("NULL");
            setPubDOB("NULL");
            setVolNumber(0);
            setPrice(0);
        }

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

        void setBook(int id, string title, string author, string ISBN, string pubName, string pubDOB, int volNumber, int price) {
            setID(id);
            setTitle(title);
            setAuthor(author);
            setISBN(ISBN);
            setPubName(pubName);
            setPubDOB(pubDOB);
            setVolNumber(volNumber);
            setPrice(price);
        }

        //getters

        int getID() {
            return this->id;
        }

        string getTitle() {
            return this->title;
        }

        string getAuthor() {
            return this->author;
        }

        string getISBN() {
            return this->ISBN;
        }

        string getPubName() {
            return this->pubName;
        }

        string getPubDOB() {
            return this->pubDOB;
        }

        int getVolNumber() {
            return this->volNumber;
        }

        int getPrice() {
            return this->price;
        }

        //methods

        void displayBook() {
            cout << "\nBook ID: \t\t" << getID();
            cout << "\nBook Title: \t\t" << getTitle();
            cout << "\nBook Author: \t\t" << getAuthor();
            cout << "\nBook ISBN: \t\t" << getISBN(); 
            cout << "\nBook Publisher: \t" << getPubName();
            cout << "\nBook Publishing Date: \t" << getPubName();
            cout << "\nBook Volume number: \t" << getVolNumber();
            cout << "\nBook Price: \t\t" << getPrice();
        }

        void addBook() {

            string bookTitle, bookAuthor, bookISBN, bookPubName, bookPubDOB, line;
            int bookVolNumber, bookPrice;
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter the title of the book: ";
            getline(cin, bookTitle);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter the author of the book: ";
            getline(cin, bookAuthor);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter the ISBN of the book: ";
            getline(cin, bookISBN);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter the publisher name of the book: ";
            getline(cin, bookPubName);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter the publication date (DD MONTH, YYYY) of the book: ";
            getline(cin, bookPubDOB);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter the new title of the book: ";
            getline(cin, newTitle);

            cout << "Enter the new author of the book: ";
            getline(cin, newAuthor);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter the new ISBN of the book: ";
            cin >> newISBN;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter the new publisher name of the book: ";
            getline(cin, newPubName);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter the new publication date (DD MONTH, YYYY) of the book: ";
            getline(cin, newPubDOB);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
                               "'author' = '" + newAuthor + "', "
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
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        void setAdminStatus(bool adminStatus) {
            this->adminStatus = adminStatus;
        }

        void setPerson(string fName, string lName, string username, string password, string adminStatus) {
            setFName(fName);
            setLName(lName);
            setUsername(username);
            setPassword(password);
            setAdminStatus (stoi(adminStatus));
        }

        //getters

        string getFName() {
            return this->fName;
        }

        string getLName() {
            return this->lName;
        }

        string getUsername() {
            return this->username;
        }

        string getPassword() {
            return this->password;
        }

        bool getAdminStatus() {
            return this->adminStatus;
        }

        //methods
        
        int verifyLogin(string username, string password) {

            string user[6];
            sqlite3* database;
            sqlite3_open("includes/database.db", &database);
            struct sqlite3_stmt *userStatement;
        
            string sqlQuery = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "';"; 

            int result = sqlite3_prepare_v2(database, sqlQuery.c_str(), -1, &userStatement, NULL); 
            
            if(result == SQLITE_OK) {
                if (sqlite3_step(userStatement) == SQLITE_ROW) {
                    for(int i = 0; i < 6; i++) {
                        //this returns a 'unsigned const *' so i have to convert it into a string to be able to store it
                        user[i] = string(reinterpret_cast<const char*>(sqlite3_column_text(userStatement, i)));
                    }
                } else {
                    return 0;
                }
            }   
            sqlite3_finalize(userStatement);
            sqlite3_close(database);

            if(user[5] == "0") {
                return 2;
            }

            setPerson(user[1], user[2], user[3], user[4], user[5]);

            return 1;
        }
};

class Customer : public Person, public Book {
    private:
        Book book[5][25];

    public:

        bool verifyLogin(string username, string password) {

            string user[6];
            sqlite3* database;
            sqlite3_open("includes/database.db", &database);
            struct sqlite3_stmt *userStatement;
        
            string sqlQuery = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "';"; 

            int result = sqlite3_prepare_v2(database, sqlQuery.c_str(), -1, &userStatement, NULL); 
            
            if(result == SQLITE_OK) {
                if (sqlite3_step(userStatement) == SQLITE_ROW) {
                    for(int i = 0; i < 6; i++) {
                        //this returns a 'unsigned const *' so i have to convert it into a string to be able to store it
                        user[i] = string(reinterpret_cast<const char*>(sqlite3_column_text(userStatement, i)));
                    }
                } else {
                    return 0;
                }
            }   
            sqlite3_finalize(userStatement);
            sqlite3_close(database);

            setPerson(user[1], user[2], user[3], user[4], user[5]);

            return 1;
        }

        bool registerCus(string fName, string lName, string username, string password) {

            sqlite3* database; 
            char* errorMSG;
            int exit = sqlite3_open("includes/database.db", &database);

            string sqlInsert = "INSERT INTO users('firstName', 'lastName', 'username', 'password', 'adminStatus')"
                               "VALUES ('" + fName + "', '" + lName + "', '" + username + "', '" + password + "', 0);";

            exit = sqlite3_exec(database, sqlInsert.c_str(), NULL, 0, &errorMSG);

            if (exit != SQLITE_OK) {
                return 0;
            } 

            sqlite3_close(database);
            return 1;
        }         

        void cusMenu() {
            int menuChoice;
            do {

                cout << "\n\nWelcome " + getFName() + " " + getLName() + " to Mooney's Book Store!\n";
                cout << "What would you like to do: \n";
                cout << "1. Search Books \t2. Modify Cart\n3. Carts\t\t4. Check Out \n5. Log out\n";
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
                    addToCart();
                } else if(menuChoice == 3) {
                    checkCart();
                } else if(menuChoice == 4) {
                    checkOut();
                } else if(menuChoice == 5) {
                    break;
                } else {
                    cout << "You entered a wrong option! Try agian!\n";
                    continue;
                }

            } while(menuChoice);
        }

        void checkOut() {
            int cartNumber, totalPrice = 0, checkoutConfirmation;

            do {
                totalPrice = 0;
                cout << "\n\nEnter the cart number (1 to 5) you'd like to check out. \n";
                cout << "(Enter any number outside the range from 1 to 5 to get back to main menu)\n";
                cin >> cartNumber;

                cartNumber = cartNumber - 1;

                if(cartNumber < 0 || cartNumber > 4) {
                    cout << "\nYou entered the wrong cart number!!\n";
                    continue;
                } else {

                    for(int i = 0; i < 25; i++) {

                    if(book[cartNumber][i].getTitle() == "NULL") continue;

                        cout << "\nBook: \t\t" << i + 1 << "\n";
                        book[cartNumber][i].displayBook();
                        cout << "\n";

                        totalPrice = totalPrice + book[cartNumber][i].getPrice();
                            
                    }

                    if(cartNumber == 0) cartNumber = 1;
                } 

                cout << "\nTotal price of all books is: " << totalPrice << "\n"
                        "\nAre you sure you want to proceed with this cart?\n"
                        "Press 1 if you want to check out\n"
                        "Press 0 or any other number if you want to go back to main menu\n";
                cin >> checkoutConfirmation;

                if(checkoutConfirmation == 1) {
                    cout << "\n\nThank you for purchasing these books!\n\n";
                    break;
                } else {
                    break;
                }

            } while (!checkoutConfirmation);


        }

        void addToCart() {
            int bookID, cartNumber, cartLocation, res;
            do {

                cout << "\nEnter the ID of the book you would like to add to cart: ";
                cout << "\n(Enter Book ID as '-1' if you want to leave this menu.)\n";
                cout << "(Enter Book ID as '0' if you want to empty that cart location.)\n";
                cin >> bookID;

                if(bookID == -1) {
                    break;
                }

                cout << "\nWhich cart would you like to add this book to: ";
                cin >> cartNumber;

                cartNumber = cartNumber - 1;

                if(cartNumber < 0 || cartNumber > 4) {
                    cout << "\nYou entered wrong cart number!\n";    
                    continue;
                }

                cout << "\nWhich cart location would you like to put this book into (1 to 25 range): ";
                cin >> cartLocation;

                cartLocation = cartLocation - 1;
                if(cartLocation < 0 || cartLocation > 24) {
                    cout << "\nYou entered wrong cart location! Choose from 1 to 25!\n";    
                    continue;
                }

                if(bookID == 0) {
                    book[cartNumber][cartLocation].setBook(0, "NULL", "NULL", "NULL", "NULL", "NULL", 0, 0);
                }

                res = pushIntoCartArray(bookID, cartNumber, cartLocation);

                if(res) {
                    cout << "\nBook added to cart!\n";
                    continue;
                } else {
                    cout << "\nBook ID you entered doesn't exist!\n";
                    continue;
                }

            } while (cartNumber);
        }

        bool pushIntoCartArray(int bookID, int cartNumber, int cartLocation) {
            string bookArray[8];
            sqlite3* database;
            sqlite3_open("includes/database.db", &database);
            struct sqlite3_stmt *userStatement;
            
            string sqlQuery = "SELECT * FROM books WHERE id = '" + to_string(bookID) + "';"; 

            int result = sqlite3_prepare_v2(database, sqlQuery.c_str(), -1, &userStatement, NULL); 
                
            if(result == SQLITE_OK) {
                if (sqlite3_step(userStatement) == SQLITE_ROW) {
                    for(int i = 0; i < 8; i++) {
                        //this returns a 'unsigned const *' so i have to convert it into a string to be able to store it
                        bookArray[i] = string(reinterpret_cast<const char*>(sqlite3_column_text(userStatement, i)));
                    }
                } else {
                    return 0;
                }
            }   

            sqlite3_finalize(userStatement);
            sqlite3_close(database);

            book[cartNumber][cartLocation].setBook(stoi(bookArray[0]), bookArray[1], bookArray[2], bookArray[3], bookArray[4], bookArray[5], stoi(bookArray[6]), stoi(bookArray[7]));

            return 1;   
        }

        void checkCart() {
            int cartNumber, totalPrice = 0;

            do {
                totalPrice = 0;
                cout << "\n\nYou have 5 carts with the limit of 25 books per each cart!\n";
                cout << "Enter any number outside the limit from 1 to 5 to go back to customer menu!\n";
                cout << "Which cart would you like to check?\n";
                cin >> cartNumber;
                //making it more usable for arrays
                cartNumber = cartNumber -1;

                if(cartNumber < 0 || cartNumber > 4) {
                    cout << "\nGoing back to customer main menu!\n";
                    break;
                } else {

                    for(int i = 0; i < 25; i++) {

                        if(book[cartNumber][i].getTitle() == "NULL") continue;

                        cout << "\nBook: \t\t" << i + 1 << "\n";
                        book[cartNumber][i].displayBook();
                        cout << "\n";

                        totalPrice = totalPrice + book[cartNumber][i].getPrice();
                        
                    }

                    if(cartNumber == 0) cartNumber = 1;
                }

                cout << "Total price of all books is: " << totalPrice << "\n";

            } while(cartNumber);
        }

        

};

class Admin : public Person, public Book{
    public:

        void adminMenu(bool adminStatus) {
            int menuChoice;
            if(adminStatus) {
                do {

                    cout << "\n\n";
                    cout << "Welcome " + fName + " " + lName + " to Book Store's Admin Menu!\n";
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
                        cout << "1. Title \t2. Author \t3. ISBN \t4. Publisher Name\n5. Publishing Date \t\t6. Volume \t7.Price \t8.Complete Entry\n";
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
            } else {
                cout << "This account does not have admin privileges!";
            }
            
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
                
                //TODO update the query

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
        int customerOption, res = 0;
        Customer cus;
        do {

            cout << "\n\nWould you like to: \n";
            cout << "1. Login \t2. Register\n";
            cin >> customerOption;

            if(customerOption == 1) {

                    cout << "Pleaes Enter your admin login:\n";
                    cout << "Username: "; cin >> username;
                    cout << "Password: "; cin >> password;
                    
                    res = cus.verifyLogin(username, password);

                    if(res == 1) {
                        cus.cusMenu();
                    } else {
                        cout << "\nThis account does not exist!\n";
                    }

            } else if (customerOption == 2) {

                cout << "\nPlease don't use spaces in the inputs!\n";

                string fName, lName, username, password;
                
                cout << "Enter your username: \n";
                cin >> username;

                cout << "Enter your password: \n";
                cin >> password;

                cout << "Enter your first name: \n";
                cin >> fName;

                cout << "Enter your last name: \n";
                cin >> lName;

                res = cus.registerCus(fName, lName, username, password);

                if(res == 1) {
                    cout << "\nAccount created succesfuly!\n";
                    res = 0;
                } else {
                    cout << "\nUsername or Password already exists!\n";
                }

            } else {
                cout << "\nYou chose a wrong option!\n";
            }

        } while(!res);

    } else if (mainMenuChoice == 2) {

        Admin admin;
        int res;

        do {
            cout << "Pleaes Enter your admin login:\n";
            cout << "Username: "; cin >> username;
            cout << "Password: "; cin >> password;
            
            res = admin.verifyLogin(username, password);

            if(res == 1) {
                admin.adminMenu(admin.getAdminStatus());
            } else if(res == 2) {
                cout << "\nThis account doesn't have admin privileges!\n";
                res = 0;
            } else {
                cout << "\nThis account does not exist!\n";
            }

        } while(!res);

    }

    return 0;
}