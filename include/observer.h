#pragma once

#include <string>
#include <memory>
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
public:
    FileObserver(const std::string& filename);
    void resultFight(const std::string& result) override;
    ~FileObserver();
};

class ConsoleObserver : public Observer {
public:
    void resultFight(const std::string& result) override;
};