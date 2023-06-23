#include "JsonHelper.h"
#include "Product.h"
#include "Menu.h"
#include "User.h"
#include "ISRestaurant.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#define NOMINMAX
#include <windows.h>
#include "Order.h"
#include "Guest.h"

using namespace std;


void User::editingEmployees() {
    system("cls");

    int choice;

    while (true) {
        cout << "Редактирование учетных записей:\n";
        cout << "1. Список учетных записей\n";
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
            listEmployees();
            break;
        case 2:
            addEmployees();
            break;
        case 3:
            editEmployees();
            break;
        case 4:
            removeEmployees();
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

    string newHashedPass = hashPassword(password);

    std::cout << "Роль: ";
    std::getline(std::cin, role);

    // Создание объекта сотрудника
    json newEmployee;
    newEmployee["firstName"] = firstName;
    newEmployee["lastName"] = lastName;
    newEmployee["patronymic"] = patronymic;
    newEmployee["username"] = username;
    newEmployee["password"] = newHashedPass;
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

            string newHashedPass = hashPassword(newPassword);

            user["password"] = newHashedPass;

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
void User::listEmployees() {
    JsonHelper jsonHelper;
    system("cls");

    // Загружаем данные из файла
    json jsonData = jsonHelper.readJsonData("users.json");

    // Создаем вектор для хранения информации о пользователях
    std::vector<User> users;

    // Извлекаем данные о пользователях из JSON
    for (const auto& user : jsonData["users"]) {
        User currentUser;
        currentUser.firstName = user["firstName"];
        currentUser.lastName = user["lastName"];
        currentUser.password = user["password"];
        currentUser.patronymic = user["patronymic"];
        currentUser.role = user["role"];
        currentUser.username = user["username"];
        users.push_back(currentUser);
    }

    // Определяем количество записей на странице
    const int itemsPerPage = 5;
    int totalPages = (users.size() + itemsPerPage - 1) / itemsPerPage; // Округление вверх

    // Выводим список пользователей с информацией
    std::cout << "Список пользователей:\n";
    int startIndex = 0;
    int currentPage = 1;

    while (true) {
        int endIndex = std::min(startIndex + itemsPerPage, static_cast<int>(users.size()));

        for (int i = startIndex; i < endIndex; ++i) {
            std::cout << "Имя: " << users[i].firstName << std::endl;
            std::cout << "Фамилия: " << users[i].lastName << std::endl;
            std::cout << "Отчество: " << users[i].patronymic << std::endl;
            std::cout << "Роль: " << users[i].role << std::endl;
            std::cout << "Имя пользователя: " << users[i].username << std::endl;
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


void User::printBalance(const std::string& filename) {
    system("cls");

    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        std::string balanceStr;
        std::getline(inputFile, balanceStr); // Читаем строку с балансом из файла

        try {
            double balance = std::stod(balanceStr); // Преобразуем строку в число (тип double)
            std::cout << "Баланс: " << balance << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "Ошибка при чтении баланса из файла: " << e.what() << std::endl;
        }

        inputFile.close();
    }
    else {
        std::cout << "Не удалось открыть файл: " << filename << std::endl;
    }

    int choice;
    std::cout << "Введите любой символ для выхода: ";
    std::cin >> choice;
    switch (choice) {
    default:
        return;
    }
}

void User::makeOrder() {

}

void User::guestMenu() {

    system("cls");
    int choice;
    Menu menu;
    Product product;
    Guest guest;

    while (true) {
        cout << "1. Сделать заказ\n";
        cout << "2. Выход\n";
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
            guest.createOrder();
            break;
        case 2:
            system("cls");
            return;
        default:
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
            break;
        }
    }
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
        cout << "1. Посмотреть склад\n";
        cout << "2. Создать заявку\n";
        cout << "3. Выйти\n";
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
        Product product;
        Order order;

        switch (choice) {
        case 1:
            product.productList();
            break;
        case 2:
            order.createOrder();
            break;
        case 3:
            return;
        default:
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
            system("cls");
            break;
        }
    }
}

void User::supplierMenu() {
    Order order;
    system("cls");
    int choice;

    while (true) {
        cout << "1. Посмотреть заявки\n";
        cout << "2. Выйти\n";
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
            order.ordersList();
            break;
        case 2:
            return;
        default:
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
            system("cls");
            break;
        }
    }
}

void User::accountantMenu() {
    Order order;
    system("cls");
    int choice;

    while (true) {
        cout << "1. Посмотреть отправленные заявки\n";
        cout << "2. Посмотреть принятые поставки\n";
        cout << "3. Посмотреть баланс ресторана\n";
        cout << "4. Выход\n";
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
            order.printSendOrders();
            break;
        case 2:
            order.printAcceptOrders();
            break;
        case 3:
            printBalance("RestBalance.txt");
            break;
        case 4:
            return;
        default:
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
            system("cls");
            break;
        }
    }
}








