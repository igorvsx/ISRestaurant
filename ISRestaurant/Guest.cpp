#include "Guest.h"
#include <string>
#include "JsonHelper.h"
#include <windows.h>
#include "Menu.h"
#include "Order.h"

using namespace std;

void Guest::createOrder() {
    //JsonHelper jsonHelper;
    //system("cls");

    //// �������� ������ �� JSON-�����
    //json menuData = jsonHelper.readJsonData("menu.json");
    //json productsData = jsonHelper.readJsonData("products.json");
    //json guestData = jsonHelper.readJsonData("guestOrder.json");

    //// �������� ������� ������� � ����
    //if (menuData["menu"].empty()) {
    //    cout << "���� �����." << endl;
    //    Sleep(1500);
    //    system("cls");
    //    return;
    //}

    //// ����� �������� ���� � �������� �������
    //cout << "������� ����:\n";
    //for (size_t i = 0; i < menuData["menu"].size(); ++i) {
    //    cout << "������ " << i + 1 << ":\n";
    //    cout << "��������: " << menuData["menu"][i]["name"].get<string>() << endl;
    //    cout << "��������: " << menuData["menu"][i]["description"].get<string>() << endl;
    //    cout << "--------------------------\n";
    //}

    //int recordNumber;
    //cout << "������� ����� ����� ��� ������: ";
    //cin >> recordNumber;

    //if (recordNumber <= 0 || recordNumber > menuData["menu"].size()) {
    //    cout << "������ ������������ ����� ������." << endl;
    //    system("pause");
    //    system("cls");
    //    return;
    //}

    //json& selectedDish = menuData["menu"][recordNumber - 1];

    //Order guestOrder;
    //guestOrder.setDishName(selectedDish["name"].get<string>());


    //char choice;
    //do {
    //    string menuItem;
    //    cout << "������� �������� �������� ��� ������: ";
    //    cin >> menuItem;

    //    bool found = false;

    //    for (const auto& product : productsData["products"]) {
    //        if (product["name"] == menuItem) {
    //            found = true;
    //            int quantity;
    //            cout << "������� ����������: ";
    //            cin >> quantity;

    //            // �������� ������� ������������ ���������� ��������� �� ������
    //            int availableQuantity = product["quantity"].get<int>();
    //            if (quantity <= availableQuantity) {
    //                // ���������� ������ ���� � ������
    //                guestOrder.addItem(product["id"].get<int>(), product["name"].get<string>(), quantity);
    //            }
    //            else {
    //                cout << "������������� ���������� �������� �� ������." << endl;
    //                // ��������� ������, ����� ������������� ���������� �������� �� ������
    //            }

    //            break;
    //        }
    //    }

    //    if (!found) {
    //        cout << "������� � ��������� ID �� ������." << endl;
    //        // ����������� ������, ����� ������� �� ������
    //    }

    //    cout << "�������� ��� �����������? (y/n): ";
    //    cin >> choice;
    //} while (choice == 'y');

}

void Guest::confirmOrder(double totalAmount) {

}

void Guest::displayStatus() const {

}

void Guest::displayOrder() const{

}

void Guest::removeItem() {

}

