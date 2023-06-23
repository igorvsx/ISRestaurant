#pragma once
#include <map>
#include <string>
class GuestOrder
{
public:
	std::map<std::string, int> orderCart;
	void addToOrderCart(const std::string& itemName, int quantity);
	void removeFromOrderCart(const std::string& itemName);
	void trackOrderStatus();
};

