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

void User::editMenu() {
    system("cls");
    int choice;

    while (true) {
        cout << "�������������� ����\n";
        cout << "1. �������� �����\n";
        cout << "2. ������� �����\n";
        cout << "3. ������������� �����\n";
        cout << "4. ��������� � ���������� ����\n";
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
            editMenu();
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
void User::editProductList() {
    system("cls");
    int choice;

    while (true) {
        cout << "1. �������� �������\n";
        cout << "2. �������� �������\n";
        cout << "3. ������� �������\n";
        cout << "4. ��������� � ���������� ����\n";
        cout << "�������� ��������: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "������������ �����. ���������� ��� ���." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        Menu menu;

        switch (choice) {
        case 1:
            addProduct();
            break;
        case 2:
            editProduct();
            break;
        case 3:
            removeProduct();
            break;
        case 4:
            return;
        default:
            cout << "������������ �����. ���������� ��� ���." << endl;
            break;
        }
    }
}

void User::addProduct() {
    system("cls");
    Product product;

    cout << "������� ID ��������: ";
    cin >> product.id;

    cout << "������� ������������ ��������: ";
    cin.ignore();
    getline(cin, product.name);

    cout << "������� ���� ��������: ";
    cin >> product.price;

    vector<Product> products;

    // ��������� ������� � ������ ���������
    // ��������, ���� ������ ��������� �������� � ������� products
    products.push_back(product);

    // ���������� ������ � ����
    ofstream outFile("products.txt", ios::app); // ��������� ���� ��� ���������� ������ � �����
    if (outFile.is_open()) {
        outFile << product.id << endl;
        outFile << product.name << endl;
        outFile << product.price << endl;
        outFile << "===" << endl; // ����������� ����� ����������
        outFile.close();
        cout << "������ ������� ��������� � ����." << endl;
    }
    else {
        cout << "������ �������� ����� ��� ���������� ������." << endl;
    }

    Sleep(1500);
    system("cls");
}


void User::editProduct() {
    system("cls");

    // ������ ������ �� �����
    ifstream inFile("products.txt");
    if (!inFile.is_open()) {
        cout << "������ �������� ����� ��� ������ ������." << endl;
        return;
    }

    // ������ ��� �������� ��������� �� �����
    vector<Product> fileProducts;

    string line;
    Product product;

    // ������ ������ �� ����� � ��������� �������� � �������
    while (getline(inFile, line)) {
        if (line == "===") {
            fileProducts.push_back(product);
            product = Product(); // ���������� product ��� ���������� ��������
        }
        else if (!line.empty()) {
            switch (fileProducts.size() % 3) {
            case 0:
                try {
                    product.id = stoi(line);
                }
                catch (const std::invalid_argument&) {
                    cout << "������ ������ ID �������� �� �����." << endl;
                    inFile.close();
                    return;
                }
                break;
            case 1:
                product.name = line;
                break;
            case 2:
                try {
                    product.price = stod(line);
                }
                catch (const std::invalid_argument&) {
                    cout << "������ ������ ���� �������� �� �����." << endl;
                    inFile.close();
                    return;
                }
                break;
            }
        }
    }

    inFile.close();

    // ������� ������ ��������� �� �����
    cout << "������ ���������:" << endl;
    for (const auto& prod : fileProducts) {
        cout << "ID: " << prod.id << endl;
        cout << "������������: " << prod.name << endl;
        cout << "����: " << prod.price << endl;
        cout << "=====================" << endl;
    }

    // ����������� ID ��������, ������� ����� ��������
    int id;
    cout << "������� ID ��������, ������� ����� ��������: ";
    cin >> id;

    // ���� ������� � ��������� ID � ������� ���������
    auto it = find_if(fileProducts.begin(), fileProducts.end(), [id](const Product& p) {
        return p.id == id;
        });

    if (it != fileProducts.end()) {
        // ������ �������, ����������� ����� ������
        cout << "������� ����� ������������ ��������: ";
        cin.ignore();
        getline(cin, it->name);

        cout << "������� ����� ���� ��������: ";
        cin >> it->price;

        // ��������� ��������� � �����
        ofstream outFile("products.txt");
        if (outFile.is_open()) {
            for (const auto& prod : fileProducts) {
                outFile << prod.id << endl;
                outFile << prod.name << endl;
                outFile << prod.price << endl;
                outFile << "===" << endl; // ����������� ����� ����������
            }
            outFile.close();
            cout << "������ ������� ��������� � ����." << endl;
        }
        else {
            cout << "������ �������� ����� ��� ���������� ������." << endl;
        }
    }
    else {
        cout << "������� � ��������� ID �� ������." << endl;
    }
}

void User::removeProduct() {
    system("cls");

    // ������ ������ �� �����
    ifstream inFile("products.txt");
    if (!inFile.is_open()) {
        cout << "������ �������� ����� ��� ������ ������." << endl;
        return;
    }

    // ������ ��� �������� ��������� �� �����
    vector<Product> fileProducts;

    string line;
    Product product;

    // ������ ������ �� ����� � ��������� �������� � �������
    while (getline(inFile, line)) {
        if (line == "===") {
            fileProducts.push_back(product);
            product = Product(); // ���������� product ��� ���������� ��������
        }
        else if (!line.empty()) {
            switch (fileProducts.size() % 3) {
            case 0:
                try {
                    product.id = stoi(line);
                }
                catch (const std::invalid_argument&) {
                    cout << "������ ������ ID �������� �� �����." << endl;
                    inFile.close();
                    return;
                }
                break;
            case 1:
                product.name = line;
                break;
            case 2:
                try {
                    product.price = stod(line);
                }
                catch (const std::invalid_argument&) {
                    cout << "������ ������ ���� �������� �� �����." << endl;
                    inFile.close();
                    return;
                }
                break;
            }
        }
    }

    inFile.close();

    // ������� ������ ��������� �� �����
    cout << "������ ���������:" << endl;
    for (const auto& prod : fileProducts) {
        cout << "ID: " << prod.id << endl;
        cout << "������������: " << prod.name << endl;
        cout << "����: " << prod.price << endl;
        cout << "=====================" << endl;
    }

    // ����������� ID ��������, ������� ����� �������
    int id;
    cout << "������� ID ��������, ������� ����� �������: ";
    cin >> id;

    // ���� ������� � ��������� ID � ������� ���������
    auto it = find_if(fileProducts.begin(), fileProducts.end(), [id](const Product& p) {
        return p.id == id;
        });

    if (it != fileProducts.end()) {
        // ������ �������, ������� ��� �� �������
        fileProducts.erase(it);

        // ��������� ��������� � �����
        ofstream outFile("products.txt");
        if (outFile.is_open()) {
            for (const auto& prod : fileProducts) {
                outFile << prod.id << endl;
                outFile << prod.name << endl;
                outFile << prod.price << endl;
                outFile << "===" << endl; // ����������� ����� ����������
            }
            outFile.close();
            cout << "������� ������� ������." << endl;
        }
        else {
            cout << "������ �������� ����� ��� ���������� ������." << endl;
        }
    }
    else {
        cout << "������� � ��������� ID �� ������." << endl;
    }
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
    }
    else {
        std::cout << "��������� � ��������� ������� �� ������.\n";
    }
}



void User::guestMenu() {
    cout << "���� �����" << endl;
    // �������� ���������������� ��� ���� �����
}

void User::adminMenu() {
    int choice;

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
            editMenu();
            break;
        case 2:
            editProductList();
            break;
        case 3:
            editEmployees();
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
            editMenu();
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
