#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "include/factory.h"
#include "include/npc.h"
#include "include/observer.h"
#include "include/visitor.h"

int main() {
    std::srand(static_cast<unsigned int>(time(nullptr)));
    
    moreNPC npcs;

    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("battle_log.txt");

    std::vector<std::string> npcNames = {
        "Сьюзан", "Линетт", "Габриэль", "Бри", "Майк",
        "Том", "Орсон", "Карлос", "Мэри", "Эндрю"};

    for (int i = 0; i < 10; i++) {
        NpcType type = static_cast<NpcType>(std::rand() % 3 + 1);
        std::string npcName = npcNames[i];
        
        int posX = std::rand() % 500;
        int posY = std::rand() % 500;

        auto npc = NPCFactory::createNPC(type, npcName, posX, posY);
        npc->addObserver(consoleObserver);
        npc->addObserver(fileObserver);
        npcs.insert(npc);
    }

    saveNpcToFile(npcs, "NPCs.txt");
    npcs = loadNPCsFromFile("npcs.txt");

    std::cout << "Список всех NPC на карте:" << std::endl;
    std::cout << "------------------------------" << std::endl;
    for (const auto& npc : npcs) {
        npc->print();
    }

    size_t battleRange;
    std::cout << "\nВведите дистанцию для битвы: ";
    std::cin >> battleRange;

    while (!npcs.empty()) {
        auto killed = startFight(npcs, battleRange);
        if (killed.empty()) {
            break;
        }
        for (const auto& dead : killed) {
            npcs.erase(dead);
        }
    }

    std::cout << "\nИтак!! Финал!! А вот и победители (выжившие NPC):\n" << std::endl;
    if (!npcs.empty()) {
        for (const auto& npc : npcs)
            npc->print();
    } else {
        std::cout << "Никого не осталось :(" << std::endl;
    }

    return 0;
}