#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <set>
#include <memory>
#include <algorithm>

#include "observer.h"
#include "visitor.h"

enum class NpcType {
    Unknown = 0,
    KnightType = 1,
    DruidType = 2,
    ElfType = 3
};

class NPC: public std::enable_shared_from_this<NPC> {
private:
    std::vector<std::weak_ptr<Observer>> observers;
    
public:
    NpcType type;
    std::string name;
    int x;
    int y;

    NPC(NpcType type, const std::string& name, int x, int y);
    
    void addObserver(std::shared_ptr<Observer> observer);
    void inform(const std::string& info);

    bool isAtDistance(const std::shared_ptr<NPC> &other, size_t distance) const;
    
    virtual void save(std::ostream &os) const;
    virtual void print() const;
    
    virtual void acceptVisitor(Visitor& visitor, std::shared_ptr<NPC> other) = 0;

    static std::shared_ptr<NPC> load(std::istream& is);

    virtual ~NPC() = default;
};