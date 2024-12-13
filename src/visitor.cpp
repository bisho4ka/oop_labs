#include "../include/druid.h"
#include "../include/elf.h"
#include "../include/knight.h"
#include "../include/visitor.h"

VisitorFight::VisitorFight(NPC& attacker): attacker(attacker), attackerDie(false), protectorDie(false) {}

void VisitorFight::visit(Knight& knight, oneNPC other) {
    if (attacker.type == NpcType::ElfType){
        attackerDie = true;
        protectorDie = true;
    }
}

void VisitorFight::visit(Druid& druid, oneNPC other) {
    if (attacker.type == NpcType::ElfType)
        protectorDie = true;
    else if (attacker.type == NpcType::DruidType) {
        attackerDie = true;
        protectorDie = true;
    }
}

void VisitorFight::visit(Elf& elf, oneNPC other) {
    if (attacker.type == NpcType::KnightType){
        attackerDie = true;
        protectorDie = true;
    }
}