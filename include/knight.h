#pragma once

#include "npc.h"
#include "visitor.h"

using oneNPC = std::shared_ptr<NPC>;

class Knight : public NPC {
public:
    Knight(const std::string& name, int x, int y);

    void acceptVisitor(Visitor& visitor, oneNPC other) override;

    void save(std::ostream& os) const override;
    void print() const override;

    ~Knight() override = default;
};

