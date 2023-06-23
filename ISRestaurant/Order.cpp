#include "Order.h"
#include "JsonHelper.h"
#include <ctime>
#include <set>
#include <string>
#include <windows.h>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

void TrunkTxt() {
    std::ofstream balanceFile;
    balanceFile.open("RestBalance.txt", std::ofstream::out | std::ofstream::trunc);
    balanceFile.close();
}

double getBalance() {
    std::ifstream balanceFile("RestBalance.txt");
    if (!balanceFile) {
        // ��������� ������ ������ �����
        std::cerr << "������ �������� ����� RestBalance.txt." << std::endl;
        return 0.0; // ���������� 0 � ������ ������
    }

    double balance;
    if (!(balanceFile >> balance)) {
        // ��������� ������ ������ �������� �������
        std::cerr << "������ ������ ������� �� ����� RestBalance.txt." << std::endl;
        return 0.0; // ���������� 0 � ������ ������
    }

    balanceFile.close();
    return balance;
}

void Order::createOrder() {
    JsonHelper jsonHelper;
    system("cls");

    std::time_t currentTime = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &currentTime);
    char timeBuffer[26];
    asctime_s(timeBuffer, sizeof(timeBuffer), &localTime);
    std::string sendTime(timeBuffer);

    // �������� ������ � ���������
    json productData = jsonHelper.readJsonData("products.json");

    // ����� ������ ���������
    std::cout << "������ ���������:\n";
    std::set<int> printedIds; // ��������� ��� ������������ ��� ���������� ID
    for (const auto& product : productData["products"]) {
        int productId = product["id"].get<int>();
        if (printedIds.find(productId) == printedIds.end()) {
            // ������� � ������ ID ��� �� ��� �������, ������� ���
            printedIds.insert(productId); // ��������� ID � ��������� ��� ���������� ID
            std::cout << "ID: " << productId << std::endl;
            std::cout << "������������: " << product["name"] << std::endl;
            std::cout << "����: " << product["price"] << std::endl;
            std::cout << "-----------------------\n";
        }
    }

    // ���� ������ ��� ������
    int productId;
    int quantity;

    std::cout << "������� ID ��������: ";
    std::cin >> productId;

    std::cout << "������� ����������: ";
    std::cin >> quantity;

    // ��������� ������ � ��������� ��������
    json selectedProduct = jsonHelper.getProductData(productId);

    // �������� ������� ���������� ��������
    if (selectedProduct.empty()) {
        std::cout << "������� � ��������� ID �� ������." << std::endl;
        system("pause");
        system("cls");
        return;
    }

    // ������ ����� ������
    double totalPrice = selectedProduct["price"].get<double>() * quantity;

    // �������� ������� ��������� �� �����
    double balance = getBalance();

    // �������� ������� ���������
    if (balance < totalPrice) {
        std::cout << "������������ ������� �� ������� ���������." << std::endl;
        system("pause");
        system("cls");
        return;
    }

    // �������� ������ � ������������ ������� �� �����
    json orderData = jsonHelper.readJsonData("orders.json");

    // �������� ����� ������
    json newOrder;
    newOrder["product_id"] = productId;
    newOrder["product_name"] = selectedProduct["name"];
    newOrder["quantity"] = quantity;
    newOrder["send_time"] = sendTime;

    // ���������� ����� ������ � ������
    orderData["orders"].push_back(newOrder);

    // ���������� ����������� ������ � �����
    jsonHelper.writeJsonData("orders.json", orderData);

    // ���������� ������������ ������ � ���� "SendOrders.json"
    json sendOrdersData = jsonHelper.readJsonData("SendOrders.json");
    sendOrdersData["SendOrders"].push_back(newOrder);
    jsonHelper.writeJsonData("SendOrders.json", sendOrdersData);

    std::cout << "������ ������� �������." << std::endl;

    system("pause");
    system("cls");
}

void Order::withdrawFunds(double amount){
    double currentBalance = getBalance();

    // �������� ������� ����������� �������
    if (currentBalance < amount) {
        std::cout << "������������ ������� �� ������� ���������." << std::endl;
        return;
    }

    // ��������� ����� ��������
    double updatedBalance = currentBalance - amount;

    // ���������� ������� � �����
    std::ofstream balanceFile("RestBalance.txt");
    if (balanceFile.is_open()) {
        balanceFile << updatedBalance;
        balanceFile.close();
        //std::cout << "������ ������� ������� � ������� ���������." << std::endl;
    }
    else {
        std::cout << "������ ��� ���������� ������� ���������." << std::endl;
    }
}

void Order::printSendOrders() {
    system("cls");
    JsonHelper jsonHelper;


    // ������ ������ �� ����� "SendOrders.json"
    json sendOrderData = jsonHelper.readJsonData("SendOrders.json");

    // �������� ������� ������
    if (sendOrderData["SendOrders"].empty()) {
        std::cout << "������ ������������ ������ ����." << std::endl;
        return;
    }

    // ����� ������ ������������ ������
    std::cout << "������ ������������ ������:" << std::endl;
    for (const auto& sendOrder : sendOrderData["SendOrders"]) {
        std::cout << "�������� ��������: " << sendOrder["product_name"] << std::endl;
        std::cout << "����������: " << sendOrder["quantity"] << std::endl;
        std::cout << "����� ��������: " << sendOrder["send_time"] << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
    int choice;
    std::cout << "������� ����� ������ ��� ������: ";
    std::cin >> choice;
    switch (choice) {
    default:
        return;
    }
}

void Order::ordersList() {
    JsonHelper jsonHelper;
    system("cls");


    std::time_t currentTime = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &currentTime);
    char timeBuffer[26];
    asctime_s(timeBuffer, sizeof(timeBuffer), &localTime);
    std::string sendTime(timeBuffer);


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
        Sleep(1500);
        system("cls");
        return;
    }

    withdrawFunds(amount);
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
                {"date_executed", sendTime} 
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

void Order::printAcceptOrders() {
    system("cls");
    JsonHelper jsonHelper;


    // ������ ������ �� ����� "DoneOrders.json"
    json doneOrderData = jsonHelper.readJsonData("DoneOrders.json");

    // �������� ������� ������
    if (doneOrderData["DoneOrders"].empty()) {
        std::cout << "������ �������� ��������� ����." << std::endl;
        return;
    }

    // ����� ������ ������������ ������
    std::cout << "������ �������� ���������:" << std::endl;
    for (const auto& doneOrder : doneOrderData["DoneOrders"]) {
        cout << "����: " << doneOrder["date_executed"] << endl;
        cout << "ID ��������: " << doneOrder["product_id"] << endl;
        cout << "�������� ��������: " << doneOrder["product_name"] << endl;
        std::cout << "����������: " << doneOrder["quantity"] << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
    int choice;
    std::cout << "������� ����� ������ ��� ������: ";
    std::cin >> choice;
    switch (choice) {
    default:
        return;
    }
}