#pragma once

#include <action.h>
#include <blackboard.h>
#include <cmath>

class Patrol : public Action
{
public:
    explicit Patrol(BlackBoard& bb) : blackboard(bb) {}

    [[nodiscard]] std::string_view getName() const override { return "Patrol"; }

    Rule tick(const float dt) override
    {
        constexpr float speed = 2.0f;

        Vec2 dir{
            blackboard.patrolPoint.x - blackboard.position.x,
            blackboard.patrolPoint.y - blackboard.position.y
        };

        const float distSq = dir.x * dir.x + dir.y * dir.y;

        if (distSq < 0.01f) {
            return Rule::SUCCESS;
        }

        const float length = std::sqrt(distSq);
        dir.x /= length;
        dir.y /= length;

        blackboard.position.x += dir.x * speed * dt;
        blackboard.position.y += dir.y * speed * dt;

        return Rule::RUNNING;
    }


private:
    BlackBoard& blackboard;
};
