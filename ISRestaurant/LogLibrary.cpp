#include "LogLibrary.h"
#include <iostream>
#include <fstream>
#include <ctime>

void LogLibrary::logAction(const std::string& employeeName, const std::string& action) {
    std::ofstream logFile("audit_log.txt", std::ios::app); // �������� ����� � ������ ���������� ������

    if (logFile.is_open()) {
        // ��������� �������� ������� � ����
        std::time_t currentTime;
        std::time(&currentTime);
        std::tm timeInfo;
        localtime_s(&timeInfo, &currentTime);
        char timestamp[26];
        asctime_s(timestamp, sizeof(timestamp), &timeInfo);

        // ������ � ������ ������
        logFile << "���� � �����: " << timestamp;
        logFile << "���������: " << employeeName << std::endl;
        logFile << "��������: " << action << std::endl;
        logFile << "---------------------------------------\n";

        logFile.close();
    }
    else {
        std::cout << "�� ������� ������� ���� ������� ������." << std::endl;
    }
}
