#include "JsonHelper.h"
#include "Product.h"
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
#include <openssl/sha.h>
#include "LogLibrary.h"

using namespace std;

std::string hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.length());
    SHA256_Final(hash, &sha256);

    std::string hashedPassword;
    char hexChar[3];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf_s(hexChar, "%02x", hash[i]);
        hashedPassword += hexChar;
    }

    return hashedPassword;
}

#pragma region Регистрация
// Функция для проверки существования пользователя в файле
//bool userExists(const std::string& username) {
//    std::ifstream file("users.json");
//    if (!file.is_open()) {
//        return false;  // Файл не существует, пользователь не найден
//    }
//
//    json data;
//    file >> data;
//
//    if (data.contains("users")) {
//        const json& usersArray = data["users"];
//        for (const auto& user : usersArray) {
//            if (user["username"] == username) {
//                return true;  // Пользователь с таким именем уже существует
//            }
//        }
//    }
//
//    return false;  // Пользователь не найден
//}


// Функция для регистрации нового пользователя
void registerUser() {
    JsonHelper jsonHelper;
    std::string role, firstName, lastName, patronymic, username, password;
    system("cls");
    cout << "Выберите роль пользователя:" << endl;
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
        json jsonData = jsonHelper.readJsonData("users.json");

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

    std::string hashedPassword = hashPassword(password);

    // Создаем объект JSON для нового пользователя
    json user;
    user["role"] = role;
    user["firstName"] = firstName;
    user["lastName"] = lastName;
    user["patronymic"] = patronymic;
    user["username"] = username;
    user["password"] = hashedPassword;

    // Загружаем существующие данные из файла
    json jsonData = jsonHelper.readJsonData("users.json");

    // Добавляем нового пользователя в данные
    jsonData["users"].push_back(user);

    // Сохраняем обновленные данные в файл
    jsonHelper.writeJsonData("users.json", jsonData);

    std::cout << "Пользователь успешно зарегистрирован!\n";

    Sleep(1500);
    system("cls");
}

// Функция для авторизации пользователя
bool loginUser(User& user, std::string& role) {
    LogLibrary loglibrary;

    system("cls");
    JsonHelper jsonHelper;
    std::string username, password;

    std::cout << "Логин: ";
    std::cin >> username;
    std::cout << "Пароль: ";
    std::cin >> password;

    std::string hashedPassword = hashPassword(password);

    // Загружаем данные из файла
    json jsonData = jsonHelper.readJsonData("users.json");

    // Поиск пользователя с указанным логином и паролем
    for (const auto& user : jsonData["users"]) {
        if (user["username"] == username && user["password"] == hashedPassword) {
            role = user["role"];
            system("cls");
            std::cout << "Пользователь успешно аутентифицирован!" << endl;
            loglibrary.logAction(role, "Пользователь вошёл");
            return true;
        }
    }
    system("cls");
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
            system("cls");
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
            user.guestMenu();
            break;
        case 4:
            return 0;
        default:
            std::cout << "Неправильный выбор. Попробуйте еще раз." << std::endl;
            Sleep(1500);
            system("cls");
            break;
        }

        if (loggedIn) {
            if (role == "Admin") {
                bool continueAsAdmin = true;
                while (continueAsAdmin) {
                    user.adminMenu();
                    system("cls");
                    continueAsAdmin = false;
                }
            }
            else if (role == "Skladskoy") {
                user.skladMenu();
                system("cls");
            }
            else if (role == "Supplier") {
                user.supplierMenu();
                system("cls");
            }
            else if (role == "Bughalter") {
                user.accountantMenu();
                system("cls");
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