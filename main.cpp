#include <iostream>
#include <conio.h>
#include <mysql.h>
#include <sstream>

#include "login.h"

using namespace std;

MYSQL *conn;
MYSQL_RES *res_set;
MYSQL_ROW row;
stringstream stmt;
const char *q;
string query;

/**
 * @brief Represents a book entity with attributes and operations related to books.
 *
 * This class provides methods to manage book-related data, including adding books,
 * updating price information, searching for a specific book, updating details
 * of a book, and displaying the list of books.
 *
 * The class interacts with a database to persist and retrieve book data.
 */
class books {
    int id{};
    string name;
    string auth;
    int price{};
    int qty{};

public:
    void add();

    void update_price();

    void search();

    static void update();

    static void display();
};

/**
 * @brief Adds a new book record to the books' database.
 *
 * This method collects details of a book such as its name, author, price, and quantity
 * from the user and inserts the corresponding record into the database. It constructs
 * an SQL query dynamically and executes it to persist the data. If the operation is
 * successful, the user is notified; otherwise, an error message is displayed.
 *
 * The database interaction relies on a global MySQL connection and uses standard input
 * and output for user interaction.
 */
void books::add() {
    cout << "Enter the name of the book : ";
    cin >> name;
    cout << "Enter the name of the author : ";
    cin >> auth;
    cout << "Enter the Price :";
    cin >> price;
    cout << "Enter the Qty Received : ";
    cin >> qty;

    stmt.str("");
    stmt << "INSERT INTO books (name, auth, price, qty) VALUES ('" << name << "', '" << auth << "', '" << price <<
            "', '" << qty << "')";
    query = stmt.str();
    q = query.c_str();
    mysql_query(conn, q);
    res_set = mysql_store_result(conn);

    if (!res_set) {
        cout << endl << endl << "Book Record Inserter Successfully" << endl << endl << endl;
    } else {
        cout << endl << endl << "Entry ERROR !" << endl << "Contact Technical Team" << endl << endl << endl;
    }
}

/**
 * @brief Updates the price of a specific book in the database.
 *
 * This method prompts the user to enter the ID of the book whose price
 * needs to be updated. It retrieves the current details of the book,
 * including its name and price, and presents them to the user.
 * The user is then given the option to confirm whether they want to update
 * the price. If confirmed, the new price is input by the user and updated
 * in the database. If the ID provided does not correspond to a book
 * in the database, an appropriate message is displayed.
 *
 * Error handling is integrated to notify the user in case the update operation
 * encounters any issues.
 */
void books::update_price() {
    cout << "Enter the id of the book for update in price : ";
    cin >> id;

    stmt.str("");
    stmt << "Select name,price from books where id = " << id << ";";
    query = stmt.str();
    q = query.c_str();
    mysql_query(conn, q);
    res_set = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res_set)) != nullptr) {
        char choice;
        cout << "The Name of the book is : " << row[0] << endl;
        cout << "The current price of the book is : " << row[1] << endl;
        cout << "Do you Want to Update the Price [y/n] : ";
        cin >> choice;

        if (choice == 121 || choice == 89) {
            cout << "Enter the new price : ";
            cin >> price;

            stmt.str("");
            stmt << "UPDATE books SET price = " << price << " WHERE id = " << id << ";";
            query = stmt.str();
            q = query.c_str();
            mysql_query(conn, q);
            res_set = mysql_store_result(conn);

            if (!res_set) {
                cout << endl << endl << "Book Price Updated Successfully" << endl << endl << endl;
                getch();
            } else {
                cout << endl << endl << "Entry ERROR !" << endl << "Contact Technical Team" << endl << endl << endl;
                getch();
            }
        } else {
            cout << "No changes Made!!";
            getch();
        }
    } else {
        cout << "No Book found!!";
        getch();
    }
}

/**
 * @brief Searches for a book in the database using its unique identifier.
 *
 * This function prompts the user to enter the book ID and queries the database
 * for the corresponding book details. If the book exists, it retrieves and
 * displays details such as the book's name, author, price, and inventory count.
 * If no record is found, an appropriate message is displayed.
 *
 * The function interacts directly with a MySQL database to perform the search query
 * and process the results. It uses internal member variables and database
 * connection objects for query execution and result handling.
 */
void books::search() {
    cout << "Enter book id for details : ";
    cin >> id;

    stmt.str("");
    stmt << "Select * from books where id = " << id << ";";
    query = stmt.str();
    q = query.c_str();
    mysql_query(conn, q);
    res_set = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res_set)) != nullptr) {
        cout << "the Details of Book Id " << row[0] << endl;
        cout << "The Name of the book is : " << row[1] << endl;
        cout << "THE Author of " << row[1] << " is " << row[2] << endl;
        cout << "The Price of the book is : " << row[3] << endl;
        cout << "The inventory count is " << row[4] << endl;
        getch();
    } else {
        cout << "No record Found" << endl;
        getch();
    }
}

