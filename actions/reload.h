#pragma once

#include <action.h>
#include <blackboard.h>

class Reload : public Action
{
public:
    explicit Reload(BlackBoard& bb) : blackboard(bb) {}

    [[nodiscard]] std::string_view getName() const override { return "Reload"; }

    Rule tick(float) override
    {
        blackboard.ammo = 10;
        return Rule::SUCCESS;
    }

    void reset() override {}

private:
    BlackBoard& blackboard;
};
