#ifndef PASSWORDMANAGER_HPP
#include <string>

class PasswordManager{
    public:
        static void SetPassword(String pass);
        static bool CheckPassword(String pass);
    private:
        static String password;
};
#endif