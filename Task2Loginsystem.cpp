#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Adds a new user to users.txt, but first checks the file
// to make sure the username isn't already taken.
void registerUser() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Step 1: scan the existing users file for a duplicate name
    ifstream inFile("users.txt");
    string existingUser, existingPass;
    bool usernameTaken = false;

    while (inFile >> existingUser >> existingPass) {
        if (existingUser == username) {
            usernameTaken = true;
            break; // no need to keep reading once we find a match
        }
    }
    inFile.close();

    if (usernameTaken) {
        cout << "Username already exists. Try a different one.\n";
        return;
    }

    // Step 2: append the new user (ios::app makes sure we don't
    // overwrite everyone who registered before us)
    ofstream outFile("users.txt", ios::app);
    outFile << username << " " << password << endl;
    outFile.close();

    cout << "Registration successful!\n";
}

// Checks entered credentials against everything stored in users.txt
void loginUser() {
    string username, password;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream inFile("users.txt");
    string existingUser, existingPass;
    bool credentialsMatch = false;

    while (inFile >> existingUser >> existingPass) {
        if (existingUser == username && existingPass == password) {
            credentialsMatch = true;
            break;
        }
    }
    inFile.close();

    if (credentialsMatch) {
        cout << "Login successful! Welcome, " << username << ".\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n1. Register\n2. Login\n3. Exit\nEnter choice: ";
        if (!(cin >> choice)) {
          cin.clear();              // Clear the error state
          cin.ignore(1000, '\n');   // Remove the invalid input
          cout << "Invalid choice.\n";
          continue;
     }

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            loginUser();
        } else if (choice != 3) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);

    return 0;
}