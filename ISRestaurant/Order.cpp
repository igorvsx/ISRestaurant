#include "Order.h"
#include "JsonHelper.h"

void TrunkTxt() {
    std::ofstream balanceFile;
    balanceFile.open("RestBalance.txt", std::ofstream::out | std::ofstream::trunc);
    balanceFile.close();
}

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

    // Загрузка данных о продуктах
    json productData = jsonHelper.readJsonData("products.json");

    // Вывод списка продуктов
    std::cout << "Список продуктов:\n";
    for (const auto& product : productData["products"]) {
        std::cout << "ID: " << product["id"] << std::endl;
        std::cout << "Наименование: " << product["name"] << std::endl;
        std::cout << "Цена: " << product["price"] << std::endl;
        std::cout << "-----------------------\n";
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

    // Добавление новой заявки в список
    orderData["orders"].push_back(newOrder);

    // Сохранение обновленных данных в файле
    jsonHelper.writeJsonData("orders.json", orderData);

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
        std::cout << "Деньги успешно списаны с баланса ресторана." << std::endl;
    }
    else {
        std::cout << "Ошибка при обновлении баланса ресторана." << std::endl;
    }
}

void Order::displayOrders() {
    JsonHelper jsonHelper;
    system("cls");

    // Загружаем данные о заявках из файла
    json orderData = jsonHelper.readJsonData("orders.json");

    if (orderData.empty()) {
        std::cout << "Нет доступных заявок." << std::endl;
        system("pause");
        system("cls");
        return;
    }

    // Выводим список заявок
    std::cout << "Список заявок:\n";
    for (const auto& order : orderData) {
        int productId = order["product_id"];
        int quantityPro = order["quantity"];

        std::cout << "ID продукта: " << productId << std::endl;

        // Получаем информацию о продукте по ID из файла "products.json"
        json productData = jsonHelper.getProductData(productId);
        if (!productData.empty()) {
            std::cout << "Наименование: " << productData["name"] << std::endl;
            std::cout << "Цена за штуку: " << productData["price"] << std::endl;
            std::cout << "Количество: " << quantityPro << std::endl;
            std::cout << "Общая стоимость: " << productData["price"] * quantityPro << std::endl;
            std::cout << "-----------------------\n";
        }
    }

    system("pause");
    system("cls");
}
