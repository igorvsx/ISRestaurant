#include "Menu.h"
#include "Product.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <cstdlib>
#include "JsonHelper.h"
#define NOMINMAX
#include <windows.h>

using namespace std;

void Menu::editMenu() {
    system("cls");
    int choice;

    while (true) {
        cout << "�������������� ����:\n";
        cout << "1. ������ ����\n";
        cout << "2. �������� �����\n";
        cout << "3. ������� �����\n";
        cout << "4. ������������� �����\n";
        cout << "5. �����\n";
        cout << "�������� ��������: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "������������ �����. ���������� ��� ���." << endl;
            cin.clear();
            system("cls");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
        case 1:
            listDishes();
            break;
        case 2:
            addDish();
            editMenu();
            break;
        case 3:
            removeDish();
            break;
        case 4:
            editDish();
            break;
        case 5:
            system("cls");
            return;  
            break; // ����� �� ������� editMenu() � ������� � ����������� ����
        default:
            cout << "������������ �����. ���������� ��� ���." << endl;
            system("cls");
            break;
        }
    }
}

void Menu::addDish() {
    JsonHelper jsonHelper;

    system("cls");

    // ������� ����� �����
    Menu newDish;

    json productsData = jsonHelper.readJsonData("products.json");

    cout << "������� ������������ �����: ";
    cin.ignore();
    getline(cin, newDish.name);

    cout << "������� ��������� �����: ";
    getline(cin, newDish.weight);

    // ���������� ������������
    char choice;
    do {

        Product product;
        cout << "������� ID ��������: ";
        cin >> product.id;

        bool found = false;

        for (const auto& selectedProduct : productsData["products"]) {
            if (selectedProduct["id"] == product.id) {
                found = true;
                // ������� ����� ������� �� ������ ���������� ��������
                Product newIngredient;
                newIngredient.id = selectedProduct["id"];
                newIngredient.name = selectedProduct["name"];
                newIngredient.price = selectedProduct["price"];
                newDish.ingredients.push_back(newIngredient);
                break;
            }
        }

        if (!found) {
            cout << "������� � ��������� ID �� ������." << endl;
            // ����������� ������, ����� ������� �� ������
        }

        cout << "�������� ��� �����������? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    cout << "������� �������� �����: ";
    cin.ignore();
    getline(cin, newDish.description);

    cout << "������� ����� ������������� �����: ";
    getline(cin, newDish.cookingTime);

    cout << "������� ��������� �����: ";
    cin >> newDish.cost;

    // �������� ������ �� JSON-�����
    json menuData = jsonHelper.readJsonData("menu.json");

    // ���������� ������ ����� � JSON-������
    json dishJson;

    dishJson["name"] = newDish.name;
    dishJson["weight"] = newDish.weight;

    json ingredientsJson = json::array();
    for (const auto& ingredient : newDish.ingredients) {
        json ingredientJson = {
            {"id", ingredient.id},
            {"name", ingredient.name},
            {"price", ingredient.price}
        };
        ingredientsJson.push_back(ingredientJson);
    }

    dishJson["ingredients"] = ingredientsJson;

    dishJson["description"] = newDish.description;
    dishJson["cookingTime"] = newDish.cookingTime;
    dishJson["cost"] = newDish.cost;

    menuData["menu"].push_back(dishJson);

    // ���������� ����������� ������ � JSON-����
    jsonHelper.writeJsonData("menu.json", menuData);

    cout << "����� ������� ���������!" << endl;

    // ������� ������ �����
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // �������� ������� ������� �������������
    system("pause");
    system("cls");
}

void Menu::removeDish()
{
    JsonHelper jsonHelper;

    system("cls");

    // �������� ������ �� JSON-�����
    json jsonData = jsonHelper.readJsonData("menu.json");

    // �������� ������� ������� � ����
    if (jsonData["menu"].empty()) {
        cout << "���� �����. ��� ������� ��� ��������." << endl;
        system("pause");
        system("cls");
        return;
    }

    // ����� �������� ���� � �������� �������
    cout << "������� ����:\n";
    for (size_t i = 0; i < jsonData["menu"].size(); ++i) {
        cout << "������ " << i + 1 << ":\n";
        cout << "��������: " << jsonData["menu"][i]["name"].get<string>() << endl;
        cout << "��������: " << jsonData["menu"][i]["description"].get<string>() << endl;
        cout << "--------------------------\n";
    }

    // ���� ������ ������ ��� ��������
    int recordNumber;
    cout << "������� ����� ������ ��� ��������: ";
    cin >> recordNumber;

    // �������� ���������� ������ ������
    if (recordNumber <= 0 || recordNumber > jsonData["menu"].size()) {
        cout << "������ ������������ ����� ������." << endl;
        system("pause");
        system("cls");
        return;
    }

    // �������� ��������� ������
    jsonData["menu"].erase(jsonData["menu"].begin() + recordNumber - 1);

    // ���������� ����������� ������ � JSON-����
    jsonHelper.writeJsonData("menu.json", jsonData);

    cout << "������ ������� �������!" << endl;

    system("pause");
    system("cls");
}

void Menu::editDish()
{
    JsonHelper jsonHelper;

    system("cls");

    // �������� ������ �� JSON-�����
    json jsonData = jsonHelper.readJsonData("menu.json");
    json productsData = jsonHelper.readJsonData("products.json");

    // �������� ������� ������� � ����
    if (jsonData["menu"].empty()) {
        cout << "���� �����. ��� ������� ��� ��������������." << endl;
        system("pause");
        system("cls");
        return;
    }

    // ����� �������� ���� � �������� �������
    cout << "������� ����:\n";
    for (size_t i = 0; i < jsonData["menu"].size(); ++i) {
        cout << "������ " << i + 1 << ":\n";
        cout << "��������: " << jsonData["menu"][i]["name"].get<string>() << endl;
        cout << "��������: " << jsonData["menu"][i]["description"].get<string>() << endl;
        cout << "--------------------------\n";
    }

    // ���� ������ ������ ��� ��������������
    int recordNumber;
    cout << "������� ����� ������ ��� ��������������: ";
    cin >> recordNumber;

    // �������� ���������� ������ ������
    if (recordNumber <= 0 || recordNumber > jsonData["menu"].size()) {
        cout << "������ ������������ ����� ������." << endl;
        system("pause");
        system("cls");
        return;
    }

    // ����� ������������� ������
    json& selectedDish = jsonData["menu"][recordNumber - 1];

    // ����� ���������� � ��������� �����
    cout << "�������������� �����:\n";
    cout << "��������: " << selectedDish["name"].get<string>() << endl;
    cout << "��������: " << selectedDish["description"].get<string>() << endl;

    // �������� ���������
    cin.ignore();
    cout << "������� ����� �������� �����: ";
    string newName;
    std::getline(cin, newName);
    selectedDish["name"] = newName;

    cout << "������� ����� �������� �����: ";
    string newDescription;
    std::getline(cin, newDescription);
    selectedDish["description"] = newDescription;

    cout << "������� ����� ��������� �����: ";
    double newCost;
    cin >> newCost;
    selectedDish["cost"] = newCost;

    cout << "������� ����� ����� ������������� �����: ";
    string newCookingTime;
    cin.ignore();
    std::getline(cin, newCookingTime);
    selectedDish["cookingTime"] = newCookingTime;

    cout << "������� ����� ��������� �����: ";
    string newWeight;
    std::getline(cin, newWeight);
    selectedDish["weight"] = newWeight;

    // �������������� ������������
    selectedDish["ingredients"].clear();

    //char choice;
    //do {
    //    Product product;
    //    cout << "������� ID ��������: ";
    //    cin >> product.id;


    //    // ����� �������� �� ID � ���� ������ � ���������� � ����������� �����
    //    bool found = false;
    //    for (const auto& availableProduct : jsonData["products"]) {
    //        if (availableProduct["id"] == product.id) {
    //            found = true;
    //            selectedDish["ingredients"].push_back(availableProduct);
    //            break;
    //        }
    //    }

    //    if (!found) {
    //        cout << "������� � ��������� ID �� ������." << endl;
    //        // ��������� ������, ����� ������� �� ������
    //    }

    //    cout << "�������� ��� �����������? (y/n): ";
    //    cin >> choice;
    //} while (choice == 'y');

    char choice;
    do {

        Product product;
        cout << "������� ID ��������: ";
        cin >> product.id;

        bool found = false;

        for (const auto& availableProduct : productsData["products"]) {
            if (availableProduct["id"] == product.id) {
                found = true;
                // ������� ����� ������� �� ������ ���������� ��������
                Product newIngredient;
                newIngredient.id = availableProduct["id"];
                newIngredient.name = availableProduct["name"];
                newIngredient.price = availableProduct["price"];
                selectedDish["ingredients"].push_back(availableProduct);
                break;
            }
        }

        if (!found) {
            cout << "������� � ��������� ID �� ������." << endl;
            // ����������� ������, ����� ������� �� ������
        }

        cout << "�������� ��� �����������? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    // ���������� ����������� ������ � JSON-����
    jsonHelper.writeJsonData("menu.json", jsonData);

    cout << "������ ������� ���������������!" << endl;

    system("pause");
    system("cls");
}

void Menu::listDishes() {
    JsonHelper jsonHelper;
    system("cls");

    // ��������� ������ �� �����
    json jsonData = jsonHelper.readJsonData("menu.json");

    // ������� ������ ��� �������� ���������� � ������
    std::vector<Menu> dishes;

    // ��������� ������ � ������ �� JSON
    for (const auto& dish : jsonData["menu"]) {
        Menu currentDish;
        currentDish.name = dish["name"];
        currentDish.description = dish["description"];
        currentDish.cookingTime = dish["cookingTime"];
        currentDish.weight = dish["weight"];
        currentDish.cost = dish["cost"];

        // ��������� ������ �� ������������
        for (const auto& ingredient : dish["ingredients"]) {
            Product currentIngredient;
            currentIngredient.id = ingredient["id"];
            currentIngredient.name = ingredient["name"];
            currentIngredient.price = ingredient["price"];
            currentDish.ingredients.push_back(currentIngredient);
        }

        dishes.push_back(currentDish);
    }

    // ���������� ���������� ������� �� ��������
    const int itemsPerPage = 5;
    int totalPages = (dishes.size() + itemsPerPage - 1) / itemsPerPage; // ���������� �����

    // ������� ������ ���� � �����������
    std::cout << "������ ����:\n";
    int startIndex = 0;
    int currentPage = 1;

    while (true) {
        int endIndex = std::min(startIndex + itemsPerPage, static_cast<int>(dishes.size()));

        for (int i = startIndex; i < endIndex; ++i) {
            std::cout << "��������: " << dishes[i].name << std::endl;
            std::cout << "��������: " << dishes[i].description << std::endl;
            std::cout << "����� �������������: " << dishes[i].cookingTime << std::endl;
            std::cout << "���: " << dishes[i].weight << std::endl;
            std::cout << "���������: " << dishes[i].cost << std::endl;

            std::cout << "�����������:\n";
            for (const auto& ingredient : dishes[i].ingredients) {
                std::cout << "  - ��������: " << ingredient.name << std::endl;
                std::cout << "    ����: " << ingredient.price << std::endl;
            }

            std::cout << "-----------------------\n";
        }

        // ���������, ���������� �� ��������� ��������
        if (currentPage == totalPages) {
            break;
        }

        // ����������� � ������������ �������� ��������� ��������
        std::cout << "��������� ���? (y/n): ";
        std::string input;
        std::cin >> input;

        // ���� ������������ �� ������ ��������� ��������� ��������, ���������� ���������
        if (input != "y") {
            break;
        }

        // ����������� ������� ��� �������� �� ��������� ��������
        startIndex += itemsPerPage;
        currentPage++;
    }

    int choice;
    std::cout << "������� ����� ������ ��� ������: ";
    std::cin >> choice;
    switch (choice) {
    default:
        return;
        break;
    }

    Sleep(1500);
    system("cls");
}

