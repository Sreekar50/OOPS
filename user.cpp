class User{
protected:
    string userId;
    string name;

public:
    User(string userId, string name) : userId(userId), name(name) {}

    virtual void displayUser() const = 0;

    string getUserId() const{
        return userId;
    }

    string getName() const{
        return name;
    }
};

class Member : public User{
public:
    Member(string userId, string name) : User(userId, name) {}

    void displayUser() const override {
        cout << "Member ID: " << userId << ", Name: " << name << endl;
    }
};

class Staff : public User{
public:
    Staff(string userId, string name) : User(userId, name) {}

    void displayUser() const override {
        cout << "Staff ID: " << userId << ", Name: " << name << endl;
    }
};
