#include "Order.h"

void Order::addItem(const OrderItem& item) {
    items.push_back(item);
}

void Order::removeItem(int itemId) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->id == itemId) {
            items.erase(it);
            break;
        }
    }
}

void Order::changeItemStatus(int itemId, const std::string& newStatus) {
    for (auto& item : items) {
        if (item.id == itemId) {
            item.status = newStatus;
            break;
        }
    }
}
