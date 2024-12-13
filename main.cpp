#include "include/factory.h"
#include "include/npc.h"
#include "include/observer.h"
#include "include/visitor.h"
#include "include/logger.h"
#include "include/coroutine.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <atomic>
#include <chrono>
#include <thread>

std::atomic<bool> game_over(false);
std::vector<std::shared_ptr<NPC>> NPCs;

int main() {
    std::srand(static_cast<unsigned int>(time(nullptr)));

    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("battle_log.txt");

    for (int i = 0; i < 50; i++) {
        NpcType type = static_cast<NpcType>(std::rand() % 3 + 1);
        std::string npcName = "Npc_" + std::to_string(i + 1);
        int posX = std::rand() % 100;
        int posY = std::rand() % 100;

        auto npc = NPCFactory::createNPC(type, npcName, posX, posY);
        npc->addObserver(consoleObserver);
        npc->addObserver(fileObserver);
        NPCs.push_back(npc);
    }

    for (auto& npc : NPCs) {
        Scheduler::instance().schedule(npc->start());
    }

    std::thread scheduler_thread([]() {
        try {
            while (!game_over.load()) {
                Scheduler::instance().start();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        } catch (const std::exception& e) {
            std::cerr << "Ошибка scheduler: " << e.what() << std::endl;
        }
    });
    
    auto start_time = std::chrono::steady_clock::now();
    while (!game_over) {
        Logger::logBlock([&]() {
            std::cout << "\nСписок всех NPC на карте:\n" << std::endl;
            for (const auto& npc : NPCs) {
                if (npc->isAlive) 
                    npc->print();
            }
            std::cout << std::endl;
        });
        std::this_thread::sleep_for(std::chrono::seconds(1));

        auto elapsed = std::chrono::steady_clock::now() - start_time;
        if (std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() >= 30)
            game_over = true;
    }

    scheduler_thread.join();

    Logger::log("Итак!! Финал!! А вот и победители (выжившие NPC):");
    for (const auto& npc : NPCs) 
        npc->print();

    return 0;
}