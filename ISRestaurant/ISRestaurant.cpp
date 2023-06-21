#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <iomanip>
#define NOMINMAX
#include <windows.h>
#include "single_include/nlohmann/json.hpp"

using json = nlohmann::json;

using namespace std;

#pragma region Классы
// Класс "Гость"
class Guest {
public:
    // Функции для работы с заказами
    void createOrder();
    void confirmOrder();
    void trackOrderStatus();
    // ...
};

// Класс "Заказ"
class Order {
public:
    // Функции для работы с пунктами заказа
    void addItem();
    void removeItem();
    void changeItemStatus();
    // ...
};

// Класс "Продукт"
class Product {
public:
    int id;
    string name;
    double price;
};

// Класс "Пункт меню"
class MenuItem {
public:
    string name;
    string weight;
    vector<Product> ingredients;
    string description;
    string cookingTime;
    double cost;
};

// Класс "Меню"
class Menu {
public:
    vector<MenuItem> items;
    // Функции для работы с блюдами
    void addDish();
    void removeDish();
    void editDish();
    // ...
};

// Класс "Сотрудник"
class User {
public:
    string role;
    string lastName;
    string firstName;
    string patronymic;
    string username;
    string password;
    // Функции меню для разных ролей
    void addProduct();
    void editProduct();
    void removeProduct();
    void guestMenu();
    void skladMenu();
    void adminMenu();
    void employeeMenu();
    void editMenu();
    void editProductList();
    void editEmployees();
};
#pragma endregion Классы

#pragma region Очистка консоли
void clearConsole() {
    system("cls");
}
#pragma endregion Очистка консоли


#pragma region Функции работы с меню 
void Menu::addDish() {
    MenuItem dish;

    clearConsole();

    cout << "Введите наименование блюда: ";
    cin.ignore();
    getline(cin, dish.name);

    cout << "Введите граммовку: ";
    getline(cin, dish.weight);

    // Здесь можно реализовать логику для выбора состава продуктов из списка

    cout << "Введите описание блюда: ";
    getline(cin, dish.description);

    cout << "Введите примерное время приготовления: ";
    getline(cin, dish.cookingTime);

    cout << "Введите стоимость блюда: ";
    cin >> dish.cost;

    items.push_back(dish);

    cout << "Блюдо успешно добавлено в меню." << endl;

    Sleep(1500);
    clearConsole();

    // Сохранение данных в файл
    ofstream outFile("menu.txt", ios::app); // Открываем файл для добавления данных в конец
    if (outFile.is_open()) {
        outFile << dish.name << endl;
        outFile << dish.weight << endl;
        outFile << dish.description << endl;
        outFile << dish.cookingTime << endl;
        outFile << dish.cost << endl;
        outFile << "===" << endl; // Разделитель между блюдами
        outFile.close();
        cout << "Данные успешно сохранены в файл." << endl;
    }
    else {
        cout << "Ошибка открытия файла для сохранения данных." << endl;
    }
}

