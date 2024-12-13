#pragma once

#include <string>
#include <memory>
#include <mutex>
#include <fstream>
#include <iostream>

class Observer {
public:
    virtual void resultFight(const std::string& result) = 0;
    virtual ~Observer() = default;
};

class FileObserver : public Observer {
private:
    std::ofstream file;
    std::mutex mutex;
public:
    FileObserver(const std::string& fileName);
    void resultFight(const std::string& result) override;
    ~FileObserver();
};

class ConsoleObserver : public Observer {
public:
    void resultFight(const std::string& result) override;
};