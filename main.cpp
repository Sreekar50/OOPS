#include <iostream>
#include <thread>
using namespace std;

void issueBookThread(Library& library, string bookId, string userId){
    try {
        library.issueBook(bookId, userId);
        cout << "Book issued successfully!" << endl;
    } catch (LibraryException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

int main(){
    Library library;

    // Adding sample data
    library.addBook(Book("B1", "The Great Gatsby", "F. Scott Fitzgerald"));
    library.addBook(Book("B2", "1984", "George Orwell"));
    library.addUser(new Member("M1", "Alice"));
    library.addUser(new Staff("S1", "Bob"));

    int choice;
    do {
        cout << "Library Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Add User" << endl;
        cout << "3. Issue Book" << endl;
        cout << "4. Return Book" << endl;
        cout << "5. Display Books" << endl;
        cout << "6. Display Users" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string id, title, author;
                cout << "Enter Book ID: ";
                cin >> id;
                cout << "Enter Title: ";
                cin >> title;
                cout << "Enter Author: ";
                cin >> author;
                library.addBook(Book(id, title, author));
                break;
            }
            case 2: {
                int userType;
                string userId, name;
                cout << "Enter User ID: ";
                cin >> userId;
                cout << "Enter Name: ";
                cin >> name;
                cout << "Enter User Type (1 for Member, 2 for Staff): ";
                cin >> userType;
                if (userType == 1) {
                    library.addUser(new Member(userId, name));
                } else {
                    library.addUser(new Staff(userId, name));
                }
                break;
            }
            case 3: {
                string bookId, userId;
                cout << "Enter Book ID: ";
                cin >> bookId;
                cout << "Enter User ID: ";
                cin >> userId;
                thread t(issueBookThread, ref(library), bookId, userId);
                t.join();
                break;
            }
            case 4: {
                string bookId, userId;
                cout << "Enter Book ID: ";
                cin >> bookId;
                cout << "Enter User ID: ";
                cin >> userId;
                try {
                    library.returnBook(bookId, userId);
                    cout << "Book returned successfully!" << endl;
                } catch (LibraryException& e) {
                    cout << "Error: " << e.what() << endl;
                }
                break;
            }
            case 5: {
                library.displayBooks();
                break;
            }
            case 6: {
                library.displayUsers();
                break;
            }
            case 7: {
                cout << "Exiting..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    } while (choice != 7);

    return 0;
}
