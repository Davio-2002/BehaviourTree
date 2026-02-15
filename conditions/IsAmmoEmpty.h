#pragma once

#include <blackboard.h>
#include <condition.h>

class IsAmmoEmpty : public Condition {
public:
    explicit IsAmmoEmpty(BlackBoard &contextInfo) : board{contextInfo} {
    }

    [[nodiscard]] std::string_view getName() const override { return "IsAmmoEmpty"; }

    Rule tick(float) override {
        if (board.ammo <= 0) {
            return Rule::SUCCESS;
        }
        return Rule::FAILURE;
    }

private:
    BlackBoard &board;
};
