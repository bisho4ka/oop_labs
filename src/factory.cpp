#include "../include/factory.h"
#include "../include/knight.h"
#include "../include/elf.h"
#include "../include/druid.h"

#include <stdexcept>

oneNPC NPCFactory::createNPC(NpcType type, const std::string& name, int x, int y) {
    if (type == NpcType::KnightType)
        return std::make_shared<Knight>(name, x, y);
    else if (type == NpcType::ElfType)
        return std::make_shared<Elf>(name, x, y);
    else if (type == NpcType::DruidType)
        return std::make_shared<Druid>(name, x, y);
    else
        throw std::invalid_argument("Неизвестный NPC");
}