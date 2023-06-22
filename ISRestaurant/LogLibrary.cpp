#include "LogLibrary.h"
#include <iostream>
#include <fstream>
#include <ctime>

void LogLibrary::logAction(const std::string& employeeName, const std::string& action) {
    std::ofstream logFile("audit_log.txt", std::ios::app); // Открытие файла в режиме добавления данных

    if (logFile.is_open()) {
        // Получение текущего времени и даты
        std::time_t currentTime;
        std::time(&currentTime);
        std::tm timeInfo;
        localtime_s(&timeInfo, &currentTime);
        char timestamp[26];
        asctime_s(timestamp, sizeof(timestamp), &timeInfo);

        // Запись в журнал аудита
        logFile << "Дата и время: " << timestamp;
        logFile << "Сотрудник: " << employeeName << std::endl;
        logFile << "Действие: " << action << std::endl;
        logFile << "---------------------------------------\n";

        logFile.close();
    }
    else {
        std::cout << "Не удалось открыть файл журнала аудита." << std::endl;
    }
}
