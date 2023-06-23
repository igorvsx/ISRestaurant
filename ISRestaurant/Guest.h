#pragma once
class Guest
{
public:
    void createOrder();
    void removeItem();
    void confirmOrder(double totalAmount);
    void displayOrder() const;
    void displayStatus() const;
};	

