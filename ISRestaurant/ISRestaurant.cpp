#include <iostream>
#include <fstream>
#include <vector>
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
    else if (role == "Администратор") {
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
                clearConsole();
                cout << "Авторизация успешна. \n" << endl;
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
        clearConsole();
        main();
    }

    // Здесь может быть код основной логики программы после успешной авторизации

    return 0;
}
#pragma endregion main