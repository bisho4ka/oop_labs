#include "../include/npc.h"
#include "../include/visitor.h"
#include "../include/factory.h"

NPC::NPC(NpcType type, const std::string& name, int x, int y) : type(type), name(name), x(x), y(y) {}

void NPC::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void NPC::inform(const std::string& info) {
    for (auto& weakObs : observers) {
        if (auto obs = weakObs.lock())
            obs->resultFight(info);
    }
}

bool NPC::isAtDistance(const std::shared_ptr<NPC>& other, size_t distance) const {
    int dx = x - other->x;
    int dy = y - other->y;
    return (dx * dx + dy * dy) <= static_cast<int>(distance * distance);
}

void NPC::save(std::ostream& os) const {
    os << static_cast<int>(type) << ' ' << name << ' ' << x << ' ' << y << '\n';
}

void NPC::print() const {
    std::cout << "Расса: " << static_cast<int>(type) << ", Имя: " << name << ", Координаты: (" << x << ", " << y << ")" << std::endl;
}

std::shared_ptr<NPC> NPC::load(std::istream& is) {
    std::string name;
    int typeInt;
    int x;
    int y;

    if (is >> typeInt >> name >> x >> y) {
        NpcType type = static_cast<NpcType>(typeInt);
        return NPCFactory::createNPC(type, name, x, y);
    }
    
    return nullptr;
}