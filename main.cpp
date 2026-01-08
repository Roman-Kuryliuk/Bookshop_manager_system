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

    void update();

    void display();
};

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
