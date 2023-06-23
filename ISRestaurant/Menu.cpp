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
        cout << "1. Список блюд\n";
        cout << "2. Добавить блюдо\n";
        cout << "3. Удалить блюдо\n";
        cout << "4. Редактировать блюдо\n";
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
            listDishes();
            break;
        case 2:
            addDish();
            editMenu();
            break;
        case 3:
            removeDish();
            break;
        case 4:
            editDish();
            break;
        case 5:
            system("cls");
            return;  
            break; // Выход из функции editMenu() и возврат к предыдущему меню
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

    json productsData = jsonHelper.readJsonData("products.json");

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

        bool found = false;

        for (const auto& selectedProduct : productsData["products"]) {
            if (selectedProduct["id"] == product.id) {
                found = true;
                // Создаем новый продукт на основе найденного продукта
                Product newIngredient;
                newIngredient.id = selectedProduct["id"];
                newIngredient.name = selectedProduct["name"];
                newIngredient.price = selectedProduct["price"];
                newDish.ingredients.push_back(newIngredient);
                break;
            }
        }

        if (!found) {
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
    json menuData = jsonHelper.readJsonData("menu.json");

    // Добавление нового блюда в JSON-данные
    json dishJson;

    dishJson["name"] = newDish.name;
    dishJson["weight"] = newDish.weight;

    json ingredientsJson = json::array();
    for (const auto& ingredient : newDish.ingredients) {
        json ingredientJson = {
            {"id", ingredient.id},
            {"name", ingredient.name},
            {"price", ingredient.price}
        };
        ingredientsJson.push_back(ingredientJson);
    }

    dishJson["ingredients"] = ingredientsJson;

    dishJson["description"] = newDish.description;
    dishJson["cookingTime"] = newDish.cookingTime;
    dishJson["cost"] = newDish.cost;

    menuData["menu"].push_back(dishJson);

    // Сохранение обновленных данных в JSON-файл
    jsonHelper.writeJsonData("menu.json", menuData);

    cout << "Блюдо успешно добавлено!" << endl;

    // Очистка буфера ввода
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Ожидание нажатия клавиши пользователем
    system("pause");
    system("cls");
}

void Menu::removeDish()
{
    JsonHelper jsonHelper;

    system("cls");

    // Загрузка данных из JSON-файла
    json jsonData = jsonHelper.readJsonData("menu.json");

    // Проверка наличия записей в меню
    if (jsonData["menu"].empty()) {
        cout << "Меню пусто. Нет записей для удаления." << endl;
        system("pause");
        system("cls");
        return;
    }

    // Вывод текущего меню с номерами записей
    cout << "Текущее меню:\n";
    for (size_t i = 0; i < jsonData["menu"].size(); ++i) {
        cout << "Запись " << i + 1 << ":\n";
        cout << "Название: " << jsonData["menu"][i]["name"].get<string>() << endl;
        cout << "Описание: " << jsonData["menu"][i]["description"].get<string>() << endl;
        cout << "--------------------------\n";
    }

    // Ввод номера записи для удаления
    int recordNumber;
    cout << "Введите номер записи для удаления: ";
    cin >> recordNumber;

    // Проверка введенного номера записи
    if (recordNumber <= 0 || recordNumber > jsonData["menu"].size()) {
        cout << "Введен некорректный номер записи." << endl;
        system("pause");
        system("cls");
        return;
    }

    // Удаление выбранной записи
    jsonData["menu"].erase(jsonData["menu"].begin() + recordNumber - 1);

    // Сохранение обновленных данных в JSON-файл
    jsonHelper.writeJsonData("menu.json", jsonData);

    cout << "Запись успешно удалена!" << endl;

    system("pause");
    system("cls");
}

