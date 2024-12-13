#include <gtest/gtest.h>

#include "../include/npc.h"
#include "../include/visitor.h"
#include "../include/observer.h"
#include "../include/factory.h"
#include "../include/knight.h"
#include "../include/elf.h"
#include "../include/druid.h"
#include "../include/coroutine.h"

std::vector<std::shared_ptr<NPC>> NPCs;
std::atomic<bool> game_over(false);

TEST(NPCTest, VisitTest) {
    auto knight = NPCFactory::createNPC(NpcType::KnightType, "Шрек", 0, 0);
    auto elf = NPCFactory::createNPC(NpcType::ElfType, "Фрирен", 0, 0);
    auto druid = NPCFactory::createNPC(NpcType::DruidType, "Галадриэль", 0, 0);

    EXPECT_EQ(knight->name, "Шрек");
    EXPECT_EQ(elf->name, "Фрирен");
    EXPECT_EQ(druid->name, "Галадриэль");
    
    VisitorFight fight1(*knight);
    elf->acceptVisitor(fight1, knight);

    VisitorFight fight2(*elf);
    druid->acceptVisitor(fight2, elf);

    VisitorFight fight3(*druid);
    druid->acceptVisitor(fight3, druid);

    EXPECT_TRUE(fight1.attackerDie);
    EXPECT_TRUE(fight1.protectorDie);

    EXPECT_FALSE(fight2.attackerDie);
    EXPECT_TRUE(fight2.protectorDie);

    EXPECT_TRUE(fight3.attackerDie);
    EXPECT_TRUE(fight3.protectorDie);
}

TEST(NPCTest, isAtDistanceTest) {
    auto knight = NPCFactory::createNPC(NpcType::KnightType, "Благородный", 30, 40);
    auto elf = NPCFactory::createNPC(NpcType::ElfType, "Длинноухий", 0, 0);
    auto druid = NPCFactory::createNPC(NpcType::DruidType, "Дружелюбный", 6, 8);

    EXPECT_TRUE(knight->isAtDistance(elf, 50));
    EXPECT_TRUE(elf->isAtDistance(druid, 10));
    EXPECT_FALSE(druid->isAtDistance(knight, 5));
}

TEST(NPCTest, SaveTest) {
    auto knight = NPCFactory::createNPC(NpcType::KnightType, "Шрек", 50, 50);

    std::ostringstream os;
    knight->save(os);

    std::istringstream is(os.str());
    auto loadKnight = NPC::load(is);

    ASSERT_NE(loadKnight, nullptr);
    EXPECT_EQ(loadKnight->type, NpcType::KnightType);
    EXPECT_EQ(loadKnight->name, "Шрек");
    EXPECT_EQ(loadKnight->x, knight->x);
    EXPECT_EQ(loadKnight->y, knight->y);
    EXPECT_EQ(loadKnight->isAlive, knight->isAlive);
}

TEST(NPCTest, Movement) {
    auto knight = NPCFactory::createNPC(NpcType::KnightType, "Шрек", 10, 20);
    NPCs.push_back(knight);

    auto posX = knight->x;
    auto posY = knight->y;

    auto coTask = knight->start();
    Scheduler::instance().schedule(std::move(coTask));
    Scheduler::instance().start();

    EXPECT_NE(knight->x, posX);
    EXPECT_NE(knight->y, posY);
    NPCs.clear();

}

TEST(NPCTest, GameOver) {
    auto druid = NPCFactory::createNPC(NpcType::DruidType, "Галадриэль", 2, 6);

    game_over.store(true);

    auto coTask = druid->start();
    Scheduler::instance().schedule(std::move(coTask));
    Scheduler::instance().start();

    EXPECT_TRUE(coTask.done());
    game_over.store(false);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}