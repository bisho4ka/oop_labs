#include "../include/druid.h"

Druid::Druid(const std::string& name, int x, int y) : NPC(NpcType::DruidType, name, x, y) {}

void Druid::acceptVisitor(Visitor& visitor, oneNPC other) {
    visitor.visit(*this, other);
}

void Druid::save(std::ostream& os) const {
    NPC::save(os);
}

void Druid::print() const {
    std::cout << "Друид: " << name << ", Координаты: (" << x << ", " << y << ")" << std::endl;
}
