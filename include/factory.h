#pragma once

#include "npc.h"

using oneNPC = std::shared_ptr<NPC>;

class NPCFactory {
public:
    static oneNPC createNPC(NpcType type, const std::string& name, int x, int y);
};