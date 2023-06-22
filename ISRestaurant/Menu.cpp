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
        cout << "1. �������� �����\n";
        cout << "2. ������� �����\n";
        cout << "3. ������������� �����\n";
        cout << "4. ��������� � ���������� ����\n";
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
            addDish();
            editMenu();
            break;
        case 2:
            removeDish();
            break;
        case 3:
            editDish();
            break;
        case 4:
            return;  // ����� �� ������� editMenu() � ������� � ����������� ����
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

    json jsonData = jsonHelper.readJsonData("products.json");

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

        string productName;
        bool found = false;

        Product selectedProduct;
        for (const auto& selectedProduct : jsonData["products"]) {
            if (selectedProduct["id"] == product.id) {
                found = true;
                selectedProduct["name"] == productName;
                break;
            }
        }

        if (found) {

            // ����������� selectedProduct ��� ������� � ������ � ��������� ��������
            // ��������, �� ������ ������������ selectedProduct.name ��� ��������� ������������ ��������
            // � �������� ��� � ����� ����� newDish.ingredients.push_back(selectedProduct);

            // ���������� ��� ��� ��������� ���������� ��������
            newDish.ingredients.push_back(product);
        }
        else {
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
    /*json jsonData = jsonHelper.readJsonData("menu.json");*/

    // ���������� ������ ����� � JSON-������
    json ingredientsJson = json::array();
    for (const auto& ingredient : newDish.ingredients) {
        json ingredientJson = {
            {"id", ingredient.id},
            {"name", ingredient.name},
            {"price", ingredient.price}
        };
        ingredientsJson.push_back(ingredientJson);
    }

    jsonData["dishes"].push_back({
    {"name", newDish.name},
    {"weight", newDish.weight},
    {"ingredients", ingredientsJson},
    {"description", newDish.description},
    {"cookingTime", newDish.cookingTime},
    {"cost", newDish.cost}
        });

    // ���������� ����������� ������ � JSON-����
    jsonHelper.writeJsonData("menu.json", jsonData);

    cout << "����� ������� ���������!" << endl;

    // ������� ������ �����
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // �������� ������� ������� �������������
    system("pause");
    system("cls");
}



void Menu::removeDish() {
    //clearConsole();

    //// ������ ������ �� �����
    //ifstream inFile("menu.txt");
    //if (!inFile.is_open()) {
    //    cout << "������ �������� ����� ��� ������ ������." << endl;
    //    return;
    //}

    //// ������ ��� �������� ���� �� �����
    //vector<MenuItem> fileItems;

    //string line;
    //MenuItem dish;

    //// ������ ������ �� ����� � ��������� ����� � �������
    //while (getline(inFile, line)) {
    //    if (line == "===") {
    //        fileItems.push_back(dish);
    //        dish = MenuItem(); // ���������� dish ��� ���������� �����
    //    }
    //    else if (!line.empty()) {
    //        switch (fileItems.size() % 5) {
    //        case 0: {
    //            // �������� �������� � ���� �� ������
    //            size_t pricePos = line.find_last_of(' ');
    //            dish.name = line.substr(0, pricePos);
    //            try {
    //                dish.cost = stod(line.substr(pricePos + 1));
    //            }
    //            catch (const std::invalid_argument&) {
    //                cout << "������ �������������� ���� �����. ���������� �����." << endl;
    //                continue;
    //            }
    //            break;
    //        }
    //        case 1: dish.weight = line; break;
    //        case 2: dish.description = line; break;
    //        case 3: dish.cookingTime = line; break;
    //        case 4: dish.cost = stod(line); break;
    //        }
    //    }
    //}
    //inFile.close();

    //// ������� ������������ ���� � �������
    //if (fileItems.empty()) {
    //    cout << "� ���� ��� ��������� ����." << endl;
    //    return;
    //}

    //cout << "������ ��������� ����:" << endl;
    //for (const auto& item : fileItems) {
    //    cout << "- " << item.name << endl;
    //}

    //// ������ ������������ ������ �������� ����� ��� ��������
    //string dishName;
    //cout << "������� �������� ����� ��� ��������: ";
    //cin.ignore();
    //getline(cin, dishName);

    //// ����� � �������� �����
    //bool found = false;
    //for (auto it = fileItems.begin(); it != fileItems.end(); ++it) {
    //    if (it->name == dishName) {
    //        fileItems.erase(it);
    //        found = true;
    //        break;
    //    }
    //}

    //if (found) {
    //    // �������������� ������ � ����� ��� ���������� �����
    //    ofstream outFile("menu.txt");
    //    if (outFile.is_open()) {
    //        for (const auto& item : fileItems) {
    //            outFile << item.name << " " << item.cost << endl;
    //            outFile << item.weight << endl;
    //            outFile << item.description << endl;
    //            outFile << item.cookingTime << endl;
    //            outFile << item.cost << endl;
    //            outFile << "===" << endl;
    //        }
    //        outFile.close();
    //        cout << "����� ������� ������� �� ����." << endl;
    //    }
    //    else {
    //        cout << "������ �������� ����� ��� ������ ������." << endl;
    //    }
    //}
    //else {
    //    cout << "����� � ��������� ��������� �� �������." << endl;
    //}

    //Sleep(1500);
    //clearConsole();
}


void Menu::editDish() {
    /*cout << "";*/
}
