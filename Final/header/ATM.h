#ifndef FINAL_ATM_H
#define FINAL_ATM_H

#include <string>
using namespace std;

class ATM{
private:
    string ID;
    int PIN;
    double balance;
    string friendsAccount[10];
    int friendNumber = 0;
public:
    void setID(string ID_);
    string getID();
    void setPIN(int PIN_);
    int getPIN();
    void setBalance(double Balance_);
    double getBalance();
    void setFriends(string Friend_);
    void setFriendNumber(int FriendNumber_);
    string* getFriends();
    int loginScreen(bool loginStatus);
    bool checkCredential(string IDread, bool needPIN);
    void createAccount();
    bool mainScreen();
    void accountInformation();
    void transaction(double change);
    void pauseScreen();
    void createFile(string IDread);
    void writeNewBalance(string IDread, double newBalance);
    void transferMoney(string transferID, int change);
};

#endif //FINAL_ATM_H
