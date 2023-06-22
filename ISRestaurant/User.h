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

    // ������� ���� ��� ������ �����
    void guestMenu();
    void skladMenu();
    void adminMenu();
    void editEmployees();
    void addEmployees();
    void removeEmployees();
    void editingEmployees();
};