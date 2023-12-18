//
// Created by ngo kiyo on 12/12/2023.
//
#include <iostream>
#include "header/ATM.h"
#include <fstream>

int ATM::loginScreen(bool loginStatus) {
    cout << "=== Welcome! === \n";
    while (loginStatus) {
        cout << "1. Login:\n"//user will be asked for ID and PIN. Unsuccessful login returns user to the main menu.
                "2. Create new account:\n"//user will be given a random ID (10 characters string) and set his/her own password. the initial balance is 0.
                "3. Exit:\n";
        int loginScreenChoice;
        cin >> loginScreenChoice;
        switch (loginScreenChoice) {
            case 1: {
                cout << " === Login === \n";
                string IDlog;
                cout << "Enter your ID: ";
                cin >> IDlog;
                if(this->checkCredential(IDlog, true)){
                    cout << " === Successfully logged in! === \n";
                    loginStatus = this->mainScreen();
                } else {this->loginScreen(true);}
                break;
            }
            case 2: {
                cout << " === Creating account... === \n";
                this->createAccount();
                break;
            }
            case 3: {
                cout << " === GOODBYE === ";
                exit(0);
            }
            default: {
                cout << "/Invalid input, please re-enter!/ \n";
                cin.clear();
                cin.ignore(100000, '\n');
                break;
            }
        }
    }
    return 0;
}

bool ATM::checkCredential(string readID, bool needPIN) {
    ifstream inputFile;
    //get user's ID file from directory
    string dirID = "../resources/userID/" + readID + ".txt";
    // Open user's ID file, re-input if incorrect
    inputFile.open(dirID, ios::in);
    while (!inputFile.is_open()) {
        cout << "/Error can't find ID, please re-enter!/" << endl <<
             "Enter your ID: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin >> readID;
        dirID = "../resources/userID/" + readID + ".txt";
        inputFile.open(dirID, ios::in);
    }
    setID(readID);
    double fileBalance;
    int filePIN, count = 0;
    string idFriend;
    //read first line consist of PIN + balance
    inputFile >> filePIN >> fileBalance;
    // Check if user PIN is correct, if wrong re-ask
    if(needPIN) {
        cout << "Enter your PIN number: ";
        int readPIN;
        cin >> readPIN;
        while (readPIN != filePIN) {
            //assign PIN, balance, friendList to running ATM
            cout << "/Incorrect PIN, please re-enter: /\n";
            cin.clear();
            cin.ignore(10000, '\n');
            if (count == 5) return false;
            cin >> readPIN;
            count++;
        }
    }
    this->setPIN(filePIN);
    this->setBalance(fileBalance);
    this->setFriendNumber(0);
    while (inputFile >> idFriend) {
        this->setFriends(idFriend);
    }
    inputFile.close();
    return true;
}

void ATM::createAccount(){
    //Creating a string of 10 random characters
    const char rAlpha[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char rNum[] =
            "0123456789";
    string newID;
    newID.reserve(10);
    srand (time(NULL));
    for (int i = 0; i < 2; ++i) {
        newID += rAlpha[rand() % (sizeof(rAlpha) - 1)];
    }
    for (int i = 0; i < 8; ++i) {
        newID += rNum[rand() % (sizeof(rNum) - 1)];
    }

    cout << "* Your new account's ID is (Make sure to note it down!): " << newID << "\n";
    this->setID(newID);
    cout << "Enter your account's PIN (Enter a positive 6-digits number): ";
    int newPIN;
    cin >> newPIN;
    //User input PIN
    while(true) {
        if (newPIN >= 100000 && newPIN <= 999999) {
            this->setPIN(newPIN);
            this->setBalance(0);
            this->createFile(this->getID());
            cout << " === Account created! === \n";
            this->pauseScreen();
            return;
        } else {
            cout << "Invalid! enter a positive 6-digits number: ";
            cin.clear();
            cin.ignore(1000000, '\n');
            cin >> newPIN;
        }
    }
}

void ATM::pauseScreen(){
    cout << " === Press any key to return === \n";
    char key;
    cin >> key;
    cin.clear();
    cin.ignore(100000, '\n');
}