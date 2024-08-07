#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <exception>

class LibraryException : public exception{
private:
    string message;
public:
    LibraryException(string message) : message(message) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class LibraryInterface{
public:
    virtual void addBook(Book book) = 0;
    virtual void addUser(User* user) = 0;
    virtual void issueBook(string bookId, string userId) = 0;
    virtual void returnBook(string bookId, string userId) = 0;
    virtual void displayBooks() const = 0;
    virtual void displayUsers() const = 0;
};

class Library : public LibraryInterface{
private:
    vector<Book> books;
    vector<User*> users;
    map<string, string> issuedBooks;
    mutable mutex mtx;

public:
    void addBook(Book book) override {
        lock_guard<mutex> lock(mtx);
        books.push_back(book);
    }

    void addUser(User* user) override {
        lock_guard<mutex> lock(mtx);
        users.push_back(user);
    }

    void issueBook(string bookId, string userId) override {
        lock_guard<mutex> lock(mtx);
        for (auto& book : books) {
            if (book.getId() == bookId) {
                if (!book.getAvailability()) {
                    throw LibraryException("Book is not available");
                }
                book.setAvailability(false);
                issuedBooks[bookId] = userId;
                return;
            }
        }
        throw LibraryException("Book not found");
    }

    void returnBook(string bookId, string userId) override{
        lock_guard<mutex> lock(mtx);
        if (issuedBooks.find(bookId) == issuedBooks.end() || issuedBooks[bookId] != userId) {
            throw LibraryException("Book not issued to this user");
        }
        for (auto& book : books) {
            if (book.getId() == bookId) {
                book.setAvailability(true);
                issuedBooks.erase(bookId);
                return;
            }
        }
    }

    void displayBooks() const override{
        lock_guard<mutex> lock(mtx);
        for (const auto& book : books) {
            book.displayBook();
        }
    }

    void displayUsers() const override{
        lock_guard<mutex> lock(mtx);
        for (const auto& user : users) {
            user->displayUser();
        }
    }
};
