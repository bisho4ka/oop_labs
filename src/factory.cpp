#include "../include/factory.h"
#include "../include/knight.h"
#include "../include/elf.h"
#include "../include/druid.h"

#include <stdexcept>

std::shared_ptr<NPC> NPCFactory::createNPC(NpcType type, const std::string& name, int x, int y) {
    switch (type) {
        case NpcType::KnightType:
            return std::make_shared<Knight>(name, x, y);
        case NpcType::ElfType:
            return std::make_shared<Elf>(name, x, y);
        case NpcType::DruidType:
            return std::make_shared<Druid>(name, x, y);
        default:
            throw std::invalid_argument("Неизвестный NPC");
    }
}