#include "Menu.h"
#include "Product.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <cstdlib>
#include "JsonHelper.h"
#define NOMINMAX
#include <windows.h>

using namespace std;

void Menu::editMenu() {
    system("cls");
    int choice;

    while (true) {
        cout << "Редактирование меню:\n";
        cout << "1. Добавить блюдо\n";
        cout << "2. Удалить блюдо\n";
        cout << "3. Редактировать блюдо\n";
        cout << "4. Вернуться в предыдущее меню\n";
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
            addDish();
            editMenu();
            break;
        case 2:
            removeDish();
            break;
        case 3:
            editDish();
            break;
        case 4:
            return;  // Выход из функции editMenu() и возврат к предыдущему меню
        default:
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
            system("cls");
            break;
        }
    }
}

void Menu::addDish() {
    JsonHelper jsonHelper;

    system("cls");

    // Создаем новое блюдо
    Menu newDish;

    json jsonData = jsonHelper.readJsonData("products.json");

    cout << "Введите наименование блюда: ";
    cin.ignore();
    getline(cin, newDish.name);

    cout << "Введите граммовку блюда: ";
    getline(cin, newDish.weight);

    // Добавление ингредиентов
    char choice;
    do {

        Product product;
        cout << "Введите ID продукта: ";
        cin >> product.id;

        string productName;
        bool found = false;

        Product selectedProduct;
        for (const auto& selectedProduct : jsonData["products"]) {
            if (selectedProduct["id"] == product.id) {
                found = true;
                selectedProduct["name"] == productName;
                break;
            }
        }

        if (found) {

            // Используйте selectedProduct для доступа к данным о выбранном продукте
            // Например, вы можете использовать selectedProduct.name для получения наименования продукта
            // и добавить его в новое блюдо newDish.ingredients.push_back(selectedProduct);

            // Продолжите код для обработки выбранного продукта
            newDish.ingredients.push_back(product);
        }
        else {
            cout << "Продукт с указанным ID не найден." << endl;
            // Обработайте случай, когда продукт не найден
        }

        cout << "Добавить еще ингредиенты? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    cout << "Введите описание блюда: ";
    cin.ignore();
    getline(cin, newDish.description);

    cout << "Введите время приготовления блюда: ";
    getline(cin, newDish.cookingTime);

    cout << "Введите стоимость блюда: ";
    cin >> newDish.cost;

    // Загрузка данных из JSON-файла
    /*json jsonData = jsonHelper.readJsonData("menu.json");*/

    // Добавление нового блюда в JSON-данные
    json ingredientsJson = json::array();
    for (const auto& ingredient : newDish.ingredients) {
        json ingredientJson = {
            {"id", ingredient.id},
            {"name", ingredient.name},
            {"price", ingredient.price}
        };
        ingredientsJson.push_back(ingredientJson);
    }

    jsonData["dishes"].push_back({
    {"name", newDish.name},
    {"weight", newDish.weight},
    {"ingredients", ingredientsJson},
    {"description", newDish.description},
    {"cookingTime", newDish.cookingTime},
    {"cost", newDish.cost}
        });

    // Сохранение обновленных данных в JSON-файл
    jsonHelper.writeJsonData("menu.json", jsonData);

    cout << "Блюдо успешно добавлено!" << endl;

    // Очистка буфера ввода
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Ожидание нажатия клавиши пользователем
    system("pause");
    system("cls");
}



void Menu::removeDish() {
    //clearConsole();

    //// Чтение данных из файла
    //ifstream inFile("menu.txt");
    //if (!inFile.is_open()) {
    //    cout << "Ошибка открытия файла для чтения данных." << endl;
    //    return;
    //}

    //// Вектор для хранения блюд из файла
    //vector<MenuItem> fileItems;

    //string line;
    //MenuItem dish;

    //// Читаем данные из файла и сохраняем блюда в векторе
    //while (getline(inFile, line)) {
    //    if (line == "===") {
    //        fileItems.push_back(dish);
    //        dish = MenuItem(); // Сбрасываем dish для следующего блюда
    //    }
    //    else if (!line.empty()) {
    //        switch (fileItems.size() % 5) {
    //        case 0: {
    //            // Получаем название и цену из строки
    //            size_t pricePos = line.find_last_of(' ');
    //            dish.name = line.substr(0, pricePos);
    //            try {
    //                dish.cost = stod(line.substr(pricePos + 1));
    //            }
    //            catch (const std::invalid_argument&) {
    //                cout << "Ошибка преобразования цены блюда. Пропускаем блюдо." << endl;
    //                continue;
    //            }
    //            break;
    //        }
    //        case 1: dish.weight = line; break;
    //        case 2: dish.description = line; break;
    //        case 3: dish.cookingTime = line; break;
    //        case 4: dish.cost = stod(line); break;
    //        }
    //    }
    //}
    //inFile.close();

    //// Выводим наименования блюд в консоль
    //if (fileItems.empty()) {
    //    cout << "В меню нет доступных блюд." << endl;
    //    return;
    //}

    //cout << "Список доступных блюд:" << endl;
    //for (const auto& item : fileItems) {
    //    cout << "- " << item.name << endl;
    //}

    //// Просим пользователя ввести название блюда для удаления
    //string dishName;
    //cout << "Введите название блюда для удаления: ";
    //cin.ignore();
    //getline(cin, dishName);

    //// Поиск и удаление блюда
    //bool found = false;
    //for (auto it = fileItems.begin(); it != fileItems.end(); ++it) {
    //    if (it->name == dishName) {
    //        fileItems.erase(it);
    //        found = true;
    //        break;
    //    }
    //}

    //if (found) {
    //    // Перезаписываем данные в файле без удаленного блюда
    //    ofstream outFile("menu.txt");
    //    if (outFile.is_open()) {
    //        for (const auto& item : fileItems) {
    //            outFile << item.name << " " << item.cost << endl;
    //            outFile << item.weight << endl;
    //            outFile << item.description << endl;
    //            outFile << item.cookingTime << endl;
    //            outFile << item.cost << endl;
    //            outFile << "===" << endl;
    //        }
    //        outFile.close();
    //        cout << "Блюдо успешно удалено из меню." << endl;
    //    }
    //    else {
    //        cout << "Ошибка открытия файла для записи данных." << endl;
    //    }
    //}
    //else {
    //    cout << "Блюдо с указанным названием не найдено." << endl;
    //}

    //Sleep(1500);
    //clearConsole();
}


void Menu::editDish() {
    /*cout << "";*/
}
