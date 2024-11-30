#pragma once

#include "npc.h"

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(NpcType type, const std::string& name, int x, int y);
};