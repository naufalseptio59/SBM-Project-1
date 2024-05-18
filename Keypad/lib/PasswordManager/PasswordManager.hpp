#ifndef PASSWORDMANAGER_HPP
#include <string>

class PasswordManager{
    public:
        static void SetPassword(std::string pass);
        static bool CheckPassword(std::string pass);
        PasswordManager();
    private:
        static std::string password;
};
#endif