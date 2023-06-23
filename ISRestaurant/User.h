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
    void guestMenu();
    void skladMenu();
    void adminMenu();
    void povarMenu();
    void supplierMenu();
    void accountantMenu();

    void editEmployees();
    void addEmployees();
    void removeEmployees();
    void editingEmployees();
    void listEmployees();
    
    void printBalance(const std::string& filename);
    void makeOrder();

    void displayPaidOrdersForCook();
    void startCooking();
};
