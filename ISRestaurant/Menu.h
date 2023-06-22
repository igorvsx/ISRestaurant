#pragma once

#include <vector>
#include <string>
#include "Product.h"

class Menu {
public:
    // ���������� ����� ��� ������ ���� (�����)
    class MenuItem {
    public:
        std::string name;
        std::string weight;
        std::vector<Product> ingredients;
        std::string description;
        std::string cookingTime;
        double cost;
        // �������������� ���� ����� (��������, ��������, ������ � �.�.)
    };

    // ������� ��� ������ � �������
    void editMenu();
    void addDish();
    void removeDish();
    void editDish();
    // ...

private:
    std::vector<MenuItem> items;
};
