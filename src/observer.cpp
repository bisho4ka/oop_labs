#include "../include/observer.h"
#include "../include/logger.h"

FileObserver::FileObserver(const std::string& fileName) {
    file.open(fileName, std::ios::app);
    if (!file.is_open()) 
        throw std::runtime_error("Ошибка при открытии файла");
}

void FileObserver::resultFight(const std::string& result) {
    std::lock_guard<std::mutex> lock(mutex);
    if (file.is_open()) 
        file << result << std::endl;
}

FileObserver::~FileObserver() {
    if (file.is_open()) 
        file.close();
}

void ConsoleObserver::resultFight(const std::string& result) {
    Logger::log(result);
}