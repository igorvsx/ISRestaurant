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

    //// Загрузка данных из JSON-файла
    //json menuData = jsonHelper.readJsonData("menu.json");
    //json productsData = jsonHelper.readJsonData("products.json");
    //json guestData = jsonHelper.readJsonData("guestOrder.json");

    //// Проверка наличия записей в меню
    //if (menuData["menu"].empty()) {
    //    cout << "Меню пусто." << endl;
    //    Sleep(1500);
    //    system("cls");
    //    return;
    //}

    //// Вывод текущего меню с номерами записей
    //cout << "Текущее меню:\n";
    //for (size_t i = 0; i < menuData["menu"].size(); ++i) {
    //    cout << "Запись " << i + 1 << ":\n";
    //    cout << "Название: " << menuData["menu"][i]["name"].get<string>() << endl;
    //    cout << "Описание: " << menuData["menu"][i]["description"].get<string>() << endl;
    //    cout << "--------------------------\n";
    //}

    //int recordNumber;
    //cout << "Введите номер блюда для выбора: ";
    //cin >> recordNumber;

    //if (recordNumber <= 0 || recordNumber > menuData["menu"].size()) {
    //    cout << "Введен некорректный номер записи." << endl;
    //    system("pause");
    //    system("cls");
    //    return;
    //}

    //json& selectedDish = menuData["menu"][recordNumber - 1];

    //GuestOrder guestOrder;
    //guestOrder.setDishName(selectedDish["name"].get<string>());


    //char choice;
    //do {
    //    string menuItem;
    //    cout << "Введите название продукта для заказа: ";
    //    cin >> menuItem;

    //    bool found = false;

    //    for (const auto& product : productsData["products"]) {
    //        if (product["name"] == menuItem) {
    //            found = true;
    //            int quantity;
    //            cout << "Введите количество: ";
    //            cin >> quantity;

    //            // Проверка наличия достаточного количества продуктов на складе
    //            int availableQuantity = product["quantity"].get<int>();
    //            if (quantity <= availableQuantity) {
    //                // Добавление пункта меню к заказу
    //                guestOrder.addItem(product["id"].get<int>(), product["name"].get<string>(), quantity);
    //            }
    //            else {
    //                cout << "Недостаточное количество продукта на складе." << endl;
    //                // Обработка случая, когда недостаточное количество продукта на складе
    //            }

    //            break;
    //        }
    //    }

    //    if (!found) {
    //        cout << "Продукт с указанным ID не найден." << endl;
    //        // Обработайте случай, когда продукт не найден
    //    }

    //    cout << "Добавить еще ингредиенты? (y/n): ";
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

