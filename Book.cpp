#include <iostream>
#include <string>
using namespace std;

class Book{
private:
    string id;
    string title;
    string author;
    bool isAvailable;

public:
    Book(string id, string title, string author) : id(id), title(title), author(author), isAvailable(true) {}

    string getId() const {
        return id;
    }

    string getTitle() const{
        return title;
    }

    string getAuthor() const{
        return author;
    }

    bool getAvailability() const {
        return isAvailable;
    }

    void setAvailability(bool availability){
        isAvailable = availability;
    }

    void displayBook() const {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};
