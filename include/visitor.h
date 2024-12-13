#pragma once

#include <memory>

class NPC;
class Knight;
class Druid;
class Elf;

using oneNPC = std::shared_ptr<NPC>;

class Visitor {
public:
    virtual void visit(Knight& knight, oneNPC other) = 0;
    virtual void visit(Druid& druid, oneNPC other) = 0;
    virtual void visit(Elf& elf, oneNPC other) = 0;
    virtual ~Visitor() = default;
};

class VisitorFight : public Visitor {
public:
    bool attackerDie, protectorDie;
    NPC& attacker;

    VisitorFight(NPC& attacker);

    void visit(Knight& knight, oneNPC other) override;
    void visit(Elf& elf, oneNPC other) override;
    void visit(Druid& druid, oneNPC other) override;
};
