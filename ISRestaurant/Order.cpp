#include "Order.h"
#include "JsonHelper.h"
#include <ctime>
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
    for (const auto& product : productData["products"]) {
        std::cout << "ID: " << product["id"] << std::endl;
        std::cout << "������������: " << product["name"] << std::endl;
        std::cout << "����: " << product["price"] << std::endl;
        std::cout << "-----------------------\n";
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
        std::cout << "������ ������� ������� � ������� ���������." << std::endl;
    }
    else {
        std::cout << "������ ��� ���������� ������� ���������." << std::endl;
    }
}

void Order::displayOrders() {
    JsonHelper jsonHelper;
    system("cls");

    // ��������� ������ � ������� �� �����
    json orderData = jsonHelper.readJsonData("orders.json");

    if (orderData.empty()) {
        std::cout << "��� ��������� ������." << std::endl;
        system("pause");
        system("cls");
        return;
    }

    // ������� ������ ������
    std::cout << "������ ������:\n";
    for (const auto& order : orderData) {
        int productId = order["product_id"];
        int quantityPro = order["quantity"];

        std::cout << "ID ��������: " << productId << std::endl;

        // �������� ���������� � �������� �� ID �� ����� "products.json"
        json productData = jsonHelper.getProductData(productId);
        if (!productData.empty()) {
            std::cout << "������������: " << productData["name"] << std::endl;
            std::cout << "���� �� �����: " << productData["price"] << std::endl;
            std::cout << "����������: " << quantityPro << std::endl;
            std::cout << "����� ���������: " << productData["price"] * quantityPro << std::endl;
            std::cout << "-----------------------\n";
        }
    }

    system("pause");
    system("cls");
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
