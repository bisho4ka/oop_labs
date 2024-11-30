#include "../include/observer.h"

FileObserver::FileObserver(const std::string& filename) {
    file.open(filename, std::ios::app);
    if (!file.is_open()) 
        throw std::runtime_error("Ошибка при открытии файла");
}

void FileObserver::resultFight(const std::string& result) {
    if (file.is_open()) 
        file << result << std::endl;
}

FileObserver::~FileObserver() {
    if (file.is_open()) 
        file.close();
}

void ConsoleObserver::resultFight(const std::string& result) {
    std::cout << result << std::endl;
}
