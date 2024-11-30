#include <gtest/gtest.h>

#include "../include/npc.h"
#include "../include/visitor.h"
#include "../include/observer.h"
#include "../include/factory.h"
#include "../include/knight.h"
#include "../include/elf.h"
#include "../include/druid.h"


TEST(NPCTest, VisitTest) {
    auto knight = NPCFactory::createNPC(NpcType::KnightType, "Рыцарь Владимир", 0, 0);
    auto elf = NPCFactory::createNPC(NpcType::ElfType, "Эльф Фрирен", 0, 0);
    auto druid = NPCFactory::createNPC(NpcType::DruidType, "Друид Ден", 0, 0);

    EXPECT_EQ(knight->name, "Рыцарь Владимир");
    EXPECT_EQ(elf->name, "Эльф Фрирен");
    EXPECT_EQ(druid->name, "Друид Ден");
   
    auto consoleObserver = std::make_shared<ConsoleObserver>();

    knight->addObserver(consoleObserver);
    elf->addObserver(consoleObserver);
    druid->addObserver(consoleObserver);

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
    auto knight = NPCFactory::createNPC(NpcType::KnightType, "Геральд", 30, 40);
    auto elf = NPCFactory::createNPC(NpcType::ElfType, "Легалас", 0, 0);
    auto druid = NPCFactory::createNPC(NpcType::DruidType, "Постарамикс", 6, 8);

    EXPECT_TRUE(knight->isAtDistance(elf, 50));
    EXPECT_TRUE(elf->isAtDistance(druid, 10));
    EXPECT_FALSE(druid->isAtDistance(knight, 5));
}

TEST(NPCTest, SaveTest) {
    auto elf = NPCFactory::createNPC(NpcType::ElfType, "Крафт", 50, 50);

    std::ostringstream os;
    elf->save(os);

    std::istringstream is(os.str());
    auto loadElf = NPC::load(is);

    ASSERT_NE(loadElf, nullptr);
    EXPECT_EQ(loadElf->type, NpcType::ElfType);
    EXPECT_EQ(loadElf->x, 50);
    EXPECT_EQ(loadElf->y, 50);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}