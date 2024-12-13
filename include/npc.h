#pragma once

#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <random>
#include <atomic>

#include "observer.h"
#include "visitor.h"
#include "coroutine.h"

enum class NpcType {Unknown = 0, KnightType = 1, DruidType = 2, ElfType = 3};

class NPC: public std::enable_shared_from_this<NPC> {
private:
    std::vector<std::weak_ptr<Observer>> observers;
    
public:
    NpcType type;
    std::string name;
    bool isAlive;
    int x, y, move_distance, kill_distance;

    NPC(NpcType type, const std::string& name, int x, int y);
    
    void inform(const std::string& info);
    void addObserver(std::shared_ptr<Observer> observer);
    
    virtual void save(std::ostream &os) const;
    virtual void print() const;
    
    virtual void acceptVisitor(Visitor& visitor, oneNPC other) = 0;
    
    void handleFight(std::shared_ptr<NPC> &other, int attack_strength, int protection_strength);
    bool isAtDistance(const oneNPC &other, size_t distance) const;

    static oneNPC load(std::istream& is);

    CoroutineTask start();

    virtual ~NPC() = default;
};