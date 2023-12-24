//
// Created by ngo kiyo on 13/12/2023.
//
#include <iostream>
#include "header/ATM.h"
#include <fstream>

bool ATM::mainScreen(){
    while(true) {
        cout << " === Main screen === \n"
                "1. Account Information\n"
                "2. Withdraw money\n"
                "3. Deposit money\n"
                "4. Transfer money\n"
                "5. Logout\n";
        int mainChoice;
        cin >> mainChoice;
        switch (mainChoice) {
            case 1: {
                this->accountInformation();
                break;
            }
            case 2: {
                cout << " === How much money do you want to withdraw? === \n"
                        "1. $10\n"
                        "2. $20\n"
                        "3. $50\n"
                        "4. $100\n"
                        "5. Other\n";
                int withdrawChoice;
                double money = 0;
                cin >> withdrawChoice;
                while(money <= 0) {
                    switch (withdrawChoice) {
                        case 1:
                            money = 10;
                            break;
                        case 2:
                            money = 20;
                            break;
                        case 3:
                            money = 50;
                            break;
                        case 4:
                            money = 100;
                            break;
                        case 5:
                            cout << "Enter the amount:";
                            cin >> money;
                            while(money <= 0){
                                cout << "/Invalid quantity. Please re-enter: / \n";
                                cin.clear();
                                cin.ignore(100000, '\n');
                                cin >> money;
                            }
                            break;
                        default:
                            cout << "/Invalid choice. Please re-enter: / \n";
                            cin.clear();
                            cin.ignore(100000, '\n');
                            cin >> withdrawChoice;
                    }
                }
                this->transaction(money);
                break;
            }
            case 3: {
                int moneyDepo;
                cout << "Enter the amount:";
                cin >> moneyDepo;
                while(moneyDepo <= 0){
                    cout << "/Invalid quantity. Please re-enter: / \n";
                    cin.clear();
                    cin.ignore(100000, '\n');
                    cin >> moneyDepo;
                }
                this->transaction(-moneyDepo);
                break;
            }
            case 4: {
                //print out user's friendlist
                cout << "*Friend list: \n";
                for(string* i = this->getFriends(); i - this->getFriends() < 10; i++){
                    cout << *i << " ";
                }
                cout << "\n(You can also transfer money to people outside of your friendlist)\n";
                //get destined user's id
                cout << " === Enter userID to transfer money to: === " << endl;
                string transferID;
                cin >> transferID;
                //input validation for self id entering
                while(transferID == this->getID()){
                    cout << "/Transferring money to yourself is not allowed! Re-enter: /\n";
                    cin >> transferID;
                }
                cout << "*Enter the money to transfer: " ;
                int change;
                cin >> change;
                this->transferMoney(transferID, change);
                break;
            }
            case 5: {
                cout << " === Successfully logged out === \n";
                return true;
            }
            default: {
                cout << "/Invalid input, please re-enter!/ \n";
                cin.clear();
                cin.ignore(100000, '\n');
                break;
            }
        }
    }
}

void ATM::accountInformation(){
    this->checkCredential(this->getID(), false);
    cout << " === Account Information === \n"
            "* ID: " << this->getID() << endl <<
            "* Balance: " << "$" << setprecision(10) << this->getBalance() << endl <<
            "* Friends list's accounts: " ;
            for(string* i = this->getFriends(); i - this->getFriends() < 10; i++){
                cout << *i << " ";
            }
    cout << "\n";
    this->pauseScreen();
}

void ATM::transaction(double change) {
    //check if the balance is enough for a withdrawal
    if(this->getBalance() - change < 0){
        cout << "/Error! Not Enough Money!/ \n";
        this->pauseScreen();
        return;
    }
    //make change to balance
    this->writeNewBalance(this->getID(), change);
    //print transaction message
    cout << " === Successful, account " << this->getID();
    if(change < 0) cout << " deposited $" << -change;
    else if(change >0) cout << " withdrawn -$" << change;
    cout << "! === \n ";
    //update new values to ATM
    this->checkCredential(this->getID(), false);
    cout << "* Remaining balance: $" << this->getBalance() << "\n";
    this->pauseScreen();
}

void ATM::transferMoney(string transferID, int change) {
    string tracebackID = this->getID();
    while(change <= 0){
        cout << "/Invalid quantity. Please re-enter: / \n";
        cin.clear();
        cin.ignore(100000, '\n');
        cin >> change;
    }
    if(this->getBalance() - change < 0){
        cout << "/Error! Not Enough Money!/ \n";
        this->pauseScreen();
        return;
    }
    writeNewBalance(transferID, -change);
    cout << " === Successfully transfer $" << change << " to ID: " << this->getID() << " === \n";
    writeNewBalance(tracebackID, change);
    checkCredential(tracebackID, false);
    cout << "*Current balance: $" << this->getBalance() << endl;
    this->pauseScreen();
}


void ATM::writeNewBalance(string IDread, double newBalance) {
    //update ATM's info
    this->checkCredential(IDread, false);
    ofstream outputFile;
    string dirID = "../resources/userID/" + this->getID() + ".txt";
    //clear file's content
    outputFile.open(dirID,std::ofstream::out | std::ofstream::trunc);
    outputFile.close();
    //input in new content for the file
    outputFile.open(dirID, ios::in);
    outputFile << this->getPIN() << " ";
    outputFile << this->getBalance() - newBalance << endl;
    for(string* test1 = this->getFriends(); test1 - (this->getFriends()) < 10; test1++){
        outputFile << *(test1) << endl;
    }
    outputFile.close();
}