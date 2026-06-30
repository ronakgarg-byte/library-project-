#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int MAX_CAPACITY = 100;

class Book {
public:
    int book_id;
    string title;
    string author;
    bool isIssued = false;
    int borrowedByUserId = -1;
};

class User {
public:
    int user_id;
    string name;
};

void displayMenu() {
    cout << "\n-----------------------------" << endl;
    cout << "      LIBRARY MANAGEMENT       " << endl;
    cout << "-------------------------------" << endl;
    cout << "1. Add Book Details" << endl;
    cout << "2. View Book Details" << endl;
    cout << "3. Add User Details" << endl;
    cout << "4. View User Details" << endl;
    cout << "5. Issue / Borrow Book" << endl;
    cout << "6. Return Book" << endl;
    cout << "7. Delete Book" << endl;
    cout << "8. Delete User" << endl;
    cout << "9. Exit" << endl;
    cout << "Enter your choice: ";
}

bool getValidInteger(int &outputNum) {
    string rawInput;
    getline(cin, rawInput);

    if (rawInput.empty()) {
        return false;
    }

    stringstream ss(rawInput);
    if (ss >> outputNum && ss.eof()) {
        return true;
    }
    return false;
}

int findBookIndex(Book books[], int count, int targetId) {
    for (int i = 0; i < count; i++) {
        if (books[i].book_id == targetId) {
            return i;
        }
    }
    return -1;
}

int findUserIndex(User users[], int count, int targetId) {
    for (int i = 0; i < count; i++) {
        if (users[i].user_id == targetId) {
            return i;
        }
    }
    return -1;
}

