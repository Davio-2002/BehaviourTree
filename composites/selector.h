#pragma once

#include <composite.h>

class Selector : public Composite {
public:
    Rule tick(const float dT) override {
        while (currentNode < children.size()) {
            const auto rule = children[currentNode]->tick(dT);

            if (rule == Rule::FAILURE) {
                ++currentNode;
                continue;
            }

            if (rule == Rule::RUNNING) {
                return Rule::RUNNING;
            }

            reset();
            return Rule::SUCCESS;
        }

        reset();
        return Rule::FAILURE;
    }

    void reset() override {
        currentNode = 0;
        for (const auto &node: children) {
            node->reset();
        }
    }

private:
    std::size_t currentNode = 0;
};
