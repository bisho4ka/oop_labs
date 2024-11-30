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

using moreNPC = std::set<std::shared_ptr<NPC>>;

enum class NpcType {Unknown = 0, KnightType = 1, DruidType = 2, ElfType = 3};

class NPC: public std::enable_shared_from_this<NPC> {
private:
    std::vector<std::weak_ptr<Observer>> observers;
    
public:
    NpcType type;
    std::string name;
    int x, y;

    NPC(NpcType type, const std::string& name, int x, int y);
    
    void inform(const std::string& info);
    void addObserver(std::shared_ptr<Observer> observer);
    
    virtual void save(std::ostream &os) const;
    virtual void print() const;
    
    virtual void acceptVisitor(Visitor& visitor, oneNPC other) = 0;

    bool isAtDistance(const oneNPC &other, size_t distance) const;
    
    static oneNPC load(std::istream& is);

    virtual ~NPC() = default;
};

void saveNpcToFile(const moreNPC& npcs, const std::string& filename);
moreNPC loadNPCsFromFile(const std::string& filename);
moreNPC startFight(moreNPC& npcs, size_t range);