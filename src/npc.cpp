#include "../include/factory.h"
#include "../include/npc.h"
#include "../include/visitor.h"

NPC::NPC(NpcType type, const std::string& name, int x, int y) : type(type), name(name), x(x), y(y) {}

void NPC::inform(const std::string& info) {
    for (auto& weakObserver : observers) {
        if (auto obs = weakObserver.lock())
            obs->resultFight(info);
    }
}

void NPC::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void NPC::save(std::ostream& os) const {
    os << static_cast<int>(type) << ' ' << name << ' ' << x << ' ' << y << '\n';
}

void NPC::print() const {
    std::cout << "Расса: " << static_cast<int>(type) << ", имя: " << name << ", координаты: (" << x << ", " << y << ")" << std::endl;
}

bool NPC::isAtDistance(const oneNPC& other, size_t distance) const {
    int dx = x - other->x;
    int dy = y - other->y;
    bool isTrue = (dx * dx + dy * dy) <= static_cast<int>(distance * distance);
    return isTrue;
}

oneNPC NPC::load(std::istream& is) {
    std::string name;
    int iType, x, y;

    if (is >> iType >> name >> x >> y) {
        NpcType type = static_cast<NpcType>(iType);
        return NPCFactory::createNPC(type, name, x, y);
    }
    
    return nullptr;
}

void saveNpcToFile(const moreNPC& npcs, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << npcs.size() << '\n';
        for (const auto& npc : npcs) {
            npc->save(outputFile);
        }
    }
}

moreNPC loadNPCsFromFile(const std::string& filename) {
    moreNPC npcs;
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        size_t npcCount;
        inputFile >> npcCount;
        for (size_t i = 0; i < npcCount; i++) {
            auto npc = NPC::load(inputFile);
            if (npc) 
                npcs.insert(npc);
        }
    }
    return npcs;
}

moreNPC startFight(moreNPC& npcs, size_t range) {
    moreNPC killedNPCs;
    auto npcsCopy = npcs;
    for (const auto& attacker : npcsCopy) {
        for (const auto& protector : npcsCopy) {
            if (attacker != protector && attacker->isAtDistance(protector, range)) {
                VisitorFight battle(*attacker);
                protector->acceptVisitor(battle, attacker);
                if (battle.attackerDie) {
                    killedNPCs.insert(attacker);
                    protector->inform(protector->name + " одержал победу в бою с " + attacker->name);
                }
                if (battle.protectorDie) {
                    killedNPCs.insert(protector);
                    attacker->inform(attacker->name + " одержал победу в бою с " + protector->name);
                }
            }
        }
    }
    return killedNPCs;
}