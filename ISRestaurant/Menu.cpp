#include "Menu.h"
#include <fstream>


void clearConsole() {
    system("cls");
}

void Menu::addDish() {
    //MenuItem dish;

    //clearConsole();

    //cout << "Введите наименование блюда: ";
    //cin.ignore();
    //getline(cin, dish.name);

    //cout << "Введите граммовку: ";
    //getline(cin, dish.weight);

    //// Здесь можно реализовать логику для выбора состава продуктов из списка

    //cout << "Введите описание блюда: ";
    //getline(cin, dish.description);

    //cout << "Введите примерное время приготовления: ";
    //getline(cin, dish.cookingTime);

    //cout << "Введите стоимость блюда: ";
    //cin >> dish.cost;

    //items.push_back(dish);

    //cout << "Блюдо успешно добавлено в меню." << endl;

    //Sleep(1500);
    //clearConsole();

    //// Сохранение данных в файл
    //ofstream outFile("menu.txt", ios::app); // Открываем файл для добавления данных в конец
    //if (outFile.is_open()) {
    //    outFile << dish.name << endl;
    //    outFile << dish.weight << endl;
    //    outFile << dish.description << endl;
    //    outFile << dish.cookingTime << endl;
    //    outFile << dish.cost << endl;
    //    outFile << "===" << endl; // Разделитель между блюдами
    //    outFile.close();
    //    cout << "Данные успешно сохранены в файл." << endl;
    //}
    //else {
    //    cout << "Ошибка открытия файла для сохранения данных." << endl;
    //}
}

void Menu::removeDish() {
    //clearConsole();

    //// Чтение данных из файла
    //ifstream inFile("menu.txt");
    //if (!inFile.is_open()) {
    //    cout << "Ошибка открытия файла для чтения данных." << endl;
    //    return;
    //}

    //// Вектор для хранения блюд из файла
    //vector<MenuItem> fileItems;

    //string line;
    //MenuItem dish;

    //// Читаем данные из файла и сохраняем блюда в векторе
    //while (getline(inFile, line)) {
    //    if (line == "===") {
    //        fileItems.push_back(dish);
    //        dish = MenuItem(); // Сбрасываем dish для следующего блюда
    //    }
    //    else if (!line.empty()) {
    //        switch (fileItems.size() % 5) {
    //        case 0: {
    //            // Получаем название и цену из строки
    //            size_t pricePos = line.find_last_of(' ');
    //            dish.name = line.substr(0, pricePos);
    //            try {
    //                dish.cost = stod(line.substr(pricePos + 1));
    //            }
    //            catch (const std::invalid_argument&) {
    //                cout << "Ошибка преобразования цены блюда. Пропускаем блюдо." << endl;
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

    //// Выводим наименования блюд в консоль
    //if (fileItems.empty()) {
    //    cout << "В меню нет доступных блюд." << endl;
    //    return;
    //}

    //cout << "Список доступных блюд:" << endl;
    //for (const auto& item : fileItems) {
    //    cout << "- " << item.name << endl;
    //}

    //// Просим пользователя ввести название блюда для удаления
    //string dishName;
    //cout << "Введите название блюда для удаления: ";
    //cin.ignore();
    //getline(cin, dishName);

    //// Поиск и удаление блюда
    //bool found = false;
    //for (auto it = fileItems.begin(); it != fileItems.end(); ++it) {
    //    if (it->name == dishName) {
    //        fileItems.erase(it);
    //        found = true;
    //        break;
    //    }
    //}

    //if (found) {
    //    // Перезаписываем данные в файле без удаленного блюда
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
    //        cout << "Блюдо успешно удалено из меню." << endl;
    //    }
    //    else {
    //        cout << "Ошибка открытия файла для записи данных." << endl;
    //    }
    //}
    //else {
    //    cout << "Блюдо с указанным названием не найдено." << endl;
    //}

    //Sleep(1500);
    //clearConsole();
}


void Menu::editDish() {
    /*cout << "";*/
}
