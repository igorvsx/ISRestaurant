#pragma once

#include <vector>
#include <string>

class Order {
public:
    void createOrder();
    void withdrawFunds(double amount);
    void printSendOrders();
    void ordersList();
    void printAcceptOrders();
    void setDishName(const std::string& dishName);
    void addItem(const std::string& itemName, int quantity);
};
