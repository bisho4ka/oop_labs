#include "../include/elf.h"

Elf::Elf(const std::string& name, int x, int y) : NPC(NpcType::ElfType, name, x, y) {}

void Elf::acceptVisitor(Visitor& visitor, oneNPC other) {
    visitor.visit(*this, other);
}

void Elf::save(std::ostream& os) const {
    NPC::save(os);
}

void Elf::print() const {
    if (isAlive)
        std::cout << "Эльф: " << name << ", Координаты: (" << x << ", " << y << ")" << std::endl;
}
