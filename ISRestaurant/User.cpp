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


void User::editingEmployees() {
    system("cls");

    int choice;

    while (true) {
        cout << "Редактирование учетных записей:\n";
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
            addEmployees();
            break;
        case 2:
            editEmployees();
            break;
        case 3:
            removeEmployees();
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
void User::addEmployees()
{
    JsonHelper jsonHelper;
    system("cls");

    // Загружаем данные из файла
    json jsonData = jsonHelper.readJsonData("users.json");

    std::string firstName, lastName, patronymic, username, password, role;

    std::cout << "Добавление нового сотрудника:\n";

    // Ввод данных сотрудника
    std::cout << "Имя: ";
    std::cin.ignore();
    std::getline(std::cin, firstName);

    std::cout << "Фамилия: ";
    std::getline(std::cin, lastName);

    std::cout << "Отчество: ";
    std::getline(std::cin, patronymic);

    std::cout << "Логин: ";
    std::getline(std::cin, username);

    std::cout << "Пароль: ";
    std::getline(std::cin, password);

    std::cout << "Роль: ";
    std::getline(std::cin, role);

    // Создание объекта сотрудника
    json newEmployee;
    newEmployee["firstName"] = firstName;
    newEmployee["lastName"] = lastName;
    newEmployee["patronymic"] = patronymic;
    newEmployee["username"] = username;
    newEmployee["password"] = password;
    newEmployee["role"] = role;

    // Добавление нового сотрудника в список
    jsonData["users"].push_back(newEmployee);

    // Сохраняем обновленные данные в файл
    jsonHelper.writeJsonData("users.json", jsonData);

    std::cout << "Сотрудник успешно добавлен.\n";
    Sleep(1500);
    system("cls");
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
        Sleep(1500);
        system("cls");
    }
    else {
        std::cout << "Сотрудник с указанным логином не найден.\n";
        Sleep(1500);
        system("cls");
    }
}
void User::removeEmployees()
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
    std::string deleteUsername;
    std::cout << "Введите логин сотрудника для удаления: ";
    std::cin.ignore();
    std::getline(std::cin, deleteUsername);

    // Поиск сотрудника с указанным логином
    bool found = false;
    size_t index = 0;
    while (index < jsonData["users"].size()) {
        if (jsonData["users"][index]["username"] == deleteUsername) {
            found = true;
            jsonData["users"].erase(jsonData["users"].begin() + index);
            std::cout << "Сотрудник успешно удален.\n";
            break;
        }
        else {
            index++;
        }
    }

    // Сохраняем обновленные данные в файл
    if (found) {
        jsonHelper.writeJsonData("users.json", jsonData);
        Sleep(1500);
        system("cls");
    }
    else {
        std::cout << "Сотрудник с указанным логином не найден.\n";
        Sleep(1500);
        system("cls");
    }
}


void User::guestMenu() {
    cout << "Меню гостя" << endl;
    // Добавьте функциональность для меню гостя
}

void User::adminMenu() {
    int choice;
    Menu menu;
    Product product;

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
            menu.editMenu();
            break;
        case 2:
            product.editingProducts();
            break;
        case 3:
            editingEmployees();
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
            menu.editMenu();
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


