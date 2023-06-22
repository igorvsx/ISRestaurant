#include "Product.h"
#include "JsonHelper.h"
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

void Product::addProduct() {
    JsonHelper jsonHelper;
    system("cls");

    // ��������� ������ �� �����
    json jsonData = jsonHelper.readJsonData("products.json");

    Product product;

    cout << "������� ID ��������: ";
    cin >> product.id;

    // ��������� ������������ ID ��������
    for (const auto& existingProduct : jsonData["products"]) {
        if (existingProduct["id"] == product.id) {
            cout << "������� � ��������� ID ��� ����������. ���������� ����������." << endl;
            Sleep(1500);
            system("cls");
            return;
        }
    }

    cout << "������� ������������ ��������: ";
    cin.ignore();
    getline(cin, product.name);

    cout << "������� ���� ��������: ";
    cin >> product.price;

    // ��������� ������� � ������ ��������� � ������� JSON
    jsonData["products"].push_back({
        {"id", product.id},
        {"name", product.name},
        {"price", product.price}
        });

    // ��������� ����������� ������ � ���� JSON
    jsonHelper.writeJsonData("products.json", jsonData);

    Sleep(1500);
    system("cls");
}

void Product::editProduct() {
    JsonHelper jsonHelper;
    system("cls");

    // ��������� ������ �� �����
    json jsonData = jsonHelper.readJsonData("products.json");

    // ������� ������ ���������
    std::cout << "������ ���������:\n";
    for (const auto& product : jsonData["products"]) {
        std::cout << "ID: " << product["id"] << std::endl;
        std::cout << "������������: " << product["name"] << std::endl;
        std::cout << "����: " << product["price"] << std::endl;
        std::cout << "-----------------------\n";
    }

    // �������� ID ��������, ������� ����� ���������������
    int productId;
    std::cout << "������� ID �������� ��� ��������������: ";
    std::cin >> productId;

    // ����� �������� � ��������� ID
    bool found = false;
    for (auto& product : jsonData["products"]) {
        if (product["id"] == productId) {
            found = true;

            std::cout << "������� ����� ������������ ��������: ";
            std::cin.ignore();
            std::string newName;
            std::getline(std::cin, newName);
            product["name"] = newName;

            std::cout << "������� ����� ���� ��������: ";
            double newPrice;
            std::cin >> newPrice;
            product["price"] = newPrice;

            std::cout << "������� ������� ��������������.\n";
            break;
        }
    }

    // ��������� ����������� ������ � ����
    if (found) {
        jsonHelper.writeJsonData("products.json", jsonData);
    }
    else {
        std::cout << "������� � ��������� ID �� ������.\n";
    }

    Sleep(1500);
    system("cls");
}

void Product::removeProduct() {
    JsonHelper jsonHelper;
    system("cls");

    // ��������� ������ �� �����
    json jsonData = jsonHelper.readJsonData("products.json");

    // ������� ������ ���������
    std::cout << "������ ���������:\n";
    for (const auto& product : jsonData["products"]) {
        std::cout << "ID: " << product["id"] << std::endl;
        std::cout << "������������: " << product["name"] << std::endl;
        std::cout << "����: " << product["price"] << std::endl;
        std::cout << "-----------------------\n";
    }

    // �������� ID ��������, ������� ����� �������
    int productId;
    std::cout << "������� ID �������� ��� ��������: ";
    std::cin >> productId;

    // ����� �������� � ��������� ID
    bool found = false;
    for (auto it = jsonData["products"].begin(); it != jsonData["products"].end(); ++it) {
        if ((*it)["id"] == productId) {
            found = true;
            jsonData["products"].erase(it);
            std::cout << "������� ������� ������.\n";
            break;
        }
    }

    // ��������� ����������� ������ � ����
    if (found) {
        jsonHelper.writeJsonData("products.json", jsonData);
    }
    else {
        std::cout << "������� � ��������� ID �� ������.\n";
    }

    Sleep(1500);
    system("cls");
}

void Product::editingProducts() {
    system("cls");

    int choice;

    while (true) {
        cout << "�������������� ���������:\n";
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
            addProduct();
            break;
        case 2:
            editProduct();
            break;
        case 3:
            removeProduct();
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

void Product::productList() {
    JsonHelper jsonHelper;
    system("cls");

    // ��������� ������ �� �����
    json jsonData = jsonHelper.readJsonData("products.json");

    // ������� ������� ��� �������� ���������� � ���������
    std::map<int, std::tuple<std::string, int, double, double>> productInfo;

    // ������������ ���������� �������, ����� ��������� � ���� �� 1 �����
    for (const auto& product : jsonData["products"]) {
        int id = product["id"];
        std::string name = product["name"];
        double price = product["price"];
        if (productInfo.find(id) != productInfo.end()) {
            std::get<1>(productInfo[id])++; // ����������� ���������� �������
            std::get<2>(productInfo[id]) += price; // ����������� ����� ���������
        }
        else {
            double costPerUnit = price; // ���� �� 1 ����� ����� ��������� ����
            productInfo[id] = std::make_tuple(name, 1, price, costPerUnit);
        }
    }

    // ������� ������ ��������� � �����������
    std::cout << "������ ���������:\n";
    for (const auto& item : productInfo) {
        int id = item.first;
        std::string name = std::get<0>(item.second);
        int quantity = std::get<1>(item.second);
        double totalCost = std::get<2>(item.second);
        double costPerUnit = std::get<3>(item.second);

        std::cout << "ID: " << id << std::endl;
        std::cout << "������������: " << name << std::endl;
        std::cout << "����������: " << quantity << std::endl;
        std::cout << "����� ���������: " << totalCost << std::endl;
        std::cout << "���� �� 1 �����: " << costPerUnit << std::endl;
        std::cout << "-----------------------\n";
    }

    int choice;
    std::cout << "������� ����� ������ ��� ������: ";
    std::cin >> choice;
    switch (choice) {
    default:
        return;
        break;
    }

    Sleep(1500);
    system("cls");
}