int main() {
    Book libraryBooks[MAX_CAPACITY];
    User libraryUsers[MAX_CAPACITY];
    int bookCount = 0;
    int userCount = 0;
    int choice;

    while (true) {
        displayMenu();

        if (!getValidInteger(choice)) {
            cout << "\nError: Invalid choice! Please enter a number from 1 to 9." << endl;
            continue;
        }

        if (choice == 1) {
            if (bookCount >= MAX_CAPACITY) {
                cout << "\nError: Library storage is full!" << endl;
            } else {
                cout << "\nEnter Book ID: ";
                if (!getValidInteger(libraryBooks[bookCount].book_id)) {
                    cout << "Error: Book ID must be an integer only!" << endl;
                    continue;
                }

                cout << "Enter Title: ";
                getline(cin, libraryBooks[bookCount].title);
                cout << "Enter Author: ";
                getline(cin, libraryBooks[bookCount].author);

                libraryBooks[bookCount].isIssued = false;
                libraryBooks[bookCount].borrowedByUserId = -1;

                bookCount++;
                cout << "--- Book added successfully! ---" << endl;
            }
        }
        else if (choice == 2) {
            if (bookCount == 0) {
                cout << "\nNo books available in the library yet." << endl;
            } else {
                cout << "\n--- Current Book Details ---" << endl;
                for (int i = 0; i < bookCount; i++) {
                    cout << "ID: " << libraryBooks[i].book_id
                         << " | Title: " << libraryBooks[i].title
                         << " | Author: " << libraryBooks[i].author;

                    if (libraryBooks[i].isIssued) {
                        cout << " [ISSUED to User ID: " << libraryBooks[i].borrowedByUserId << "]" << endl;
                    } else {
                        cout << " [AVAILABLE]" << endl;
                    }
                }
            }
        }
        else if (choice == 3) {
            if (userCount >= MAX_CAPACITY) {
                cout << "\nError: User database is full!" << endl;
            } else {
                cout << "\nEnter User ID: ";
                if (!getValidInteger(libraryUsers[userCount].user_id)) {
                    cout << "Error: User ID must be an integer only!" << endl;
                    continue;
                }

                cout << "Enter User Name: ";
                getline(cin, libraryUsers[userCount].name);

                userCount++;
                cout << "--- User added successfully! ---" << endl;
            }
        }
        else if (choice == 4) {
            if (userCount == 0) {
                cout << "\nNo users registered yet." << endl;
            } else {
                cout << "\n--- Current User Details ---" << endl;
                for (int i = 0; i < userCount; i++) {
                    cout << "User ID: " << libraryUsers[i].user_id
                         << " | Name: " << libraryUsers[i].name << endl;
                }
            }
        }
        else if (choice == 5) {
            int targetBookId, targetUserId;
            cout << "\nEnter Book ID to borrow: ";
            if (!getValidInteger(targetBookId)) {
                cout << "Error: Book ID must be an integer only!" << endl;
                continue;
            }

            cout << "Enter your User ID: ";
            if (!getValidInteger(targetUserId)) {
                cout << "Error: User ID must be an integer only!" << endl;
                continue;
            }

            int userIndex = findUserIndex(libraryUsers, userCount, targetUserId);
            if (userIndex == -1) {
                cout << "\nError: User ID not found! Register the user first." << endl;
                continue;
            }

            int bookIndex = findBookIndex(libraryBooks, bookCount, targetBookId);
            if (bookIndex == -1) {
                cout << "\nError: Book ID not found!" << endl;
            } else if (libraryBooks[bookIndex].isIssued) {
                cout << "\nError: This book is already borrowed by User ID "
                     << libraryBooks[bookIndex].borrowedByUserId << "!" << endl;
            } else {
                libraryBooks[bookIndex].isIssued = true;
                libraryBooks[bookIndex].borrowedByUserId = targetUserId;
                cout << "\n--- Book successfully issued to User " << targetUserId << "! ---" << endl;
            }
        }
        else if (choice == 6) {
            int targetBookId;
            cout << "\nEnter Book ID to return: ";
            if (!getValidInteger(targetBookId)) {
                cout << "Error: Book ID must be an integer only!" << endl;
                continue;
            }

            int bookIndex = findBookIndex(libraryBooks, bookCount, targetBookId);
            if (bookIndex == -1) {
                cout << "\nError: Book ID not found!" << endl;
            } else if (!libraryBooks[bookIndex].isIssued) {
                cout << "\nThis book is already sitting in the library (not issued)." << endl;
            } else {
                libraryBooks[bookIndex].isIssued = false;
                libraryBooks[bookIndex].borrowedByUserId = -1;
                cout << "\n--- Book returned successfully! ---" << endl;
            }
        }
        else if (choice == 7) {
            int targetBookId;
            cout << "\nEnter Book ID to delete: ";
            if (!getValidInteger(targetBookId)) {
                cout << "Error: Book ID must be an integer only!" << endl;
                continue;
            }

            int bookIndex = findBookIndex(libraryBooks, bookCount, targetBookId);
            if (bookIndex == -1) {
                cout << "\nError: Book ID not found!" << endl;
            } else if (libraryBooks[bookIndex].isIssued) {
                cout << "\nCannot delete this book because it is currently issued. Return it first." << endl;
            } else {
                for (int i = bookIndex; i < bookCount - 1; i++) {
                    libraryBooks[i] = libraryBooks[i + 1];
                }
                bookCount--;
                cout << "\n--- Book deleted successfully! ---" << endl;
            }
        }
        else if (choice == 8) {
            int targetUserId;
            cout << "\nEnter User ID to delete: ";
            if (!getValidInteger(targetUserId)) {
                cout << "Error: User ID must be an integer only!" << endl;
                continue;
            }

            int userIndex = findUserIndex(libraryUsers, userCount, targetUserId);
            if (userIndex == -1) {
                cout << "\nError: User ID not found!" << endl;
            } else {
                bool hasIssuedBook = false;
                for (int i = 0; i < bookCount; i++) {
                    if (libraryBooks[i].isIssued && libraryBooks[i].borrowedByUserId == targetUserId) {
                        hasIssuedBook = true;
                        break;
                    }
                }

                if (hasIssuedBook) {
                    cout << "\nCannot delete this user because they still have issued books." << endl;
                } else {
                    for (int i = userIndex; i < userCount - 1; i++) {
                        libraryUsers[i] = libraryUsers[i + 1];
                    }
                    userCount--;
                    cout << "\n--- User deleted successfully! ---" << endl;
                }
            }
        }
        else if (choice == 9) {
            cout << "\nExiting system. Goodbye!" << endl;
            break;
        }
        else {
            cout << "\nInvalid choice! Please select a valid option (1-9)." << endl;
        }
    }

    return 0;
}