/**
 * @brief Updates the inventory and purchase records in the database.
 *
 * This static method synchronizes the quantities of books in the inventory based on the purchase orders
 * received. It performs the following operations:
 * - Retrieves a list of books and their quantities from the purchases table where the status
 *   indicates they have been received and do not yet have an invoice marked.
 * - Updates the purchases table to mark these received orders as invoiced.
 * - Iterates through the retrieved records and adjusts the inventory of the corresponding books
 *   in the books table by updating their quantities.
 *
 * The method communicates with a MySQL database using queries for data retrieval and updates.
 * It assumes active connections and initialized global variables for interacting with the database.
 *
 * The output is a confirmation message indicating that the orders have been successfully updated.
 */
void books::update() {
    int b_id[100],qty[100],i=0;
    stmt.str("");
    stmt << "Select book_id,qty from purchases where receives = 'T' and inv IS NULL;";
    query = stmt.str();
    q = query.c_str();
    mysql_query(conn, q);
    res_set = mysql_store_result(conn);
    stmt.str("");
    stmt << "Update purchases set inv = 1 where receives = 'T' and inv IS NULL;";
    query = stmt.str();
    q = query.c_str();
    mysql_query(conn, q);

    while ((row = mysql_fetch_row(res_set)) != nullptr) {

        if (row[0] != nullptr) {
            b_id[i] = std::stoi(row[0]);
        }

        qty[i] = row[1] ? std::stoi(row[1]) : 0;

        i++;
    }

    const int max = i;

    for (i = 0; i <= max; i++) {
        stmt.str("");
        stmt << "update books set qty = " << qty[i] << " where id = " << b_id[i] << ";";
        query = stmt.str();
        q = query.c_str();
        mysql_query(conn, q);
    }

    cout << "The orders received have been updated.";
}

void books::display() {
}

/**
 * @brief Prompts the user to enter an 8-digit password.
 *        Displays feedback based on the entered password's correctness.
 *
 * The user is prompted to input the password using masked input, with each
 * digit replaced by an asterisk (*) on the screen. The input is then validated
 * against a predefined password stored in a constant. If the password is correct,
 * a success message is displayed; otherwise, an error message is displayed, and
 * the program terminates.
 *
 * @note The function uses `getch()` for character input and masking the password.
 *       It also makes use of `exit(1)` to terminate the program in case of an
 *       incorrect password.
 *
 * @warning The predefined password is stored as `PASSWORD`, which should be defined
 *          as a constant before the function is called. Ensure its definition is in
 *          scope when the function runs.
 *
 * @details
 * - The password must be exactly 8 digits long. Any shorter or longer entry is invalid.
 * - Outputs asterisks (*) to the console for masking input digits.
 * - Terminates with error status if the password is incorrect.
 */
void pass() {
    int num = 0;
    cout << "Enter password : ";

    for (int i = 0; i < 8; i++) {
        num = num * 10 + (getch() - 48);
        cout << "*";
    }

    if (num == PASSWORD) {
        cout << endl << "Correct password!" << endl << endl;
        cout << "Press any key...";
        getch();
    } else {
        cout << endl << endl << "Incorrect password!" << endl << endl;
        cout << "Press any key...";
        getch();
        exit(1);
    }
}

void book_menu() {
    books b;

    int c;
    cout << "*************************************************" << endl;
    cout << "                  BOOK MENU" << endl;
    cout << "*************************************************" << endl;
    cout << "   1. ADD" << endl;
    cout << "   2. UPDATE PRICE" << endl;
    cout << "   3. SEARCH" << endl;
    cout << "   4. UPDATE STATUS" << endl;
    cout << "   5. DISPLAY ALL" << endl;
    cout << "   6. RETURN TO MAIN MENU" << endl << endl << endl;
    cout << "Enter Your Choice : ";
    cin >> c;

    switch (c) {
        case 1:
            b.add();
            break;
        case 2:
            b.update_price();
            break;
        case 3:
            b.search();
            break;
        case 4:
            books::update();
            break;
        default: ;
    }
}

void main_menu() {
    int c;
    cout << "*************************************************" << endl;
    cout << "         BOOKSHOP MANAGEMENT SYSTEM" << endl;
    cout << "*************************************************" << endl;
    cout << "   1. BOOKS" << endl;
    cout << "   2. SUPPLIERS" << endl;
    cout << "   3. PURCHASES" << endl;
    cout << "   4. EMPLOYEES" << endl;
    cout << "   5. MEMBERS" << endl;
    cout << "   6. SALES" << endl;
    cout << "   7. EXIT" << endl << endl << endl;
    cout << "Enter Your Choice : ";
    cin >> c;

    switch (c) {
        case 1:
            system("cls");
            book_menu();
        case 2:
        default: ;
    }
}

[[noreturn]] int main() {
    pass();

    conn = mysql_init(nullptr);
    conn = mysql_real_connect(conn, HOST, USER, PASS, DATABASE, PORT, nullptr, 0);

    if (conn) {
        while (TRUE) {
            system("cls");
            main_menu();
        }
    }

    system("cls");
}
