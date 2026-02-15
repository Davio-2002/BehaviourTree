#pragma once

#include <composite.h>

class Sequence : public Composite {
public:
    Rule tick(const float dT) override {
        while (currentNode < children.size()) {
            const auto rule = children[currentNode]->tick(dT);

            if (rule == Rule::SUCCESS) {
                ++currentNode;
                continue;
            }

            if (rule == Rule::RUNNING) {
                return Rule::RUNNING;
            }

            reset();
            return Rule::FAILURE;
        }

        reset();
        return Rule::SUCCESS;
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
