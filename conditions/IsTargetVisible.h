#pragma once

#include <blackboard.h>
#include <condition.h>

class IsTargetVisible : public Condition {
public:
    explicit IsTargetVisible(BlackBoard &contextInfo) : board{contextInfo} {
    }

    Rule tick(float dT) override {
        if (board.targetVisible) {
            return Rule::SUCCESS;
        }

        return Rule::FAILURE;
    }

private:
    BlackBoard &board;
};
