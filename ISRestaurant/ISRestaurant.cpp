#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdlib>
#define NOMINMAX
#include <windows.h>

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

// Класс "Меню"
class Menu {
public:
    // Функции для работы с блюдами
    void addDish();
    void removeDish();
    void editDish();
    // ...
};

// Класс "Сотрудник"
class Employee {
protected:
    std::string role;
    std::string lastName;
    std::string firstName;
    std::string patronymic;
    std::string username;
    std::string password;
public:
    // Геттеры и сеттеры для полей
    // ...
};

// Класс "Системный администратор"
class SystemAdministrator : public Employee {
public:
    // Функции для управления меню и списком продуктов
    void editMenu();
    void editProductList();
    // ...
};

// Класс "Складской"
class Storekeeper : public Employee {
public:
    // Функции для управления складом и заявками на продукты
    void createProductRequest();
    void trackInventory();
    // ...
};

// Класс "Поставщик"
class Supplier {
public:
    // Функции для просмотра и обработки заявок на продукты
    void viewProductRequest();
    void processProductRequest();
    // ...
};

// Класс "Бухгалтер"
class Accountant {
public:
    // Функции для просмотра финансовой отчетности и заявок на продукты
    void viewFinancialReport();
    void viewProductRequest();
    // ...
};

// Класс "Повар"
class Cook : public Employee {
public:
    // Функции для просмотра и приготовления заказов
    void viewOrders();
    void startCooking();
    // ...
};

// Класс "Продукт"
class Product {
public: 
    int id;
    std::string name;
    double price;
};
#pragma endregion Классы

#pragma region Регистрация
// Функция для проверки существования пользователя в файле
bool userExists(const std::string& username) {
    std::ifstream file("users.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line == username) {
            return true;
        }
    }
    return false;
}

// Функция для регистрации нового пользователя
void registerUser() {
    std::string username, password;

    std::cout << "Введите имя пользователя: ";
    std::cin >> username;

    if (userExists(username)) {
        std::cout << "Пользователь с таким именем уже существует." << std::endl;
        return;
    }

    std::cout << "Введите пароль: ";
    std::cin >> password;

    // Валидация длины пароля (минимум 6 символов)
    if (password.length() < 6) {
        std::cout << "Пароль должен содержать минимум 6 символов." << std::endl;
        return;
    }

    std::ofstream file("users.txt", std::ios::app);
    file << username << std::endl;
    file << password << std::endl;

    std::cout << "Регистрация успешно завершена." << std::endl;
}

// Функция для авторизации пользователя
bool loginUser() {
    std::string username, password;

    std::cout << "Введите имя пользователя: ";
    std::cin >> username;

    if (!userExists(username)) {
        std::cout << "Пользователь с таким именем не найден." << std::endl;
        return false;
    }

    std::cout << "Введите пароль: ";
    std::cin >> password;

    std::ifstream file("users.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line == username) {
            std::getline(file, line);  // Читаем следующую строку с паролем
            if (line == password) {
                std::cout << "Авторизация успешна." << std::endl;
                return true;
            }
            else {
                std::cout << "Неправильный пароль." << std::endl;
                return false;
            }
        }
    }

    return false;  // Не должны сюда попадать
}
#pragma endregion Регистрация

void clearConsole() {
    system("cls");
}

int main()
{
    setlocale(LC_ALL, "RU");

    int choice;
    bool loggedIn = false;

    while (!loggedIn) {
        std::cout << "1. Регистрация\n2. Авторизация\n3. Выход\nВыберите действие: ";
        std::cin >> choice;

        // Проверка на некорректный ввод
        if (std::cin.fail()) {
            std::cout << "Неправильный выбор. Попробуйте еще раз." << std::endl << endl;
            std::cin.clear();
            clearConsole();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loggedIn = loginUser();
            break;
        case 3:
            return 0;
        default:
            std::cout << "Неправильный выбор. Попробуйте еще раз." << std::endl;
            Sleep(2000);
            clearConsole();
            break;
        }
    }

    // Здесь может быть код основной логики программы после успешной авторизации

    return 0;
}