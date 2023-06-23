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

    cout << "Продукт успешно добавлен";

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
    int offset = 0;
    int pageSize = 5;
    int totalCount = jsonData["products"].size();
    std::set<int> displayedIDs; // Множество для отслеживания уже выведенных ID

    while (offset < totalCount) {
        // Выводим текущую страницу продуктов
        for (int i = offset; i < std::min(offset + pageSize, totalCount); ++i) {
            const auto& product = jsonData["products"][i];
            int productID = product["id"].get<int>();

            // Проверяем, был ли уже выведен продукт с таким ID
            if (displayedIDs.find(productID) != displayedIDs.end()) {
                continue; // Продукт уже был выведен, переходим к следующему
            }

            displayedIDs.insert(productID); // Добавляем ID в множество выведенных продуктов

            std::cout << "ID: " << productID << std::endl;
            std::cout << "Наименование: " << product["name"] << std::endl;
            std::cout << "Цена: " << product["price"] << std::endl;
            std::cout << "-----------------------\n";
        }

        // Запрашиваем подтверждение загрузки еще записей
        if (offset + pageSize < totalCount) {
            std::string input;
            std::cout << "Загрузить еще? (y/n): ";
            std::cin >> input;

            if (input != "y")
                break;
        }

        offset += pageSize;
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

    std::cout << "Список продуктов:\n";
    int offset = 0;
    int pageSize = 5;
    int totalCount = jsonData["products"].size();
    std::set<int> displayedIDs; // Множество для отслеживания уже выведенных ID

    while (offset < totalCount) {
        // Выводим текущую страницу продуктов
        for (int i = offset; i < std::min(offset + pageSize, totalCount); ++i) {
            const auto& product = jsonData["products"][i];
            int productID = product["id"].get<int>();

            // Проверяем, был ли уже выведен продукт с таким ID
            if (displayedIDs.find(productID) != displayedIDs.end()) {
                continue; // Продукт уже был выведен, переходим к следующему
            }

            displayedIDs.insert(productID); // Добавляем ID в множество выведенных продуктов

            std::cout << "ID: " << productID << std::endl;
            std::cout << "Наименование: " << product["name"] << std::endl;
            std::cout << "Цена: " << product["price"] << std::endl;
            std::cout << "-----------------------\n";
        }

        // Запрашиваем подтверждение загрузки еще записей
        if (offset + pageSize < totalCount) {
            std::string input;
            std::cout << "Загрузить еще? (y/n): ";
            std::cin >> input;

            if (input != "y")
                break;
        }

        offset += pageSize;
    }


    //// Выводим список продуктов
    //std::cout << "Список продуктов:\n";
    //for (const auto& product : jsonData["products"]) {
    //    std::cout << "ID: " << product["id"] << std::endl;
    //    std::cout << "Наименование: " << product["name"] << std::endl;
    //    std::cout << "Цена: " << product["price"] << std::endl;
    //    std::cout << "-----------------------\n";
    //}

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
        cout << "1. Список продуктов\n";
        cout << "2. Добавить\n";
        cout << "3. Изменить\n";
        cout << "4. Удалить\n";
        cout << "5. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
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
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
            break;
        }
    }
}

void Product::productList() {
    JsonHelper jsonHelper;
    system("cls");

    // Загружаем данные из файла
    json jsonData = jsonHelper.readJsonData("products.json");

    // Создаем словарь для хранения информации о продуктах
    std::map<int, std::tuple<std::string, int, double, double>> productInfo;

    // Подсчитываем количество позиций, общую стоимость и цену за 1 штуку
    for (const auto& product : jsonData["products"]) {
        int id = product["id"];
        std::string name = product["name"];
        double price = product["price"];
        if (productInfo.find(id) != productInfo.end()) {
            std::get<1>(productInfo[id])++; // Увеличиваем количество позиций
            std::get<2>(productInfo[id]) += price; // Увеличиваем общую стоимость
        }
        else {
            double costPerUnit = price; // Цена за 1 штуку равна начальной цене
            productInfo[id] = std::make_tuple(name, 1, price, costPerUnit);
        }
    }

    // Преобразуем информацию о продуктах в список уникальных продуктов
    std::vector<std::tuple<int, std::string, int, double, double>> uniqueProducts;
    for (const auto& item : productInfo) {
        int id = item.first;
        std::string name = std::get<0>(item.second);
        int quantity = std::get<1>(item.second);
        double totalCost = std::get<2>(item.second);
        double costPerUnit = std::get<3>(item.second);
        uniqueProducts.push_back(std::make_tuple(id, name, quantity, totalCost, costPerUnit));
    }

    // Определяем количество записей на странице
    const int itemsPerPage = 5;
    int totalPages = (uniqueProducts.size() + itemsPerPage - 1) / itemsPerPage; // Округление вверх

    // Выводим список продуктов с информацией
    std::cout << "Список продуктов:\n";
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
            std::cout << "Наименование: " << name << std::endl;
            std::cout << "Количество: " << quantity << std::endl;
            std::cout << "Общая стоимость: " << totalCost << std::endl;
            std::cout << "Цена за 1 штуку: " << costPerUnit << std::endl;
            std::cout << "-----------------------\n";
        }

        // Проверяем, является ли текущая страница последней
        bool isLastPage = currentPage == totalPages;

        // Если текущая страница последняя, прекращаем пагинацию
        if (isLastPage) {
            std::cout << "Это последняя страница. Нет доступных записей для загрузки.\n";
            break;
        }

        // Просим пользователя загрузить следующую страницу
        std::cout << "Введите 'y' для загрузки следующей страницы, или любой другой символ для выхода: ";
        std::string input;
        std::cin >> input;

        // Если пользователь не желает загружать следующую страницу, прекращаем пагинацию
        if (input != "y") {
            system("cls");
            return;
        }

        // Увеличиваем индексы для перехода на следующую страницу
        startIndex += itemsPerPage;
        currentPage++;
    }

    int choice;
    std::cout << "Введите любой символ для выхода: ";
    std::cin >> choice;
    switch (choice) {
    default:
        return;
        break;
    }

    Sleep(1500);
    system("cls");
}

