//
// Created by ngo kiyo on 13/12/2023.
//
#include <iostream>
#include "header/ATM.h"
#include <string>
#include <fstream>

bool ATM::mainScreen(){
    while(true) {
        cout << "1. Account Information\n"
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
                            if(money <= 0){
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
                this->alterBalance(money);
                break;
            }
            case 3: {
                int moneyDepo;
                cout << "Enter the amount:";
                cin >> moneyDepo;
                if(moneyDepo <= 0){
                    cout << "/Invalid quantity. Please re-enter: / \n";
                    cin.clear();
                    cin.ignore(100000, '\n');
                    cin >> moneyDepo;
                }
                alterBalance(-moneyDepo);
                break;
            }
            case 4: {
                break;
            }
            case 5: {
                cout << " === Successfully logged out === \n";
                return false;
            }
        }
    }
}

void ATM::accountInformation(){
    cout << " === Account Information === \n"
            "* ID: " << this->getID() << endl <<
         "* Balance: " << "$" << setprecision(10) << this->getBalance() << endl <<
         "* Friends list's accounts: " << this->getFriends() << endl;
    this->pauseScreen();
}
void ATM::alterBalance(double change){
    ofstream outputFile;
    string dirID = "../resources/userID/" + this->getID() + ".txt";
    outputFile.open(dirID, ios::in);
    if(this->getBalance() - change < 0){
        cout << "/Error! Not Enough Money!/ \n";
        this->pauseScreen();
        return;
    }
    double newBalance = this->getBalance() - change;
    outputFile.seekp(7, std::ios::cur);
    outputFile << newBalance;
    outputFile << "    \n";
    outputFile.close();
    cout << " === Successful, account " << this->getID();
    if(change < 0) cout << " added $" << change;
    else if(change >0) cout << " withdraw $" << -change;
    cout << "! === \n ";
    this->checkCredential(this->getID(), this->getPIN());
    cout << "* Remaining balance: $" << this->getBalance() << "\n";
    this->pauseScreen();
}


void ATM::createFile(string readID){
    string dirID = "../resources/userID/" + readID + ".txt";
    ofstream outputFile(dirID);
    outputFile << this->getPIN() << " " << this->getBalance() << endl;
    outputFile.close();
}