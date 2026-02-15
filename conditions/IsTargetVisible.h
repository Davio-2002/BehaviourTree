#pragma once

#include <blackboard.h>
#include <condition.h>

class IsTargetVisible : public Condition {
public:
    explicit IsTargetVisible(BlackBoard &contextInfo) : board{contextInfo} {
    }

    [[nodiscard]] std::string_view getName() const override { return "IsTargetVisible"; }

    Rule tick(float dT) override {
        if (board.targetVisible) {
            return Rule::SUCCESS;
        }

        return Rule::FAILURE;
    }

private:
    BlackBoard &board;
};
