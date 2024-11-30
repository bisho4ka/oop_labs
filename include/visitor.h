#pragma once

#include <memory>

class Knight;
class Druid;
class Elf;
class NPC;

class Visitor {
public:
    virtual void visit(Knight& knight, std::shared_ptr<NPC> other) = 0;
    virtual void visit(Druid& druid, std::shared_ptr<NPC> other) = 0;
    virtual void visit(Elf& elf, std::shared_ptr<NPC> other) = 0;
    virtual ~Visitor() = default;
};

class VisitorFight : public Visitor {
public:
    VisitorFight(NPC& attacker);

    void visit(Knight& knight, std::shared_ptr<NPC> other) override;
    void visit(Elf& elf, std::shared_ptr<NPC> other) override;
    void visit(Druid& druid, std::shared_ptr<NPC> other) override;

    bool attackerDie;
    bool protectorDie;
    NPC& attacker;
};
