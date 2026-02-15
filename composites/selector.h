#pragma once

#include <bt_tracer.h>
#include <composite.h>

class Selector : public Composite {
public:
    [[nodiscard]] std::string_view getName() const override { return "Selector"; }

    Rule tick(const float dT) override {
        while (currentNode < children.size()) {
            auto *child = children[currentNode].get();
            auto &tracer = BTTracer::instance();
            tracer.beginChildTick(this, child, currentNode);
            const auto rule = child->tick(dT);
            tracer.endChildTick(this, child, currentNode, rule);

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
