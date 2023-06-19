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
class User {
public:
    string role;
    string lastName;
    string firstName;
    string patronymic;
    string username;
    string password;
    void menu();
    // Функции меню для разных ролей
    void guestMenu();
    void adminMenu();
    void employeeMenu();
    void editMenu();
    void editProductList();
    void editEmployees();
    void setUserDetails(const string& role, const string& firstName, const string& lastName, const string& patronymic, const string& username, const string& password);
};

// Класс "Продукт"
class Product {
public: 
    int id;
    string name;
    double price;
};
#pragma endregion Классы

#pragma region Методы

void clearConsole() {
    system("cls");
}

void User::editMenu() {
    cout << "Меню редактирования";
}

void User::editProductList() {
    cout << "Меню редактирования";
}

void User::editEmployees() {
    cout << "Меню редактирования";
}

void User::setUserDetails(const string& role, const string& firstName, const string& lastName, const string& patronymic, const string& username, const string& password) {
    this->role = role;
    this->firstName = firstName;
    this->lastName = lastName;
    this->patronymic = patronymic;
    this->username = username;
    this->password = password;
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
    cout << "Меню сотрудника" << endl;
    // Добавьте функциональность для меню сотрудника
}

void User::menu() {
    if (role == "Гость") {
        guestMenu();
    }
    else if (role == "Системный администратор") {
        adminMenu();
    }
    else {
        employeeMenu();
    }
}
#pragma endregion Методы

#pragma region Регистрация
// Функция для проверки существования пользователя в файле
bool userExists(const string& username) {
    ifstream file("users.txt");
    string line;
    while (getline(file, line)) {
        if (line == username) {
            return true;
        }
    }
    return false;
}

// Функция для регистрации нового пользователя
void registerUser() {
    string role, firstName, lastName, patronymic, username, password;

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
        role = "Администратор";
        break;
    case 2:
        role = "Складской";
        break;
    case 3:
        role = "Поставщик";
        break;
    case 4:
        role = "Бухгалтер";
        break;
    case 5:
        role = "Повар";
        break;
    case 6:
        role = "Официант";
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

    cout << "Введите имя пользователя: ";
    cin >> username;

    if (userExists(username)) {
        cout << "Пользователь с таким именем уже существует." << endl;
        return;
    }

    cout << "Введите пароль: ";
    cin >> password;

    // Валидация длины пароля (минимум 6 символов)
    /*if (password.length() < 6) {
        cout << "Пароль должен содержать минимум 6 символов." << endl;
    }*/

    ofstream file("users.txt", ios::app);
    file << username << endl;
    file << password << endl;
    file << role << endl;
    file << firstName << endl;
    file << lastName << endl;
    file << patronymic << endl;
    

    cout << "Регистрация успешно завершена." << endl;
}

// Функция для авторизации пользователя
// Функция для авторизации пользователя
bool loginUser(User& user) {
    string username, password;

    cout << "Введите имя пользователя: ";
    cin >> username;

    if (!userExists(username)) {
        cout << "Пользователь с таким именем не найден." << endl;
        return false;
    }

    cout << "Введите пароль: ";
    cin >> password;

    ifstream file("users.txt");
    string line;
    string role;
    string pass;
    while (getline(file, line)) {
        if (line == username) {
            getline(file, pass); // Read password
            user.password = pass;
            getline(file, role); // Read role
            user.role = role;
            getline(file, line); // Read firstname
            user.firstName = line;
            getline(file, line); // Read lastname
            user.lastName = line;
            getline(file, line); // Read patronymic
            user.patronymic = line;
            user.setUserDetails(role, "", "", "", "", ""); // Инициализация объекта user
            if (pass == password) {
                cout << "Авторизация успешна." << endl;
                return true;
            }
            else {
                cout << "Неправильный пароль." << endl;
                return false;
            }
        }
    }
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

    while (!loggedIn) {
        std::cout << "1. Регистрация\n2. Авторизация\n3. Войти как гость\n4. Выход\nВыберите действие: ";
        std::cin >> choice;

        // Проверка на некорректный ввод
        if (std::cin.fail()) {
            std::cout << "Неправильный выбор. Попробуйте еще раз." << std::endl << endl;
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
            loggedIn = loginUser(user);
            break;
        case 3:
            loggedIn = true;
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
    }

    if (loggedIn && user.role == "Администратор") {
        user.adminMenu();
    }

    // Здесь может быть код основной логики программы после успешной авторизации

    return 0;
}
#pragma endregion main