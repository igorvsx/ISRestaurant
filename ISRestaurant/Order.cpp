#include "Order.h"
#include "JsonHelper.h"
#include <ctime>
#include <set>
#include <string>
#include <windows.h>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

double getBalance() {
    std::ifstream balanceFile("RestBalance.txt");
    if (!balanceFile) {
        // Обработка ошибки чтения файла
        std::cerr << "Ошибка открытия файла RestBalance.txt." << std::endl;
        return 0.0; // Возвращаем 0 в случае ошибки
    }

    double balance;
    if (!(balanceFile >> balance)) {
        // Обработка ошибки чтения значения баланса
        std::cerr << "Ошибка чтения баланса из файла RestBalance.txt." << std::endl;
        return 0.0; // Возвращаем 0 в случае ошибки
    }

    balanceFile.close();
    return balance;
}

void Order::createOrder() {
    JsonHelper jsonHelper;
    system("cls");

    std::time_t currentTime = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &currentTime);
    char timeBuffer[26];
    asctime_s(timeBuffer, sizeof(timeBuffer), &localTime);
    std::string sendTime(timeBuffer);

    // Загрузка данных о продуктах
    json productData = jsonHelper.readJsonData("products.json");

    // Вывод списка продуктов
    std::cout << "Список продуктов:\n";
    std::set<int> printedIds; // Контейнер для отслеживания уже выведенных ID
    for (const auto& product : productData["products"]) {
        int productId = product["id"].get<int>();
        if (printedIds.find(productId) == printedIds.end()) {
            // Продукт с данным ID еще не был выведен, выводим его
            printedIds.insert(productId); // Добавляем ID в контейнер уже выведенных ID
            std::cout << "ID: " << productId << std::endl;
            std::cout << "Наименование: " << product["name"] << std::endl;
            std::cout << "Цена: " << product["price"] << std::endl;
            std::cout << "-----------------------\n";
        }
    }

    // Ввод данных для заявки
    int productId;
    int quantity;

    std::cout << "Введите ID продукта: ";
    std::cin >> productId;

    std::cout << "Введите количество: ";
    std::cin >> quantity;

    // Получение данных о выбранном продукте
    json selectedProduct = jsonHelper.getProductData(productId);

    // Проверка наличия выбранного продукта
    if (selectedProduct.empty()) {
        std::cout << "Продукт с указанным ID не найден." << std::endl;
        system("pause");
        system("cls");
        return;
    }

    // Расчет суммы заявки
    double totalPrice = selectedProduct["price"].get<double>() * quantity;

    // Загрузка баланса ресторана из файла
    double balance = getBalance();

    // Проверка баланса ресторана
    if (balance < totalPrice) {
        std::cout << "Недостаточно средств на балансе ресторана." << std::endl;
        system("pause");
        system("cls");
        return;
    }

    // Загрузка данных о существующих заявках из файла
    json orderData = jsonHelper.readJsonData("orders.json");

    // Создание новой заявки
    json newOrder;
    newOrder["product_id"] = productId;
    newOrder["product_name"] = selectedProduct["name"];
    newOrder["quantity"] = quantity;
    newOrder["send_time"] = sendTime;

    // Добавление новой заявки в список
    orderData["orders"].push_back(newOrder);

    // Сохранение обновленных данных в файле
    jsonHelper.writeJsonData("orders.json", orderData);

    // Сохранение отправленной заявки в файл "SendOrders.json"
    json sendOrdersData = jsonHelper.readJsonData("SendOrders.json");
    sendOrdersData["SendOrders"].push_back(newOrder);
    jsonHelper.writeJsonData("SendOrders.json", sendOrdersData);

    std::cout << "Заявка успешно создана." << std::endl;

    system("pause");
    system("cls");
}

void Order::withdrawFunds(double amount){
    double currentBalance = getBalance();

    // Проверка наличия достаточных средств
    if (currentBalance < amount) {
        std::cout << "Недостаточно средств на балансе ресторана." << std::endl;
        return;
    }

    // Вычитание суммы списания
    double updatedBalance = currentBalance - amount;

    // Обновление баланса в файле
    std::ofstream balanceFile("RestBalance.txt");
    if (balanceFile.is_open()) {
        balanceFile << updatedBalance;
        balanceFile.close();
        //std::cout << "Деньги успешно списаны с баланса ресторана." << std::endl;
    }
    else {
        std::cout << "Ошибка при обновлении баланса ресторана." << std::endl;
    }
}

void Order::printSendOrders() {
    system("cls");
    JsonHelper jsonHelper;


    // Чтение данных из файла "SendOrders.json"
    json sendOrderData = jsonHelper.readJsonData("SendOrders.json");

    // Проверка наличия заявок
    if (sendOrderData["SendOrders"].empty()) {
        std::cout << "Список отправленных заявок пуст." << std::endl;
        return;
    }

    // Вывод списка отправленных заявок
    std::cout << "Список отправленных заявок:" << std::endl;
    for (const auto& sendOrder : sendOrderData["SendOrders"]) {
        std::cout << "Название продукта: " << sendOrder["product_name"] << std::endl;
        std::cout << "Количество: " << sendOrder["quantity"] << std::endl;
        std::cout << "Время отправки: " << sendOrder["send_time"] << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
    int choice;
    std::cout << "Введите любой символ для выхода: ";
    std::cin >> choice;
    switch (choice) {
    default:
        return;
    }
}

void Order::ordersList() {
    JsonHelper jsonHelper;
    system("cls");


    std::time_t currentTime = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &currentTime);
    char timeBuffer[26];
    asctime_s(timeBuffer, sizeof(timeBuffer), &localTime);
    std::string sendTime(timeBuffer);


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
        Sleep(1500);
        system("cls");
        return;
    }

    withdrawFunds(amount);
    for (int i = 0; i < quantity; ++i) {
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
                {"date_executed", sendTime} 
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

void Order::printAcceptOrders() {
    system("cls");
    JsonHelper jsonHelper;


    // Чтение данных из файла "DoneOrders.json"
    json doneOrderData = jsonHelper.readJsonData("DoneOrders.json");

    // Проверка наличия заявок
    if (doneOrderData["DoneOrders"].empty()) {
        std::cout << "Список принятых продуктов пуст." << std::endl;
        return;
    }

    // Вывод списка отправленных заявок
    std::cout << "Список принятых продуктов:" << std::endl;
    for (const auto& doneOrder : doneOrderData["DoneOrders"]) {
        cout << "Дата: " << doneOrder["date_executed"] << endl;
        cout << "ID продукта: " << doneOrder["product_id"] << endl;
        cout << "Название продукта: " << doneOrder["product_name"] << endl;
        std::cout << "Количество: " << doneOrder["quantity"] << std::endl;
        std::cout << "-----------------------" << std::endl;
    }
    int choice;
    std::cout << "Введите любой символ для выхода: ";
    std::cin >> choice;
    switch (choice) {
    default:
        return;
    }
}