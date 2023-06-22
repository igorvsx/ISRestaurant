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

    // Загружаем данные из файла
    json jsonData = jsonHelper.readJsonData("products.json");

    Product product;

    cout << "Введите ID продукта: ";
    cin >> product.id;

    // Проверяем уникальность ID продукта
    for (const auto& existingProduct : jsonData["products"]) {
        if (existingProduct["id"] == product.id) {
            cout << "Продукт с указанным ID уже существует. Добавление невозможно." << endl;
            Sleep(1500);
            system("cls");
            return;
        }
    }

    cout << "Введите наименование продукта: ";
    cin.ignore();
    getline(cin, product.name);

    cout << "Введите цену продукта: ";
    cin >> product.price;

    // Добавляем продукт в список продуктов в формате JSON
    jsonData["products"].push_back({
        {"id", product.id},
        {"name", product.name},
        {"price", product.price}
        });

    // Сохраняем обновленные данные в файл JSON
    jsonHelper.writeJsonData("products.json", jsonData);

    Sleep(1500);
    system("cls");
}

void Product::editProduct() {
    JsonHelper jsonHelper;
    system("cls");

    // Загружаем данные из файла
    json jsonData = jsonHelper.readJsonData("products.json");

    // Выводим список продуктов
    std::cout << "Список продуктов:\n";
    for (const auto& product : jsonData["products"]) {
        std::cout << "ID: " << product["id"] << std::endl;
        std::cout << "Наименование: " << product["name"] << std::endl;
        std::cout << "Цена: " << product["price"] << std::endl;
        std::cout << "-----------------------\n";
    }

    // Получаем ID продукта, который нужно отредактировать
    int productId;
    std::cout << "Введите ID продукта для редактирования: ";
    std::cin >> productId;

    // Поиск продукта с указанным ID
    bool found = false;
    for (auto& product : jsonData["products"]) {
        if (product["id"] == productId) {
            found = true;

            std::cout << "Введите новое наименование продукта: ";
            std::cin.ignore();
            std::string newName;
            std::getline(std::cin, newName);
            product["name"] = newName;

            std::cout << "Введите новую цену продукта: ";
            double newPrice;
            std::cin >> newPrice;
            product["price"] = newPrice;

            std::cout << "Продукт успешно отредактирован.\n";
            break;
        }
    }

    // Сохраняем обновленные данные в файл
    if (found) {
        jsonHelper.writeJsonData("products.json", jsonData);
    }
    else {
        std::cout << "Продукт с указанным ID не найден.\n";
    }

    Sleep(1500);
    system("cls");
}

void Product::removeProduct() {
    JsonHelper jsonHelper;
    system("cls");

    // Загружаем данные из файла
    json jsonData = jsonHelper.readJsonData("products.json");

    // Выводим список продуктов
    std::cout << "Список продуктов:\n";
    for (const auto& product : jsonData["products"]) {
        std::cout << "ID: " << product["id"] << std::endl;
        std::cout << "Наименование: " << product["name"] << std::endl;
        std::cout << "Цена: " << product["price"] << std::endl;
        std::cout << "-----------------------\n";
    }

    // Получаем ID продукта, который нужно удалить
    int productId;
    std::cout << "Введите ID продукта для удаления: ";
    std::cin >> productId;

    // Поиск продукта с указанным ID
    bool found = false;
    for (auto it = jsonData["products"].begin(); it != jsonData["products"].end(); ++it) {
        if ((*it)["id"] == productId) {
            found = true;
            jsonData["products"].erase(it);
            std::cout << "Продукт успешно удален.\n";
            break;
        }
    }

    // Сохраняем обновленные данные в файл
    if (found) {
        jsonHelper.writeJsonData("products.json", jsonData);
    }
    else {
        std::cout << "Продукт с указанным ID не найден.\n";
    }

    Sleep(1500);
    system("cls");
}

void Product::editingProducts() {
    system("cls");

    int choice;

    while (true) {
        cout << "Редактирование продуктов:\n";
        cout << "1. Добавить\n";
        cout << "2. Изменить\n";
        cout << "3. Удалить\n";
        cout << "4. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
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
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
            break;
        }
    }
}
