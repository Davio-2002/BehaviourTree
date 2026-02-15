#pragma once

#include <action.h>
#include <blackboard.h>

class Shoot : public Action {
public:
    explicit Shoot(BlackBoard &bb) : blackboard(bb) {
    }

    Rule tick(float) override {
        if (!blackboard.targetVisible) {
            return Rule::FAILURE;
        }

        if (blackboard.ammo <= 0) {
            return Rule::FAILURE;
        }


        constexpr float range = 5.0f;

        const float dx = blackboard.targetPos.x - blackboard.position.x;
        const float dy = blackboard.targetPos.y - blackboard.position.y;

        if (const float distanceSq = dx * dx + dy * dy;
            distanceSq > range * range)
        {

            return Rule::FAILURE;
        }

        --blackboard.ammo;

        return Rule::SUCCESS;
    }

private:
    BlackBoard &blackboard;
};
