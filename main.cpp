#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

// Class to handle user operations
class User {
private:
    string username;
    string password;

    void checkEmptyInput(const string& input, const string& fieldName) const {
        if (input.empty()) {
            throw invalid_argument(fieldName + " cannot be empty.");
        }
    }

public:
    User(const string& uname, const string& pwd) {
        checkEmptyInput(uname, "Username");
        checkEmptyInput(pwd, "Password");
        username = uname;
        password = pwd;
    }

    void registerUser() const {
        if (isUserRegistered()) {
            cout << "Error: Username already exists. Please choose a different username." << endl;
            return;
        }

        ofstream userFile(username + ".txt");
        if (!userFile) {
            cout << "Error: Unable to create user file. Please try again later." << endl;
            return;
        }

        userFile << username << endl;
        userFile << password << endl;
        userFile.close();
        cout << "Registration successful!" << endl;
    }

    bool loginUser() const {
        if (!isUserRegistered()) {
            cout << "Error: User does not exist. Please register first." << endl;
            return false;
        }

        string storedUsername, storedPassword;
        ifstream userFile(username + ".txt");
        if (userFile.is_open()) {
            getline(userFile, storedUsername);
            getline(userFile, storedPassword);
            userFile.close();

            if (storedUsername == username && storedPassword == password) {
                return true;
            } else {
                cout << "Error: Incorrect password." << endl;
                return false;
            }
        } else {
            cout << "Error: Unable to open user file. Please try again later." << endl;
            return false;
        }
    }

private:
    bool isUserRegistered() const {
        ifstream userFile(username + ".txt");
        return userFile.good();
    }
};

// Function to display the menu
void showMenu() {
    cout << "Welcome to Login and Registration System" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "Choose an option: ";
}

int main() {
    int choice;
    string username, password;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                try {
                    User newUser(username, password);
                    newUser.registerUser();
                } catch (const invalid_argument& ex) {
                    cout << "Error: " << ex.what() << endl;
                }
                break;
            }

            case 2: {
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                try {
                    User existingUser(username, password);
                    if (existingUser.loginUser()) {
                        cout << "Login successful!" << endl;
                    }
                } catch (const invalid_argument& ex) {
                    cout << "Error: " << ex.what() << endl;
                }
                break;
            }

            case 3:
                cout << "Thank you for using the User Management System. Goodbye!" << endl;
                break;

            default:
                cout << "Error: Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 3);

    return 0;
}
