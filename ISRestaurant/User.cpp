#include "JsonHelper.h"
#include "Product.h"
#include "Menu.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <iomanip>
#define NOMINMAX
#include <windows.h>

using namespace std;


void User::editingEmployees() {
    system("cls");

    int choice;

    while (true) {
        cout << "�������������� ������� �������:\n";
        cout << "1. ��������\n";
        cout << "2. ��������\n";
        cout << "3. �������\n";
        cout << "4. �����\n";
        cout << "�������� ��������: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "������������ �����. ���������� ��� ���." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            addEmployees();
            break;
        case 2:
            editEmployees();
            break;
        case 3:
            removeEmployees();
            break;
        case 4:
            system("cls");
            return;  
        default:
            cout << "������������ �����. ���������� ��� ���." << endl;
            break;
        }
    }
}
void User::addEmployees()
{
    JsonHelper jsonHelper;
    system("cls");

    // ��������� ������ �� �����
    json jsonData = jsonHelper.readJsonData("users.json");

    std::string firstName, lastName, patronymic, username, password, role;

    std::cout << "���������� ������ ����������:\n";

    // ���� ������ ����������
    std::cout << "���: ";
    std::cin.ignore();
    std::getline(std::cin, firstName);

    std::cout << "�������: ";
    std::getline(std::cin, lastName);

    std::cout << "��������: ";
    std::getline(std::cin, patronymic);

    std::cout << "�����: ";
    std::getline(std::cin, username);

    std::cout << "������: ";
    std::getline(std::cin, password);

    std::cout << "����: ";
    std::getline(std::cin, role);

    // �������� ������� ����������
    json newEmployee;
    newEmployee["firstName"] = firstName;
    newEmployee["lastName"] = lastName;
    newEmployee["patronymic"] = patronymic;
    newEmployee["username"] = username;
    newEmployee["password"] = password;
    newEmployee["role"] = role;

    // ���������� ������ ���������� � ������
    jsonData["users"].push_back(newEmployee);

    // ��������� ����������� ������ � ����
    jsonHelper.writeJsonData("users.json", jsonData);

    std::cout << "��������� ������� ��������.\n";
    Sleep(1500);
    system("cls");
}
void User::editEmployees()
{
    JsonHelper jsonHelper;
    system("cls");
    // ��������� ������ �� �����
    json jsonData = jsonHelper.readJsonData("users.json");

    // ������� ������ �����������
    std::cout << "������ �����������:\n";
    for (const auto& user : jsonData["users"]) {
        std::cout << "���: " << user["firstName"] << std::endl;
        std::cout << "�������: " << user["lastName"] << std::endl;
        std::cout << "��������: " << user["patronymic"] << std::endl;
        std::cout << "�����: " << user["username"] << std::endl;
        std::cout << "������: " << user["password"] << std::endl;
        std::cout << "����: " << user["role"] << std::endl;
        std::cout << "-----------------------\n";
    }

    // �������� ����� ����������, �������� ����� �������������
    std::string editUsername;
    std::cout << "������� ����� ���������� ��� ��������������: ";
    std::cin.ignore();
    std::getline(std::cin, editUsername);

    // ����� ���������� � ��������� �������
    bool found = false;
    for (auto& user : jsonData["users"]) {
        if (user["username"] == editUsername) {
            found = true;
            std::string firstName, lastName, patronymic, newUsername, newPassword, newRole;

            std::cout << "�������������� ������ ����������:\n";

            // �������������� ���
            std::cout << "����� ���: ";
            std::getline(std::cin, firstName);
            user["firstName"] = firstName;

            std::cout << "����� �������: ";
            std::getline(std::cin, lastName);
            user["lastName"] = lastName;

            std::cout << "����� ��������: ";
            std::getline(std::cin, patronymic);
            user["patronymic"] = patronymic;

            // �������������� ������
            std::cout << "����� �����: ";
            std::getline(std::cin, newUsername);
            user["username"] = newUsername;

            // �������������� ������
            std::cout << "����� ������: ";
            std::getline(std::cin, newPassword);
            user["password"] = newPassword;

            // �������������� ����
            std::cout << "����� ����: ";
            std::getline(std::cin, newRole);
            user["role"] = newRole;

            std::cout << "������ ���������� ������� ���������.\n";
            break;
        }
    }

    // ��������� ����������� ������ � ����
    if (found) {
        jsonHelper.writeJsonData("users.json", jsonData);
        Sleep(1500);
        system("cls");
    }
    else {
        std::cout << "��������� � ��������� ������� �� ������.\n";
        Sleep(1500);
        system("cls");
    }
}
void User::removeEmployees()
{
    JsonHelper jsonHelper;
    system("cls");
    // ��������� ������ �� �����
    json jsonData = jsonHelper.readJsonData("users.json");

    // ������� ������ �����������
    std::cout << "������ �����������:\n";
    for (const auto& user : jsonData["users"]) {
        std::cout << "���: " << user["firstName"] << std::endl;
        std::cout << "�������: " << user["lastName"] << std::endl;
        std::cout << "��������: " << user["patronymic"] << std::endl;
        std::cout << "�����: " << user["username"] << std::endl;
        std::cout << "������: " << user["password"] << std::endl;
        std::cout << "����: " << user["role"] << std::endl;
        std::cout << "-----------------------\n";
    }

    // �������� ����� ����������, �������� ����� �������������
    std::string deleteUsername;
    std::cout << "������� ����� ���������� ��� ��������: ";
    std::cin.ignore();
    std::getline(std::cin, deleteUsername);

    // ����� ���������� � ��������� �������
    bool found = false;
    size_t index = 0;
    while (index < jsonData["users"].size()) {
        if (jsonData["users"][index]["username"] == deleteUsername) {
            found = true;
            jsonData["users"].erase(jsonData["users"].begin() + index);
            std::cout << "��������� ������� ������.\n";
            break;
        }
        else {
            index++;
        }
    }

    // ��������� ����������� ������ � ����
    if (found) {
        jsonHelper.writeJsonData("users.json", jsonData);
        Sleep(1500);
        system("cls");
    }
    else {
        std::cout << "��������� � ��������� ������� �� ������.\n";
        Sleep(1500);
        system("cls");
    }
}


