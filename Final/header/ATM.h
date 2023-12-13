#ifndef FINAL_ATM_H
#define FINAL_ATM_H

#include <string>
using namespace std;

class ATM{
private:
    string ID;
    int PIN;
    double balance = 0;
    string friendsAccount;
public:
    void setID(string ID_);
    string getID();
    void setPIN(int PIN_);
    int getPIN();
    void setBalance(double Balance_);
    double getBalance();
    void setFriends(string Friend_);
    string getFriends();
    int loginScreen(bool loginStatus);
    bool checkCredential(string IDread, int PINread);
    void createAccount();
    bool mainScreen();
    void accountInformation();
    void withdrawMoney(double withdraw);
//    void depositMoney();
    void pauseScreen();
    void createFile(string IDcreate);
};

#endif //FINAL_ATM_H
