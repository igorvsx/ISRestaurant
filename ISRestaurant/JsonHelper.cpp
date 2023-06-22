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
            std::cout << "Данные успешно сохранены в файл: " << filename << std::endl;
        }
        else {
            std::cout << "Не удалось открыть файл: " << filename << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка при записи данных в файл: " << e.what() << std::endl;
    }
}

json JsonHelper::getProductData(int productId) {
    // Загружаем данные о продуктах из файла
    json productData = readJsonData("products.json");

    // Поиск продукта по ID
    for (const auto& product : productData["products"]) {
        if (product["id"] == productId) {
            return product;
        }
    }

    // Если продукт не найден, возвращаем пустой JSON-объект
    return json();
}
