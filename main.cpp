#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "include/npc.h"
#include "include/observer.h"
#include "include/visitor.h"
#include "include/factory.h"

using NPCCollection = std::set<std::shared_ptr<NPC>>;

void saveNPCsToFile(const NPCCollection& npcs, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << npcs.size() << '\n';
        for (const auto& npc : npcs) {
            npc->save(outputFile);
        }
    }
}

NPCCollection loadNPCsFromFile(const std::string& filename) {
    NPCCollection npcs;
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        size_t npcCount;
        inputFile >> npcCount;
        for (size_t i = 0; i < npcCount; ++i) {
            auto npc = NPC::load(inputFile);
            if (npc) {
                npcs.insert(npc);
            }
        }
    }
    return npcs;
}

NPCCollection simulateFights(NPCCollection& npcs, size_t range) {
    NPCCollection fallenNPCs;
    auto npcsCopy = npcs;
    for (const auto& attacker : npcsCopy) {
        for (const auto& defender : npcsCopy) {
            if (attacker != defender && attacker->isAtDistance(defender, range)) {
                VisitorFight battle(*attacker);
                defender->acceptVisitor(battle, attacker);
                if (battle.protectorDie) {
                    fallenNPCs.insert(defender);
                    attacker->inform(attacker->name + " победил " + defender->name);
                }
                if (battle.attackerDie) {
                    fallenNPCs.insert(attacker);
                    defender->inform(defender->name + " победил " + attacker->name);
                }
            }
        }
    }
    return fallenNPCs;
}

int main() {
    std::srand(static_cast<unsigned int>(time(nullptr)));

    NPCCollection npcs;

    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("battle_log.txt");

    for (int i = 0; i < 10; ++i) {
        NpcType type = static_cast<NpcType>(std::rand() % 3 + 1);
        std::string npcName = "NPC_" + std::to_string(i + 1);
        int posX = std::rand() % 500;
        int posY = std::rand() % 500;

        auto npc = NPCFactory::createNPC(type, npcName, posX, posY);
        npc->addObserver(consoleObserver);
        npc->addObserver(fileObserver);
        npcs.insert(npc);
    }

    saveNPCsToFile(npcs, "npcs.txt");
    npcs = loadNPCsFromFile("npcs.txt");

    std::cout << "Список всех NPC на карте:" << std::endl;
    for (const auto& npc : npcs) {
        npc->print();
    }

    size_t battleRange;
    std::cout << "Введите дистанцию для битвы: ";
    std::cin >> battleRange;

    while (!npcs.empty()) {
        auto fallen = simulateFights(npcs, battleRange);
        if (fallen.empty()) {
            break;
        }
        for (const auto& dead : fallen) {
            npcs.erase(dead);
        }
    }

    std::cout << "\nИтак!! Финал!! А вот и победители (выжившие NPC):\n" << std::endl;
    for (const auto& npc : npcs) {
        npc->print();
    }

    return 0;
}