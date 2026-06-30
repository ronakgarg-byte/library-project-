#include <iostream>
#include <string>
using namespace std;

const int MAX_CAPACITY = 100;

class Book {
public:
    int book_id;
    string title;
    string author;
    bool isIssued = false;       // Track if the book is checked out
    int borrowedByUserId = -1;   // Track who has it (-1 means nobody)
};

class User {
public:
    string name;
    int user_id;
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
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Book libraryBooks[MAX_CAPACITY];
    User libraryUsers[MAX_CAPACITY];
    int bookCount = 0;
    int userCount = 0;
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            if (bookCount >= MAX_CAPACITY) {
                cout << "\nError: Library storage is full!" << endl;
            } else {
                cout << "\nEnter Book ID: ";
                cin >> libraryBooks[bookCount].book_id;
                cin.ignore();
                cout << "Enter Title: ";
                getline(cin, libraryBooks[bookCount].title);
                cout << "Enter Author: ";
                getline(cin, libraryBooks[bookCount].author);
                
                libraryBooks[bookCount].isIssued = false; // Freshly added book is available
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
                cin >> libraryUsers[userCount].user_id;
                cin.ignore();
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
            // Issue / Borrow Book
            int targetBookId, targetUserId;
            cout << "\nEnter Book ID to borrow: ";
            cin >> targetBookId;
            cout << "Enter your User ID: ";
            cin >> targetUserId;

            // 1. Check if the user exists
            bool userExists = false;
            for (int i = 0; i < userCount; i++) {
                if (libraryUsers[i].user_id == targetUserId) {
                    userExists = true;
                    break;
                }
            }

            if (!userExists) {
                cout << "\nError: User ID not found! Register the user first." << endl;
                continue; // Skips the rest of this loop iteration and goes back to menu
            }

            // 2. Find the book and process transaction
            bool bookFound = false;
            for (int i = 0; i < bookCount; i++) {
                if (libraryBooks[i].book_id == targetBookId) {
                    bookFound = true;
                    if (libraryBooks[i].isIssued) {
                        cout << "\nError: This book is already borrowed by User ID " 
                             << libraryBooks[i].borrowedByUserId << "!" << endl;
                    } else {
                        libraryBooks[i].isIssued = true;
                        libraryBooks[i].borrowedByUserId = targetUserId;
                        cout << "\n--- Book successfully issued to User " << targetUserId << "! ---" << endl;
                    }
                    break;
                }
            }

            if (!bookFound) {
                cout << "\nError: Book ID not found!" << endl;
            }
        }
        else if (choice == 6) {
            // Return Book
            int targetBookId;
            cout << "\nEnter Book ID to return: ";
            cin >> targetBookId;

            bool bookFound = false;
            for (int i = 0; i < bookCount; i++) {
                if (libraryBooks[i].book_id == targetBookId) {
                    bookFound = true;
                    if (!libraryBooks[i].isIssued) {
                        cout << "\nThis book is already sitting in the library (not issued)." << endl;
                    } else {
                        libraryBooks[i].isIssued = false;
                        libraryBooks[i].borrowedByUserId = -1; // Reset to default
                        cout << "\n--- Book returned successfully! ---" << endl;
                    }
                    break;
                }
            }

            if (!bookFound) {
                cout << "\nError: Book ID not found!" << endl;
            }
        }
        else if (choice == 7) {
            cout << "\nExiting system. Goodbye!" << endl;
            break;
        }
        else {
            cout << "\nInvalid choice! Please select a valid option (1-7)." << endl;
        }
    }

    return 0;
}

