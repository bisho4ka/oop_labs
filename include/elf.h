#pragma once

#include "npc.h"
#include "visitor.h"

class Elf : public NPC {
public:
    Elf(const std::string& name, int x, int y);

    void acceptVisitor(Visitor& visitor, std::shared_ptr<NPC> other) override;

    void save(std::ostream& os) const override;
    void print() const override;

    ~Elf() override = default;
};

