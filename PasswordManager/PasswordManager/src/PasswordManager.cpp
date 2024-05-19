#include "PasswordManager.hpp"
#include <string>

String PasswordManager::password = "";

void PasswordManager::SetPassword(String pass){
    PasswordManager::password = pass;
}

bool PasswordManager::CheckPassword(String pass){
    return pass == PasswordManager::password;
}