void User::guestMenu() {
    cout << "���� �����" << endl;
    // �������� ���������������� ��� ���� �����
}

void User::adminMenu() {
    int choice;
    Menu menu;
    Product product;

    while (true) {
        cout << "�������������:\n";
        cout << "1. ����\n";
        cout << "2. ������ ���������\n";
        cout << "3. ������� ������\n";
        cout << "4. �����\n";
        cout << "�������� ��������: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "������������ �����. ���������� ��� ���." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            menu.editMenu();
            break;
        case 2:
            product.editingProducts();
            break;
        case 3:
            editingEmployees();
            break;
        case 4:
            return;  // ����� �� ������� adminMenu() � ������� � ����� ������
        default:
            cout << "������������ �����. ���������� ��� ���." << endl;
            break;
        }
    }
}

void User::skladMenu() {
    system("cls");
    int choice;

    while (true) {
        cout << "1. ������� ������\n";
        cout << "1. ���������� �����\n";
        cout << "�������� ��������: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "������������ �����. ���������� ��� ���." << endl;
            cin.clear();
            system("cls");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        Menu menu;

        switch (choice) {
        case 1:
            menu.addDish();
            menu.editMenu();
            break;
        case 2:
            menu.removeDish();
            return;
            break;
        case 3:
            menu.editDish();
            return;
            break;
        case 4:
            return;  // ����� �� ������� editMenu() � ������� � ����������� ����
        default:
            cout << "������������ �����. ���������� ��� ���." << endl;
            system("cls");
            break;
        }
    }
}


