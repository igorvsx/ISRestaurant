#include "Menu.h"
#include <fstream>


void clearConsole() {
    system("cls");
}

void Menu::addDish() {
    //MenuItem dish;

    //clearConsole();

    //cout << "������� ������������ �����: ";
    //cin.ignore();
    //getline(cin, dish.name);

    //cout << "������� ���������: ";
    //getline(cin, dish.weight);

    //// ����� ����� ����������� ������ ��� ������ ������� ��������� �� ������

    //cout << "������� �������� �����: ";
    //getline(cin, dish.description);

    //cout << "������� ��������� ����� �������������: ";
    //getline(cin, dish.cookingTime);

    //cout << "������� ��������� �����: ";
    //cin >> dish.cost;

    //items.push_back(dish);

    //cout << "����� ������� ��������� � ����." << endl;

    //Sleep(1500);
    //clearConsole();

    //// ���������� ������ � ����
    //ofstream outFile("menu.txt", ios::app); // ��������� ���� ��� ���������� ������ � �����
    //if (outFile.is_open()) {
    //    outFile << dish.name << endl;
    //    outFile << dish.weight << endl;
    //    outFile << dish.description << endl;
    //    outFile << dish.cookingTime << endl;
    //    outFile << dish.cost << endl;
    //    outFile << "===" << endl; // ����������� ����� �������
    //    outFile.close();
    //    cout << "������ ������� ��������� � ����." << endl;
    //}
    //else {
    //    cout << "������ �������� ����� ��� ���������� ������." << endl;
    //}
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
