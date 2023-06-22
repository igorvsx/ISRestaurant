#pragma once

#include <vector>
#include <string>
#include "Product.h"

class Menu {
public:
    // Внутренний класс для пункта меню (блюда)
    class MenuItem {
    public:
        std::string name;
        std::string weight;
        std::vector<Product> ingredients;
        std::string description;
        std::string cookingTime;
        double cost;
        // Дополнительные поля блюда (например, описание, состав и т.д.)
    };

    // Функции для работы с блюдами
    void editMenu();
    void addDish();
    void removeDish();
    void editDish();
    // ...

private:
    std::vector<MenuItem> items;
};
