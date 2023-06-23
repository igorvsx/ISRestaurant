#include <string>
#include "JsonHelper.h"
#include <windows.h>
#include "Menu.h"
#include "Order.h"
#include "Guest.h"

using namespace std;

struct MenuItem {
    std::string name;
    double cost;
};


void Guest::displayCart() {
    JsonHelper jsonHelper;
    system("cls");

    // �������� ������ �� JSON-�����
    json cartData = jsonHelper.readJsonData("cart.json");

    // �������� ������� ������� � �������
    if (cartData["cart"].empty()) {
        cout << "������� �����." << endl;
        Sleep(1500);
        system("cls");
        return;
    }

    // ����� ������� �� �������� "In processing"
    cout << "���������� �������:\n";
    bool foundOrders = false;
    for (const auto& item : cartData["cart"]) {
        if (item["status"] == "In processing") {
            cout << "��������: " << item["name"].get<string>() << endl;
            cout << "����: " << item["cost"].get<double>() << " ������" << endl;
            cout << "--------------------------\n";
            foundOrders = true;
        }
    }

    if (!foundOrders) {
        cout << "������� �����." << endl;
    }

    int choice;
    std::cout << "������� ����� ������ ��� ������: ";
    std::cin >> choice;
    system("cls");
}


void Guest::createOrder() {
    JsonHelper jsonHelper;
    system("cls");

    // �������� ������ �� JSON-�����
    json menuData = jsonHelper.readJsonData("menu.json");
    json productsData = jsonHelper.readJsonData("products.json");
    json guestData = jsonHelper.readJsonData("guestOrder.json");

    // �������� ������� ������� � ����
    if (menuData["menu"].empty()) {
        cout << "���� �����." << endl;
        Sleep(1500);
        system("cls");
        return;
    }

    // ����� �������� ���� � �������� �������
    bool isAvailable = true;
    cout << "������� ����:\n";
    for (size_t i = 0; i < menuData["menu"].size(); ++i) {
        cout << "������ " << i + 1 << ":\n";
        cout << "��������: " << menuData["menu"][i]["name"].get<string>() << endl;
        cout << "��������: " << menuData["menu"][i]["description"].get<string>() << endl;
        cout << "����� �������������: " << menuData["menu"][i]["cookingTime"].get<string>() << " �����" << endl;
        cout << "����: " << menuData["menu"][i]["cost"].get<double>() << " ������" << endl;
        cout << "��� �����: " << menuData["menu"][i]["weight"].get<string>() << " �����" << endl;
        cout << "�����������: " << endl;
        for (const auto& ingredient : menuData["menu"][i]["ingredients"]) {
            cout << "   - " << ingredient["name"].get<string>() << endl;
        }
        cout << "--------------------------\n";
    }

    int recordNumber;
    cout << "������� ����� ����� ��� ������: ";
    cin >> recordNumber;

    if (recordNumber <= 0 || recordNumber > menuData["menu"].size()) {
        cout << "������ ������������ ����� ������." << endl;
        system("pause");
        system("cls");
        return;
    }

    
    bool ingredientsAvailable = true;

    // ������� ���� ��� �������� ���������� ��������� �� �� ��������
    std::unordered_map<std::string, int> productQuantities;

    // ������� ���������� ���������
    for (const auto& product : productsData["products"]) {
        std::string productName = product["name"].get<std::string>();

        if (productQuantities.find(productName) != productQuantities.end()) {
            // ������� ��� ������������ � ����, ����������� ����������
            productQuantities[productName]++;
        }
        else {
            // ������� ����������� �������, �������������� ��� ����������
            productQuantities[productName] = 1;
        }
    }

    // �������� ����������� ������������ ���������� �����
    for (const auto& ingredient : menuData["menu"][recordNumber - 1]["ingredients"]) {
        std::string ingredientName = ingredient["name"].get<std::string>();
        int requiredQuantity = 1; // ������������, ��� ������ ����� ������� 1 ����������

        if (productQuantities.find(ingredientName) == productQuantities.end() ||
            productQuantities[ingredientName] < requiredQuantity) {
            // ���������� ����������� ��� ���������� ��������� ������������ ������������
            ingredientsAvailable = false;
            break;
        }
    }

    if (ingredientsAvailable) {

        MenuItem selectedMenuItem;
        /*std::vector<MenuItem> cart;*/

        selectedMenuItem.name = menuData["menu"][recordNumber - 1]["name"].get<std::string>();
        selectedMenuItem.cost = menuData["menu"][recordNumber - 1]["cost"].get<double>();

        /*addToCart(cart, selectedMenuItem.name, selectedMenuItem.cost);*/

        cout << endl << "����� ��������� � �������.";

        json cartData = jsonHelper.readJsonData("cart.json");

        cartData["cart"].push_back({
            {"name", selectedMenuItem.name},
            {"cost", selectedMenuItem.cost},
            {"status", "In processing"}
            });

        jsonHelper.writeJsonData("cart.json", cartData);

        Sleep(1500);
        system("cls");
    }
    else {
        system("cls");
        cout << "������������ ������������. ��������� ����� ������ �������� � �����." << endl;
        Sleep(1500);
        system("cls");
    }

}