void Menu::removeDish() {
    clearConsole();

    // Чтение данных из файла
    ifstream inFile("menu.txt");
    if (!inFile.is_open()) {
        cout << "Ошибка открытия файла для чтения данных." << endl;
        return;
    }

    // Вектор для хранения блюд из файла
    vector<MenuItem> fileItems;

    string line;
    MenuItem dish;

    // Читаем данные из файла и сохраняем блюда в векторе
    while (getline(inFile, line)) {
        if (line == "===") {
            fileItems.push_back(dish);
            dish = MenuItem(); // Сбрасываем dish для следующего блюда
        }
        else if (!line.empty()) {
            switch (fileItems.size() % 5) {
            case 0: {
                // Получаем название и цену из строки
                size_t pricePos = line.find_last_of(' ');
                dish.name = line.substr(0, pricePos);
                try {
                    dish.cost = stod(line.substr(pricePos + 1));
                }
                catch (const std::invalid_argument&) {
                    cout << "Ошибка преобразования цены блюда. Пропускаем блюдо." << endl;
                    continue;
                }
                break;
            }
            case 1: dish.weight = line; break;
            case 2: dish.description = line; break;
            case 3: dish.cookingTime = line; break;
            case 4: dish.cost = stod(line); break;
            }
        }
    }
    inFile.close();

    // Выводим наименования блюд в консоль
    if (fileItems.empty()) {
        cout << "В меню нет доступных блюд." << endl;
        return;
    }

    cout << "Список доступных блюд:" << endl;
    for (const auto& item : fileItems) {
        cout << "- " << item.name << endl;
    }

    // Просим пользователя ввести название блюда для удаления
    string dishName;
    cout << "Введите название блюда для удаления: ";
    cin.ignore();
    getline(cin, dishName);

    // Поиск и удаление блюда
    bool found = false;
    for (auto it = fileItems.begin(); it != fileItems.end(); ++it) {
        if (it->name == dishName) {
            fileItems.erase(it);
            found = true;
            break;
        }
    }

    if (found) {
        // Перезаписываем данные в файле без удаленного блюда
        ofstream outFile("menu.txt");
        if (outFile.is_open()) {
            for (const auto& item : fileItems) {
                outFile << item.name << " " << item.cost << endl;
                outFile << item.weight << endl;
                outFile << item.description << endl;
                outFile << item.cookingTime << endl;
                outFile << item.cost << endl;
                outFile << "===" << endl;
            }
            outFile.close();
            cout << "Блюдо успешно удалено из меню." << endl;
        }
        else {
            cout << "Ошибка открытия файла для записи данных." << endl;
        }
    }
    else {
        cout << "Блюдо с указанным названием не найдено." << endl;
    }

    Sleep(1500);
    clearConsole();
}


void Menu::editDish() {
    cout << "";
}
#pragma endregion
#pragma region Методы

void User::editMenu() {
    clearConsole();
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
            clearConsole();
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
            clearConsole();
            break;
        }
    }
}


void User::editProductList() {
    clearConsole();
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
    clearConsole();
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
    clearConsole();
}


