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
#include <set>

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

    cout << "������� ������� ��������";

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
    int offset = 0;
    int pageSize = 5;
    int totalCount = jsonData["products"].size();
    std::set<int> displayedIDs; // ��������� ��� ������������ ��� ���������� ID

    while (offset < totalCount) {
        // ������� ������� �������� ���������
        for (int i = offset; i < std::min(offset + pageSize, totalCount); ++i) {
            const auto& product = jsonData["products"][i];
            int productID = product["id"].get<int>();

            // ���������, ��� �� ��� ������� ������� � ����� ID
            if (displayedIDs.find(productID) != displayedIDs.end()) {
                continue; // ������� ��� ��� �������, ��������� � ����������
            }

            displayedIDs.insert(productID); // ��������� ID � ��������� ���������� ���������

            std::cout << "ID: " << productID << std::endl;
            std::cout << "������������: " << product["name"] << std::endl;
            std::cout << "����: " << product["price"] << std::endl;
            std::cout << "-----------------------\n";
        }

        // ����������� ������������� �������� ��� �������
        if (offset + pageSize < totalCount) {
            std::string input;
            std::cout << "��������� ���? (y/n): ";
            std::cin >> input;

            if (input != "y")
                break;
        }

        offset += pageSize;
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

    std::cout << "������ ���������:\n";
    int offset = 0;
    int pageSize = 5;
    int totalCount = jsonData["products"].size();
    std::set<int> displayedIDs; // ��������� ��� ������������ ��� ���������� ID

    while (offset < totalCount) {
        // ������� ������� �������� ���������
        for (int i = offset; i < std::min(offset + pageSize, totalCount); ++i) {
            const auto& product = jsonData["products"][i];
            int productID = product["id"].get<int>();

            // ���������, ��� �� ��� ������� ������� � ����� ID
            if (displayedIDs.find(productID) != displayedIDs.end()) {
                continue; // ������� ��� ��� �������, ��������� � ����������
            }

            displayedIDs.insert(productID); // ��������� ID � ��������� ���������� ���������

            std::cout << "ID: " << productID << std::endl;
            std::cout << "������������: " << product["name"] << std::endl;
            std::cout << "����: " << product["price"] << std::endl;
            std::cout << "-----------------------\n";
        }

        // ����������� ������������� �������� ��� �������
        if (offset + pageSize < totalCount) {
            std::string input;
            std::cout << "��������� ���? (y/n): ";
            std::cin >> input;

            if (input != "y")
                break;
        }

        offset += pageSize;
    }


    //// ������� ������ ���������
    //std::cout << "������ ���������:\n";
    //for (const auto& product : jsonData["products"]) {
    //    std::cout << "ID: " << product["id"] << std::endl;
    //    std::cout << "������������: " << product["name"] << std::endl;
    //    std::cout << "����: " << product["price"] << std::endl;
    //    std::cout << "-----------------------\n";
    //}

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
        cout << "1. ������ ���������\n";
        cout << "2. ��������\n";
        cout << "3. ��������\n";
        cout << "4. �������\n";
        cout << "5. �����\n";
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
            system("cls");
            productList();
            break;
        case 2:
            system("cls");
            addProduct();
            break;
        case 3:
            system("cls");
            editProduct();
            break;
        case 4:
            system("cls");
            removeProduct();
            break;
        case 5:
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

    // ����������� ���������� � ��������� � ������ ���������� ���������
    std::vector<std::tuple<int, std::string, int, double, double>> uniqueProducts;
    for (const auto& item : productInfo) {
        int id = item.first;
        std::string name = std::get<0>(item.second);
        int quantity = std::get<1>(item.second);
        double totalCost = std::get<2>(item.second);
        double costPerUnit = std::get<3>(item.second);
        uniqueProducts.push_back(std::make_tuple(id, name, quantity, totalCost, costPerUnit));
    }

    // ���������� ���������� ������� �� ��������
    const int itemsPerPage = 5;
    int totalPages = (uniqueProducts.size() + itemsPerPage - 1) / itemsPerPage; // ���������� �����

    // ������� ������ ��������� � �����������
    std::cout << "������ ���������:\n";
    int startIndex = 0;
    int currentPage = 1;

    while (true) {
        int endIndex = std::min(startIndex + itemsPerPage, static_cast<int>(uniqueProducts.size()));

        for (int i = startIndex; i < endIndex; ++i) {
            int id = std::get<0>(uniqueProducts[i]);
            std::string name = std::get<1>(uniqueProducts[i]);
            int quantity = std::get<2>(uniqueProducts[i]);
            double totalCost = std::get<3>(uniqueProducts[i]);
            double costPerUnit = std::get<4>(uniqueProducts[i]);

            std::cout << "ID: " << id << std::endl;
            std::cout << "������������: " << name << std::endl;
            std::cout << "����������: " << quantity << std::endl;
            std::cout << "����� ���������: " << totalCost << std::endl;
            std::cout << "���� �� 1 �����: " << costPerUnit << std::endl;
            std::cout << "-----------------------\n";
        }

        // ���������, �������� �� ������� �������� ���������
        bool isLastPage = currentPage == totalPages;

        // ���� ������� �������� ���������, ���������� ���������
        if (isLastPage) {
            std::cout << "��� ��������� ��������. ��� ��������� ������� ��� ��������.\n";
            break;
        }

        // ������ ������������ ��������� ��������� ��������
        std::cout << "������� 'y' ��� �������� ��������� ��������, ��� ����� ������ ������ ��� ������: ";
        std::string input;
        std::cin >> input;

        // ���� ������������ �� ������ ��������� ��������� ��������, ���������� ���������
        if (input != "y") {
            system("cls");
            return;
        }

        // ����������� ������� ��� �������� �� ��������� ��������
        startIndex += itemsPerPage;
        currentPage++;
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

