#include "JsonHelper.h"
#include "Product.h"
#include "Menu.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#define NOMINMAX
#include <windows.h>
#include "Order.h"

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
        cout << "1. ���������� �����\n";
        cout << "2. ������� ������\n";
        cout << "3. �����\n";
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
        Product product;
        Order order;

        switch (choice) {
        case 1:
            product.productList();
            break;
        case 2:
            order.createOrder();
            break;
        case 3:
            return;
        default:
            cout << "������������ �����. ���������� ��� ���." << endl;
            system("cls");
            break;
        }
    }
}

void User::supplierMenu() {
    system("cls");
    int choice;

    while (true) {
        cout << "1. ���������� ������\n";
        cout << "2. �����\n";
        cout << "�������� ��������: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "������������ �����. ���������� ��� ���." << endl;
            cin.clear();
            system("cls");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            ordersList();
            break;
        case 2:
            return;
        default:
            cout << "������������ �����. ���������� ��� ���." << endl;
            system("cls");
            break;
        }
    }
}

void User::accountantMenu() {
    Order order;
    system("cls");
    int choice;

    while (true) {
        cout << "1. ���������� ������������ ������\n";
        cout << "2. ���������� �������� ��������\n";
        cout << "3. ���������� ������ ���������\n";
        cout << "4. �����\n";
        cout << "�������� ��������: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "������������ �����. ���������� ��� ���." << endl;
            cin.clear();
            system("cls");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            order.printSendOrders();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            return;
        default:
            cout << "������������ �����. ���������� ��� ���." << endl;
            system("cls");
            break;
        }
    }
}

std::string getCurrentDate() {
    std::time_t currentTime = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &currentTime);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);

    return std::string(buffer);
}


void User::ordersList() {
    JsonHelper jsonHelper;
    Order order;
    system("cls");

    // �������� ������ �� JSON-�����
    json orderData = jsonHelper.readJsonData("orders.json");
    json productsData = jsonHelper.readJsonData("products.json");
    json existingData = jsonHelper.readJsonData("DoneOrders.json");

    // �������� ������� ������
    if (orderData["orders"].empty()) {
        cout << "������ ������ ����." << endl;
        Sleep(1500);
        system("cls");
        return;
    }

    
    // ����� ������ ������
    for (const auto& orderItem : orderData["orders"]) {
        int productId = orderItem["product_id"].get<int>();
        int quantityPro = orderItem["quantity"].get<int>();

        std::cout << "������������: " << orderItem["product_name"] << std::endl;
        //std::cout << "���� �� �����: " << orderItem["price"] << std::endl;
        std::cout << "����������: " << quantityPro << std::endl;
        //std::cout << "����� ���������: " << orderItem["price"] * quantityPro << std::endl;
        std::cout << "-----------------------\n";

        // �������� ���������� � �������� �� ID �� ����� "products.json"
        /*json productData = jsonHelper.getProductData(productId);
        if (!productData.empty()) {
           
        }*/
    }

    string choice;
    double price = 0;
    int quantity = 0;
    double amount = 0;

    cout << "������� �������� �������� ��� ��������: ";
    cin >> choice;

    
    for (const auto& product : productsData["products"]) {
        if (product["name"] == choice) {
            price = product["price"].get<std::double_t>();
            break;
        }
    }

    for (const auto& order : orderData["orders"]) {
        if (order["product_name"] == choice) {
            quantity = order["quantity"].get<std::int16_t>();
            break;
        }
    }

    amount = price * quantity;

    //�������� ������������ id
    int Id = 0;

    // ����� ������������� �������� ID
    for (const auto& product : productsData["products"]) {
        if (product["name"] == choice) {
            Id = product["id"].get<int>();
        }
    }

    // �������� ������� ��������� ������
    if (choice.empty()) {
        cout << "������ � ��������� ID �� �������." << endl;
        system("pause");
        system("cls");
        return;
    }

    order.withdrawFunds(amount);
    for (int i = Id; i < quantity; ++i) {
        productsData["products"].push_back({
            {"id", Id},
            {"name", choice},
            {"price", price}
            });
    }

    // ���������� ����������� ������ � �����
    jsonHelper.writeJsonData("products.json", productsData);

    // ����� � �������� ��������� ������
    json updatedOrderData;
    for (const auto& order : orderData["orders"]) {
        if (!(order["product_name"] == choice && order["quantity"].get<int>() == quantity)) {
            updatedOrderData.push_back(order);
        }
        else {
            // ������ ���������, ������� JSON-������ � ����������� � ����������� ������
            json doneOrderData = {
                {"product_id", order["product_id"]},
                {"product_name", order["product_name"]},
                {"quantity", order["quantity"]},
                {"date_executed", getCurrentDate()} // ����� getCurrentDate() - ����� ��� ��������� ������� ����
            };

            // ��������� ����������� ������ � ���� "DoneOrders.json"
            existingData["DoneOrders"].push_back(doneOrderData);
            jsonHelper.writeJsonData("DoneOrders.json", existingData);
        }
    }

    // ������ ������ ������ ������ �������
    orderData["orders"] = updatedOrderData;


    // ���������� ����������� ������ � JSON-����
    jsonHelper.writeJsonData("orders.json", orderData);

    cout << "������ ������� ����������!" << endl;

    system("pause");
    system("cls");
}


