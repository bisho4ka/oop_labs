#include "../include/npc.h"
#include "../include/visitor.h"
#include "../include/factory.h"
#include "../include/logger.h"
#include "../include/coroutine.h"

extern std::vector<oneNPC> NPCs;
extern std::atomic<bool> game_over;     

NPC::NPC(NpcType type, const std::string& name, int x, int y) : type(type), name(name), x(x), y(y), isAlive(true) {
    if (type == NpcType::KnightType) {
        move_distance = 30;
        kill_distance = 10;
    } else if (type == NpcType::DruidType) {
        move_distance = 10;
        kill_distance = 10;
    } else if (type == NpcType::ElfType) {
        move_distance = 10;
        kill_distance = 50;
    }
    else {
        move_distance = 0;
        kill_distance = 0;
    }
}

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
    os << static_cast<int>(type) << ' ' << name << ' ' << x << ' ' << y << ' ' << isAlive << '\n';
}

void NPC::print() const {
    if (isAlive)
        std::cout << "Расса: " << static_cast<int>(type) << ", Имя: " << name << ", Координаты: (" << x << ", " << y << ")" << std::endl;
}

void NPC::handleFight(oneNPC &other, int attack_strength, int protection_strength) {
    VisitorFight fight(*this);
    other->acceptVisitor(fight, shared_from_this());

    if (attack_strength > protection_strength) {
        if (fight.protectorDie) {
            other->isAlive = false;
            other->inform(name + " одержал победу в бою с " + other->name);
        }
    } else {
        if (fight.attackerDie) {
            isAlive = false;
            inform(other->name + " одержал победу в бою с " + name);
        }
    }
}

bool NPC::isAtDistance(const oneNPC& other, size_t distance) const {
    int dx = x - other->x;
    int dy = y - other->y;
    bool isTrue = (dx * dx + dy * dy) <= static_cast<int>(distance * distance);
    return isTrue;}

oneNPC NPC::load(std::istream& is) {
    std::string name;
    bool isAlive;
    int iType, x, y;

    if (is >> iType >> name >> x >> y >> isAlive) {
        NpcType type = static_cast<NpcType>(iType);
        auto npc = NPCFactory::createNPC(type, name, x, y);
        npc->isAlive = isAlive;
        return npc;
    }
    
    throw std::runtime_error("Ошибка загрузки NPC");
}

CoroutineTask NPC::start() {
    static thread_local std::default_random_engine generator(std::random_device{}());
    std::uniform_int_distribution<int> points_distribution(1, 6);
    std::uniform_int_distribution<int> move_distribution(-move_distance, move_distance);

    while (isAlive && !game_over.load()) {
        x += move_distribution(generator);
        y += move_distribution(generator);

        x = std::clamp(x, 0, 100);
        y = std::clamp(y, 0, 100);

        for (auto& other : NPCs) {
            if (other.get() == this || !other->isAlive) continue;

            if (isAtDistance(other, kill_distance)) {
                int attack_strength = points_distribution(generator);
                int protection_strength = points_distribution(generator);
                handleFight(other, attack_strength, protection_strength);
                
                if (!isAlive) co_return;
            }
        }
        co_await std::suspend_always{};
    }
}