void Menu::editDish()
{
    JsonHelper jsonHelper;

    system("cls");

    // Загрузка данных из JSON-файла
    json jsonData = jsonHelper.readJsonData("menu.json");
    json productsData = jsonHelper.readJsonData("products.json");

    // Проверка наличия записей в меню
    if (jsonData["menu"].empty()) {
        cout << "Меню пусто. Нет записей для редактирования." << endl;
        system("pause");
        system("cls");
        return;
    }

    // Вывод текущего меню с номерами записей
    cout << "Текущее меню:\n";
    for (size_t i = 0; i < jsonData["menu"].size(); ++i) {
        cout << "Запись " << i + 1 << ":\n";
        cout << "Название: " << jsonData["menu"][i]["name"].get<string>() << endl;
        cout << "Описание: " << jsonData["menu"][i]["description"].get<string>() << endl;
        cout << "--------------------------\n";
    }

    // Ввод номера записи для редактирования
    int recordNumber;
    cout << "Введите номер записи для редактирования: ";
    cin >> recordNumber;

    // Проверка введенного номера записи
    if (recordNumber <= 0 || recordNumber > jsonData["menu"].size()) {
        cout << "Введен некорректный номер записи." << endl;
        system("pause");
        system("cls");
        return;
    }

    // Выбор редактируемой записи
    json& selectedDish = jsonData["menu"][recordNumber - 1];

    // Вывод информации о выбранном блюде
    cout << "Редактирование блюда:\n";
    cout << "Название: " << selectedDish["name"].get<string>() << endl;
    cout << "Описание: " << selectedDish["description"].get<string>() << endl;

    // Внесение изменений
    cin.ignore();
    cout << "Введите новое название блюда: ";
    string newName;
    std::getline(cin, newName);
    selectedDish["name"] = newName;

    cout << "Введите новое описание блюда: ";
    string newDescription;
    std::getline(cin, newDescription);
    selectedDish["description"] = newDescription;

    cout << "Введите новую стоимость блюда: ";
    double newCost;
    cin >> newCost;
    selectedDish["cost"] = newCost;

    cout << "Введите новое время приготовления блюда: ";
    string newCookingTime;
    cin.ignore();
    std::getline(cin, newCookingTime);
    selectedDish["cookingTime"] = newCookingTime;

    cout << "Введите новую граммовку блюда: ";
    string newWeight;
    std::getline(cin, newWeight);
    selectedDish["weight"] = newWeight;

    // Редактирование ингредиентов
    selectedDish["ingredients"].clear();

    //char choice;
    //do {
    //    Product product;
    //    cout << "Введите ID продукта: ";
    //    cin >> product.id;


    //    // Поиск продукта по ID в базе данных и добавление в ингредиенты блюда
    //    bool found = false;
    //    for (const auto& availableProduct : jsonData["products"]) {
    //        if (availableProduct["id"] == product.id) {
    //            found = true;
    //            selectedDish["ingredients"].push_back(availableProduct);
    //            break;
    //        }
    //    }

    //    if (!found) {
    //        cout << "Продукт с указанным ID не найден." << endl;
    //        // Обработка случая, когда продукт не найден
    //    }

    //    cout << "Добавить еще ингредиенты? (y/n): ";
    //    cin >> choice;
    //} while (choice == 'y');

    char choice;
    do {

        Product product;
        cout << "Введите ID продукта: ";
        cin >> product.id;

        bool found = false;

        for (const auto& availableProduct : productsData["products"]) {
            if (availableProduct["id"] == product.id) {
                found = true;
                // Создаем новый продукт на основе найденного продукта
                Product newIngredient;
                newIngredient.id = availableProduct["id"];
                newIngredient.name = availableProduct["name"];
                newIngredient.price = availableProduct["price"];
                selectedDish["ingredients"].push_back(availableProduct);
                break;
            }
        }

        if (!found) {
            cout << "Продукт с указанным ID не найден." << endl;
            // Обработайте случай, когда продукт не найден
        }

        cout << "Добавить еще ингредиенты? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    // Сохранение обновленных данных в JSON-файл
    jsonHelper.writeJsonData("menu.json", jsonData);

    cout << "Запись успешно отредактирована!" << endl;

    system("pause");
    system("cls");
}

void Menu::listDishes() {
    JsonHelper jsonHelper;
    system("cls");

    // Загружаем данные из файла
    json jsonData = jsonHelper.readJsonData("menu.json");

    // Создаем вектор для хранения информации о блюдах
    std::vector<Menu> dishes;

    // Извлекаем данные о блюдах из JSON
    for (const auto& dish : jsonData["menu"]) {
        Menu currentDish;
        currentDish.name = dish["name"];
        currentDish.description = dish["description"];
        currentDish.cookingTime = dish["cookingTime"];
        currentDish.weight = dish["weight"];
        currentDish.cost = dish["cost"];

        // Извлекаем данные об ингредиентах
        for (const auto& ingredient : dish["ingredients"]) {
            Product currentIngredient;
            currentIngredient.id = ingredient["id"];
            currentIngredient.name = ingredient["name"];
            currentIngredient.price = ingredient["price"];
            currentDish.ingredients.push_back(currentIngredient);
        }

        dishes.push_back(currentDish);
    }

    // Определяем количество записей на странице
    const int itemsPerPage = 5;
    int totalPages = (dishes.size() + itemsPerPage - 1) / itemsPerPage; // Округление вверх

    // Выводим список блюд с информацией
    std::cout << "Список блюд:\n";
    int startIndex = 0;
    int currentPage = 1;

    while (true) {
        int endIndex = std::min(startIndex + itemsPerPage, static_cast<int>(dishes.size()));

        for (int i = startIndex; i < endIndex; ++i) {
            std::cout << "Название: " << dishes[i].name << std::endl;
            std::cout << "Описание: " << dishes[i].description << std::endl;
            std::cout << "Время приготовления: " << dishes[i].cookingTime << std::endl;
            std::cout << "Вес: " << dishes[i].weight << std::endl;
            std::cout << "Стоимость: " << dishes[i].cost << std::endl;

            std::cout << "Ингредиенты:\n";
            for (const auto& ingredient : dishes[i].ingredients) {
                std::cout << "  - Название: " << ingredient.name << std::endl;
                std::cout << "    Цена: " << ingredient.price << std::endl;
            }
            std::cout << "-----------------------\n";
        }

        bool isLastPage = currentPage == totalPages;

        // Проверяем, достигнута ли последняя страница
        if (isLastPage) {
            std::cout << "Это последняя страница. Нет доступных записей для загрузки.\n";
            break;
        }

        // Запрашиваем у пользователя загрузку следующей страницы
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

