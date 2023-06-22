#include "Order.h"
#include "JsonHelper.h"

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

    // ���������� ����� ������ � ������
    orderData["orders"].push_back(newOrder);

    // ���������� ����������� ������ � �����
    jsonHelper.writeJsonData("orders.json", orderData);

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
