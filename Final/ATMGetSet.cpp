//
// Created by ngo kiyo on 13/12/2023.
//
#include "header/ATM.h"

using namespace std;

void ATM::setID(string ID_) {
    this->ID = ID_;
}

string ATM::getID(){
    return this->ID;
}

void ATM::setPIN(int PIN_) {
    this->PIN = PIN_;
}

int ATM::getPIN(){
    return this->PIN;
}

void ATM::setBalance(double balance_){
    this->balance = balance_;
}

double ATM::getBalance(){
    return this->balance;
}

void ATM::setFriends(string Friend_){
    this->friendsAccount[this->friendNumber] = Friend_;
    this->friendNumber++;
}

string* ATM::getFriends(){
    return this->friendsAccount;
}