#pragma once

#include <vector>
#include <string>

class Order {
public:
    // Внутренний класс для пункта заказа
    class OrderItem {
    public:
        int id;
        std::string name;
        double price;
        int quantity;
        std::string status;
    };

    // Функции для работы с пунктами заказа
    void addItem(const OrderItem& item);
    void removeItem(int itemId);
    void changeItemStatus(int itemId, const std::string& newStatus);
    // ...

private:
    std::vector<OrderItem> items;
};
