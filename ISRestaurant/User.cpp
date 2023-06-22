#include "JsonHelper.h"
#include "Product.h"
#include "Menu.h"
#include "User.h"
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
            ordersList();
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
            break;
        case 3:
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

std::string getCurrentDate() {
    std::time_t currentTime = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &currentTime);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);

    return std::string(buffer);
}


void User::ordersList() {
    JsonHelper jsonHelper;
    Order order;
    system("cls");

    // Загрузка данных из JSON-файла
    json orderData = jsonHelper.readJsonData("orders.json");
    json productsData = jsonHelper.readJsonData("products.json");
    json existingData = jsonHelper.readJsonData("DoneOrders.json");

    // Проверка наличия заявок
    if (orderData["orders"].empty()) {
        cout << "Список заявок пуст." << endl;
        Sleep(1500);
        system("cls");
        return;
    }

    
    // Вывод списка заявок
    for (const auto& orderItem : orderData["orders"]) {
        int productId = orderItem["product_id"].get<int>();
        int quantityPro = orderItem["quantity"].get<int>();

        std::cout << "Наименование: " << orderItem["product_name"] << std::endl;
        //std::cout << "Цена за штуку: " << orderItem["price"] << std::endl;
        std::cout << "Количество: " << quantityPro << std::endl;
        //std::cout << "Общая стоимость: " << orderItem["price"] * quantityPro << std::endl;
        std::cout << "-----------------------\n";

        // Получаем информацию о продукте по ID из файла "products.json"
        /*json productData = jsonHelper.getProductData(productId);
        if (!productData.empty()) {
           
        }*/
    }

    string choice;
    double price = 0;
    int quantity = 0;
    double amount = 0;

    cout << "Введите название продукта для отправки: ";
    cin >> choice;

    
    for (const auto& product : productsData["products"]) {
        if (product["name"] == choice) {
            price = product["price"].get<std::double_t>();
            break;
        }
    }

    for (const auto& order : orderData["orders"]) {
        if (order["product_name"] == choice) {
            quantity = order["quantity"].get<std::int16_t>();
            break;
        }
    }

    amount = price * quantity;

    //получаем максимальный id
    int Id = 0;

    // Поиск максимального значения ID
    for (const auto& product : productsData["products"]) {
        if (product["name"] == choice) {
            Id = product["id"].get<int>();
        }
    }

    // Проверка наличия выбранной заявки
    if (choice.empty()) {
        cout << "Заявка с указанным ID не найдена." << endl;
        system("pause");
        system("cls");
        return;
    }

    order.withdrawFunds(amount);
    for (int i = Id; i < quantity; ++i) {
        productsData["products"].push_back({
            {"id", Id},
            {"name", choice},
            {"price", price}
            });
    }

    // Сохранение обновленных данных в файле
    jsonHelper.writeJsonData("products.json", productsData);

    // Поиск и удаление выбранной заявки
    json updatedOrderData;
    for (const auto& order : orderData["orders"]) {
        if (!(order["product_name"] == choice && order["quantity"].get<int>() == quantity)) {
            updatedOrderData.push_back(order);
        }
        else {
            // Заявка выполнена, создаем JSON-объект с информацией о выполненной заявке
            json doneOrderData = {
                {"product_id", order["product_id"]},
                {"product_name", order["product_name"]},
                {"quantity", order["quantity"]},
                {"date_executed", getCurrentDate()} // Здесь getCurrentDate() - метод для получения текущей даты
            };

            // Добавляем выполненную заявку в файл "DoneOrders.json"
            existingData["DoneOrders"].push_back(doneOrderData);
            jsonHelper.writeJsonData("DoneOrders.json", existingData);
        }
    }

    // Замена старых данных новыми данными
    orderData["orders"] = updatedOrderData;


    // Сохранение обновленных данных в JSON-файл
    jsonHelper.writeJsonData("orders.json", orderData);

    cout << "Заявка успешно обработана!" << endl;

    system("pause");
    system("cls");
}


