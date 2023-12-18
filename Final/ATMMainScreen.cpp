//
// Created by ngo kiyo on 13/12/2023.
//
#include <iostream>
#include "header/ATM.h"
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
                this->transferMoney();
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
    //check if the balance is enough for a withdraw
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

void ATM::transferMoney(){
    cout << " === Enter userID to transfer money to: === " << endl;
    string transferID;
    cin >> transferID;
    cout << "*Enter the money to transfer: " ;
    int change;
    cin >> change;
    if(this->getBalance() - change < 0){
        cout << "/Error! Not Enough Money!/ \n";
        this->pauseScreen();
        return;
    }
    string tracebackID = this->getID();
    writeNewBalance(transferID, -change);
    writeNewBalance(tracebackID, change);
    cout << " === Successfully transfer $" << change << " to ID: " << transferID << " === \n";
}


void ATM::createFile(string IDread){
    string dirID = "../resources/userID/" + IDread + ".txt";
    ofstream outputFile(dirID);
    outputFile << this->getPIN() << " " << this->getBalance() << endl;
    outputFile.close();
}


void ATM::writeNewBalance(string IDread, double newBalance) {
    ofstream outputFile;
    string dirID = "../resources/userID/" + IDread + ".txt";
    //update the user's info to current ATM
    this->checkCredential(IDread, false);
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