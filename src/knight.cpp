#include "../include/knight.h"

Knight::Knight(const std::string& name, int x, int y) : NPC(NpcType::KnightType, name, x, y) {}

void Knight::acceptVisitor(Visitor& visitor, oneNPC other) {
    visitor.visit(*this, other);
}

void Knight::save(std::ostream& os) const {
    NPC::save(os);
}

void Knight::print() const {
    std::cout << "Рыцарь: " << name << ", Координаты: (" << x << ", " << y << ")" << std::endl;
}
