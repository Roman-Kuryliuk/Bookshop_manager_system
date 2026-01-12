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

    static void search();

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

void books::search() {
}

void books::update() {
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
