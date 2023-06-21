#include "JsonHelper.h"
#include "Product.h"
#include "Menu.h"
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

void User::editMenu() {
    system("cls");
    int choice;

    while (true) {
        cout << "Редактирование меню\n";
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

        Menu menu;

        switch (choice) {
        case 1:
            menu.addDish();
            editMenu();
            break;
        case 2:
            menu.removeDish();
            return;
            break;
        case 3:
            menu.editDish();
            return;
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
void User::editProductList() {
    system("cls");
    int choice;

    while (true) {
        cout << "1. Добавить продукт\n";
        cout << "2. Изменить продукт\n";
        cout << "3. Удалить продукт\n";
        cout << "4. Вернуться в предыдущее меню\n";
        cout << "Выберите действие: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        Menu menu;

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
            return;
        default:
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
            break;
        }
    }
}

void User::addProduct() {
    system("cls");
    Product product;

    cout << "Введите ID продукта: ";
    cin >> product.id;

    cout << "Введите наименование продукта: ";
    cin.ignore();
    getline(cin, product.name);

    cout << "Введите цену продукта: ";
    cin >> product.price;

    vector<Product> products;

    // Добавляем продукт в список продуктов
    // Например, если список продуктов хранится в векторе products
    products.push_back(product);

    // Сохранение данных в файл
    ofstream outFile("products.txt", ios::app); // Открываем файл для добавления данных в конец
    if (outFile.is_open()) {
        outFile << product.id << endl;
        outFile << product.name << endl;
        outFile << product.price << endl;
        outFile << "===" << endl; // Разделитель между продуктами
        outFile.close();
        cout << "Данные успешно сохранены в файл." << endl;
    }
    else {
        cout << "Ошибка открытия файла для сохранения данных." << endl;
    }

    Sleep(1500);
    system("cls");
}


void User::editProduct() {
    system("cls");

    // Чтение данных из файла
    ifstream inFile("products.txt");
    if (!inFile.is_open()) {
        cout << "Ошибка открытия файла для чтения данных." << endl;
        return;
    }

    // Вектор для хранения продуктов из файла
    vector<Product> fileProducts;

    string line;
    Product product;

    // Читаем данные из файла и сохраняем продукты в векторе
    while (getline(inFile, line)) {
        if (line == "===") {
            fileProducts.push_back(product);
            product = Product(); // Сбрасываем product для следующего продукта
        }
        else if (!line.empty()) {
            switch (fileProducts.size() % 3) {
            case 0:
                try {
                    product.id = stoi(line);
                }
                catch (const std::invalid_argument&) {
                    cout << "Ошибка чтения ID продукта из файла." << endl;
                    inFile.close();
                    return;
                }
                break;
            case 1:
                product.name = line;
                break;
            case 2:
                try {
                    product.price = stod(line);
                }
                catch (const std::invalid_argument&) {
                    cout << "Ошибка чтения цены продукта из файла." << endl;
                    inFile.close();
                    return;
                }
                break;
            }
        }
    }

    inFile.close();

    // Выводим список продуктов из файла
    cout << "Список продуктов:" << endl;
    for (const auto& prod : fileProducts) {
        cout << "ID: " << prod.id << endl;
        cout << "Наименование: " << prod.name << endl;
        cout << "Цена: " << prod.price << endl;
        cout << "=====================" << endl;
    }

    // Запрашиваем ID продукта, который нужно изменить
    int id;
    cout << "Введите ID продукта, который нужно изменить: ";
    cin >> id;

    // Ищем продукт с указанным ID в векторе продуктов
    auto it = find_if(fileProducts.begin(), fileProducts.end(), [id](const Product& p) {
        return p.id == id;
        });

    if (it != fileProducts.end()) {
        // Найден продукт, запрашиваем новые данные
        cout << "Введите новое наименование продукта: ";
        cin.ignore();
        getline(cin, it->name);

        cout << "Введите новую цену продукта: ";
        cin >> it->price;

        // Сохраняем изменения в файле
        ofstream outFile("products.txt");
        if (outFile.is_open()) {
            for (const auto& prod : fileProducts) {
                outFile << prod.id << endl;
                outFile << prod.name << endl;
                outFile << prod.price << endl;
                outFile << "===" << endl; // Разделитель между продуктами
            }
            outFile.close();
            cout << "Данные успешно сохранены в файл." << endl;
        }
        else {
            cout << "Ошибка открытия файла для сохранения данных." << endl;
        }
    }
    else {
        cout << "Продукт с указанным ID не найден." << endl;
    }
}

void User::removeProduct() {
    system("cls");

    // Чтение данных из файла
    ifstream inFile("products.txt");
    if (!inFile.is_open()) {
        cout << "Ошибка открытия файла для чтения данных." << endl;
        return;
    }

    // Вектор для хранения продуктов из файла
    vector<Product> fileProducts;

    string line;
    Product product;

    // Читаем данные из файла и сохраняем продукты в векторе
    while (getline(inFile, line)) {
        if (line == "===") {
            fileProducts.push_back(product);
            product = Product(); // Сбрасываем product для следующего продукта
        }
        else if (!line.empty()) {
            switch (fileProducts.size() % 3) {
            case 0:
                try {
                    product.id = stoi(line);
                }
                catch (const std::invalid_argument&) {
                    cout << "Ошибка чтения ID продукта из файла." << endl;
                    inFile.close();
                    return;
                }
                break;
            case 1:
                product.name = line;
                break;
            case 2:
                try {
                    product.price = stod(line);
                }
                catch (const std::invalid_argument&) {
                    cout << "Ошибка чтения цены продукта из файла." << endl;
                    inFile.close();
                    return;
                }
                break;
            }
        }
    }

    inFile.close();

    // Выводим список продуктов из файла
    cout << "Список продуктов:" << endl;
    for (const auto& prod : fileProducts) {
        cout << "ID: " << prod.id << endl;
        cout << "Наименование: " << prod.name << endl;
        cout << "Цена: " << prod.price << endl;
        cout << "=====================" << endl;
    }

    // Запрашиваем ID продукта, который нужно удалить
    int id;
    cout << "Введите ID продукта, который нужно удалить: ";
    cin >> id;

    // Ищем продукт с указанным ID в векторе продуктов
    auto it = find_if(fileProducts.begin(), fileProducts.end(), [id](const Product& p) {
        return p.id == id;
        });

    if (it != fileProducts.end()) {
        // Найден продукт, удаляем его из вектора
        fileProducts.erase(it);

        // Сохраняем изменения в файле
        ofstream outFile("products.txt");
        if (outFile.is_open()) {
            for (const auto& prod : fileProducts) {
                outFile << prod.id << endl;
                outFile << prod.name << endl;
                outFile << prod.price << endl;
                outFile << "===" << endl; // Разделитель между продуктами
            }
            outFile.close();
            cout << "Продукт успешно удален." << endl;
        }
        else {
            cout << "Ошибка открытия файла для сохранения данных." << endl;
        }
    }
    else {
        cout << "Продукт с указанным ID не найден." << endl;
    }
}



void User::editEmployees()
{
    JsonHelper jsonHelper;
    system("cls");
    // Загружаем данные из файла
    json jsonData = jsonHelper.readJsonData("users.json");

    // Выводим список сотрудников
    std::cout << "Список сотрудников:\n";
    for (const auto& user : jsonData["users"]) {
        std::cout << "Имя: " << user["firstName"] << std::endl;
        std::cout << "Фамилия: " << user["lastName"] << std::endl;
        std::cout << "Отчество: " << user["patronymic"] << std::endl;
        std::cout << "Логин: " << user["username"] << std::endl;
        std::cout << "Пароль: " << user["password"] << std::endl;
        std::cout << "Роль: " << user["role"] << std::endl;
        std::cout << "-----------------------\n";
    }

    // Получаем логин сотрудника, которого нужно редактировать
    std::string editUsername;
    std::cout << "Введите логин сотрудника для редактирования: ";
    std::cin.ignore();
    std::getline(std::cin, editUsername);

    // Поиск сотрудника с указанным логином
    bool found = false;
    for (auto& user : jsonData["users"]) {
        if (user["username"] == editUsername) {
            found = true;
            std::string firstName, lastName, patronymic, newUsername, newPassword, newRole;

            std::cout << "Редактирование данных сотрудника:\n";

            // Редактирование ФИО
            std::cout << "Новое имя: ";
            std::getline(std::cin, firstName);
            user["firstName"] = firstName;

            std::cout << "Новая фамилия: ";
            std::getline(std::cin, lastName);
            user["lastName"] = lastName;

            std::cout << "Новое отчество: ";
            std::getline(std::cin, patronymic);
            user["patronymic"] = patronymic;

            // Редактирование логина
            std::cout << "Новый логин: ";
            std::getline(std::cin, newUsername);
            user["username"] = newUsername;

            // Редактирование пароля
            std::cout << "Новый пароль: ";
            std::getline(std::cin, newPassword);
            user["password"] = newPassword;

            // Редактирование роли
            std::cout << "Новая роль: ";
            std::getline(std::cin, newRole);
            user["role"] = newRole;

            std::cout << "Данные сотрудника успешно обновлены.\n";
            break;
        }
    }

    // Сохраняем обновленные данные в файл
    if (found) {
        jsonHelper.writeJsonData("users.json", jsonData);
    }
    else {
        std::cout << "Сотрудник с указанным логином не найден.\n";
    }
}



void User::guestMenu() {
    cout << "Меню гостя" << endl;
    // Добавьте функциональность для меню гостя
}

void User::adminMenu() {
    int choice;

    while (true) {
        cout << "Редактировать:\n";
        cout << "1. Меню\n";
        cout << "2. Список продуктов\n";
        cout << "3. Учётные записи\n";
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
            editMenu();
            break;
        case 2:
            editProductList();
            break;
        case 3:
            editEmployees();
            break;
        case 4:
            return;  // Выход из функции adminMenu() и возврат к месту вызова
        default:
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
            break;
        }
    }
}

void User::skladMenu() {
    system("cls");
    int choice;

    while (true) {
        cout << "1. Создать заявку\n";
        cout << "1. Посмотреть склад\n";
        cout << "Выберите действие: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
            cin.clear();
            system("cls");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        Menu menu;

        switch (choice) {
        case 1:
            menu.addDish();
            editMenu();
            break;
        case 2:
            menu.removeDish();
            return;
            break;
        case 3:
            menu.editDish();
            return;
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
