#pragma once

#include <blackboard.h>
#include <condition.h>

class IsTargetInRange : public Condition {
public:
    explicit IsTargetInRange(BlackBoard &contextInfo) : board{contextInfo} {
    }

    [[nodiscard]] std::string_view getName() const override { return "IsTargetInRange"; }

    Rule tick(float) override {
        if (board.targetInRange) {
            return Rule::SUCCESS;
        }

        return Rule::FAILURE;
    }

private:
    BlackBoard &board;
};
