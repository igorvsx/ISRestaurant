#pragma once

#include <vector>
#include <string>

class Order {
public:
    // ���������� ����� ��� ������ ������
    class OrderItem {
    public:
        int id;
        std::string name;
        double price;
        int quantity;
        std::string status;
    };

    // ������� ��� ������ � �������� ������
    void addItem(const OrderItem& item);
    void removeItem(int itemId);
    void changeItemStatus(int itemId, const std::string& newStatus);
    // ...

private:
    std::vector<OrderItem> items;
};
