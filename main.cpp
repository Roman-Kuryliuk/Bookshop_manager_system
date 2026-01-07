#include <iostream>
#include <conio.h>

#include "login.h"

using namespace std;

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

    for (int i=0; i<8; i++) {
        num=num*10+(getch()-48);
        cout<<"*";
    }

    if (num == PASSWORD) {
        cout << endl << "Correct password!" << endl << endl;
        cout << "Press any key...";
        getch();
    }
    else {
        cout << endl << endl << "Incorrect password!" << endl << endl;
        cout << "Press any key...";
        getch();
        exit(1);
    }
}

int main() {
    pass();
    system("cls");
    return 0;
}