void Guest::confirmOrder() {
    JsonHelper jsonHelper;
    system("cls");

    // �������� ������ �� JSON-�����
    json cartData = jsonHelper.readJsonData("cart.json");

    // �������� ������� ������� � �������
    if (cartData["cart"].empty()) {
        cout << "������� �����." << endl;
        Sleep(1500);
        system("cls");
        return;
    }

    // ����� ������� �� �������� "In processing"
    cout << "�������:\n";
    double orderTotal = 0.0;
    bool foundOrders = false;
    for (const auto& order : cartData["cart"]) {
        if (order["status"] == "In processing") {
            cout << "�����: " << order["name"].get<string>() << endl;
            cout << "����: " << order["cost"].get<double>() << " ������" << endl;
            orderTotal += order["cost"].get<double>();
            cout << "--------------------------\n";
            foundOrders = true;
        }
    }

    if (!foundOrders) {
        cout << "��� ������� ��� ������." << endl;
        Sleep(1500);
        system("cls");
        return;
    }

    cout << "����� ��������� ������: " << orderTotal << " ������" << endl;

    // ���� ����� �����
    double totalAmount;
    cout << "������� ����� �����: ";
    cin >> totalAmount;

    // �������� ��������� ����� �����
    if (totalAmount < orderTotal) {
        cout << "��������� ����� ������ ��������� ������. ��� �������." << endl;
        Sleep(1500);
        system("cls");
        return;
    }

    // ���������� ������� ���������
    double restaurantBalance = 0.0;
    ifstream balanceFile("RestBalance.txt");
    if (balanceFile.is_open()) {
        balanceFile >> restaurantBalance;
        balanceFile.close();
    }

    restaurantBalance += orderTotal;
    ofstream updatedBalanceFile("RestBalance.txt");
    if (updatedBalanceFile.is_open()) {
        updatedBalanceFile << restaurantBalance;
        updatedBalanceFile.close();
    }

    // ��������� ������� �������
    for (auto& order : cartData["cart"]) {
        if (order["status"] == "In processing") {
            order["status"] = "Paid for and transferred to the kitchen";
        }
    }

    // ���������� ����������� ������ � JSON-�����
    jsonHelper.writeJsonData("cart.json", cartData);

    cout << "����� ����������� � ������� �� �����." << endl;
    Sleep(1500);
    system("cls");
}


void Guest::displayStatus(){
    JsonHelper jsonHelper;
    system("cls");

    // �������� ������ �� JSON-�����
    json cartData = jsonHelper.readJsonData("cart.json");

    // �������� ������� ������� � �������
    if (cartData["cart"].empty()) {
        cout << "������� �����." << endl;
        Sleep(1500);
        system("cls");
        return;
    }

    // ����� ������� ������� ������
    cout << "������ �������:\n";
    for (const auto& order : cartData["cart"]) {
        cout << "�����: " << order["name"].get<string>() << endl;
        cout << "������: " << order["status"].get<string>() << endl;
        cout << "--------------------------\n";
    }

    system("pause");
    system("cls");
}

