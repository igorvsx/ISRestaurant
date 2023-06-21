#pragma once

#include <string>

class User {
public:
    std::string role;
    std::string lastName;
    std::string firstName;
    std::string patronymic;
    std::string username;
    std::string password;

    // Функции меню для разных ролей
    void addProduct();
    void editProduct();
    void removeProduct();
    void guestMenu();
    void skladMenu();
    void adminMenu();
    void editMenu();
    void editProductList();
    void editEmployees();
};