void User::editProduct() {
    clearConsole();

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
    clearConsole();

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



void User::editEmployees() {
    cout << "Меню редактирования";
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

void User::employeeMenu() {
    cout << "Меню";
}

void User::skladMenu() {
    clearConsole();
    int choice;

    while (true) {
        cout << "1. Создать заявку\n";
        cout << "1. Посмотреть склад\n";
        cout << "Выберите действие: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Неправильный выбор. Попробуйте еще раз." << endl;
            cin.clear();
            clearConsole();
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
            clearConsole();
            break;
        }
    }
}
#pragma endregion Методы

#pragma region Чтение
json readJsonData(const std::string& filename) {
    std::ifstream inputFile(filename);
    json jsonData;
    if (inputFile.is_open()) {
        inputFile >> jsonData;
        inputFile.close();
    }
    return jsonData;
}
#pragma endregion Чтение

#pragma region Запись
// Запись данных в файл JSON
void writeJsonData(const std::string& filename, const json& jsonData) {
    try {
        std::ofstream file(filename);
        file << std::setw(4) << jsonData << std::endl;
        file.close();
        std::cout << "Данные успешно сохранены в файл: " << filename << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка при записи данных в файл: " << e.what() << std::endl;
    }
}
#pragma endregion Запись

#pragma region Регистрация
// Функция для проверки существования пользователя в файле
bool userExists(const std::string& username) {
    std::ifstream file("users.json");
    if (!file.is_open()) {
        return false;  // Файл не существует, пользователь не найден
    }

    json data;
    file >> data;

    if (data.contains("users")) {
        const json& usersArray = data["users"];
        for (const auto& user : usersArray) {
            if (user["username"] == username) {
                return true;  // Пользователь с таким именем уже существует
            }
        }
    }

    return false;  // Пользователь не найден
}


// Функция для регистрации нового пользователя
void registerUser() {
    std::string role, firstName, lastName, patronymic, username, password;

    cout << "\nВыберите роль пользователя:" << endl;
    cout << "1. Администратор" << endl;
    cout << "2. Складской" << endl;
    cout << "3. Поставщик" << endl;
    cout << "4. Бухгалтер" << endl;
    cout << "5. Повар" << endl;
    cout << "6. Официант" << endl;
    cout << "Ваш выбор: ";
    int roleChoice;
    cin >> roleChoice;

    switch (roleChoice) {
    case 1:
        role = "Admin";
        break;
    case 2:
        role = "Skladskoy";
        break;
    case 3:
        role = "Supplier";
        break;
    case 4:
        role = "Bughalter";
        break;
    case 5:
        role = "Chef";
        break;
    case 6:
        role = "Officiant";
        break;
    default:
        cout << "Неправильный выбор роли." << endl;
        return;
    }

    cout << "Введите Фамилию: ";
    cin >> lastName;

    cout << "Введите Имя: ";
    cin >> firstName;

    cout << "Введите Отчество: ";
    cin >> patronymic;

    // Проверка на уникальность имени пользователя
    bool isUnique = false;
    while (!isUnique) {
        std::cout << "Логин: ";
        std::cin >> username;

        // Загружаем данные из файла
        json jsonData = readJsonData("users.json");

        // Проверяем, существует ли пользователь с таким же именем пользователя
        bool exists = false;
        for (const auto& user : jsonData["users"]) {
            if (user["username"] == username) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            isUnique = true;
        }
        else {
            std::cout << "Пользователь с таким именем пользователя уже существует. Введите другое имя пользователя.\n";
        }
    }

    std::cout << "Пароль: ";
    std::cin >> password;

    // Создаем объект JSON для нового пользователя
    json user;
    user["role"] = role;
    user["firstName"] = firstName;
    user["lastName"] = lastName;
    user["patronymic"] = patronymic;
    user["username"] = username;
    user["password"] = password;

    // Загружаем существующие данные из файла
    json jsonData = readJsonData("users.json");

    // Добавляем нового пользователя в данные
    jsonData["users"].push_back(user);

    // Сохраняем обновленные данные в файл
    writeJsonData("users.json", jsonData);

    std::cout << "Пользователь успешно зарегистрирован!\n";
}

// Функция для авторизации пользователя
bool loginUser(User& user, std::string& role) {
    std::string username, password;

    std::cout << "Логин: ";
    std::cin >> username;
    std::cout << "Пароль: ";
    std::cin >> password;

    // Загружаем данные из файла
    json jsonData = readJsonData("users.json");

    // Поиск пользователя с указанным логином и паролем
    for (const auto& user : jsonData["users"]) {
        if (user["username"] == username && user["password"] == password) {
            role = user["role"];
            clearConsole();
            std::cout << "Пользователь успешно аутентифицирован!" << endl;
            return true;
        }
    }

    std::cout << "Неверный логин или пароль. Попробуйте еще раз.\n";
    return false;
}

#pragma endregion Регистрация

#pragma region main
int main()
{
    setlocale(LC_ALL, "RU");

    int choice;
    bool loggedIn = false;
    User user;
    std::string role;

    while (!loggedIn) {
        std::cout << "1. Регистрация\n2. Авторизация\n3. Войти как гость\n4. Выход\nВыберите действие: ";
        std::cin >> choice;

        // Проверка на некорректный ввод
        if (std::cin.fail()) {
            std::cout << "Неправильный выбор. Попробуйте еще раз." << std::endl << std::endl;
            std::cin.clear();
            Sleep(1500);
            clearConsole();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loggedIn = loginUser(user, role);
            break;
        case 3:
            loggedIn = true;
            role = "Гость";
            cout << "Вход выполнен как гость" << endl;
            break;
        case 4:
            return 0;
        default:
            std::cout << "Неправильный выбор. Попробуйте еще раз." << std::endl;
            Sleep(1500);
            clearConsole();
            break;
        }

        if (loggedIn) {
            if (role == "Admin") {
                bool continueAsAdmin = true;
                while (continueAsAdmin) {
                    user.adminMenu();
                    clearConsole();
                    continueAsAdmin = false;
                }
            }
            else if (role == "Skladskoy") {
                user.skladMenu();
                clearConsole();
            }
            else {
                break; // Выход из цикла, если роль неизвестна или не имеет меню
            }
        }
    }

    // Если пользователь вышел из цикла авторизации, открываем снова меню авторизации
    main();

    return 0;
}

#pragma endregion main