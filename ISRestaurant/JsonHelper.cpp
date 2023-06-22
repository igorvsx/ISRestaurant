#include "JsonHelper.h"

json JsonHelper::readJsonData(const std::string& filename) {
    std::ifstream inputFile(filename);
    json jsonData;
    if (inputFile.is_open()) {
        inputFile >> jsonData;
        inputFile.close();
    }
    return jsonData;
}

void JsonHelper::writeJsonData(const std::string& filename, const json& jsonData) {
    try {
        std::ofstream outputFile(filename);
        if (outputFile.is_open()) {
            outputFile << std::setw(4) << jsonData << std::endl;
            outputFile.close();
            std::cout << "������ ������� ��������� � ����: " << filename << std::endl;
        }
        else {
            std::cout << "�� ������� ������� ����: " << filename << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "������ ��� ������ ������ � ����: " << e.what() << std::endl;
    }
}

json JsonHelper::getProductData(int productId) {
    // ��������� ������ � ��������� �� �����
    json productData = readJsonData("products.json");

    // ����� �������� �� ID
    for (const auto& product : productData["products"]) {
        if (product["id"] == productId) {
            return product;
        }
    }

    // ���� ������� �� ������, ���������� ������ JSON-������
    return json();
}
