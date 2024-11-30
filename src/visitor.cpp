#include "../include/visitor.h"
#include "../include/knight.h"
#include "../include/druid.h"
#include "../include/elf.h"

VisitorFight::VisitorFight(NPC& attacker): attacker(attacker), attackerDie(false), protectorDie(false) {}

void VisitorFight::visit(Knight& knight, std::shared_ptr<NPC> other) {
    if (attacker.type == NpcType::ElfType){
        attackerDie = true;
        protectorDie = true;
    }
}

void VisitorFight::visit(Druid& druid, std::shared_ptr<NPC> other) {
    if (attacker.type == NpcType::ElfType)
        protectorDie = true;
    else if (attacker.type == NpcType::DruidType) {
        attackerDie = true;
        protectorDie = true;
    }
}

void VisitorFight::visit(Elf& elf, std::shared_ptr<NPC> other) {
    if (attacker.type == NpcType::KnightType){
        attackerDie = true;
        protectorDie = true;
    }
}