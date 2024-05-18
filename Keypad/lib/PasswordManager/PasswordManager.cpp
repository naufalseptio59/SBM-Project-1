#include <string>
#include "PasswordManager.hpp"

std::string PasswordManager::password = "";

void PasswordManager::SetPassword(std::string pass){
    PasswordManager::password = pass;
}

bool PasswordManager::CheckPassword(std::string pass){
    return pass == PasswordManager::password;
}

PasswordManager::PasswordManager(){
    PasswordManager::password = "";
}