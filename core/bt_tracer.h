#pragma once

#include <blackboard.h>
#include <i_node.h>
#include <iostream>
#include <ostream>
#include <string>

class BTTracer {
public:
    static BTTracer &instance() {
        static BTTracer tracer;
        return tracer;
    }

    void setEnabled(const bool value) noexcept {
        enabled = value;
    }

    [[nodiscard]] bool isEnabled() const noexcept {
        return enabled;
    }

    void setOutput(std::ostream &stream) noexcept {
        out = &stream;
    }

    void beginTreeTick(const INode *root, const float dt) {
        if (!enabled || !out || !root) {
            return;
        }

        ++tickIndex;
        depth = 0;

        (*out) << "[BT][" << tickIndex << "] tick root " << root->getName()
               << " dt=" << dt << '\n';
    }

    void endTreeTick(const INode *root, const Rule result) {
        if (!enabled || !out || !root) {
            return;
        }

        (*out) << "[BT][" << tickIndex << "] root " << root->getName()
               << " => " << toString(result) << '\n';
    }

    void logBlackboardBefore(const BlackBoard &bb) {
        if (!enabled || !out) {
            return;
        }

        (*out) << "[BT][" << tickIndex << "] BlackBoard (before) " << bb << '\n';
    }

    void logBlackboardAfter(const BlackBoard &bb) {
        if (!enabled || !out) {
            return;
        }

        (*out) << "[BT][" << tickIndex << "] BlackBoard (after)  " << bb << '\n';
    }

    void beginChildTick(const INode *parent, const INode *child, const std::size_t index) {
        if (!enabled || !out || !parent || !child) {
            return;
        }

        (*out) << "[BT][" << tickIndex << "] "
               << std::string(depth * 2, ' ')
               << parent->getName() << " -> child[" << index << "] "
               << child->getName() << '\n';

        ++depth;
    }

    void endChildTick(const INode *parent, const INode *child, const std::size_t index, const Rule result) {
        if (!enabled || !out || !parent || !child) {
            return;
        }

        if (depth > 0) {
            --depth;
        }

        (*out) << "[BT][" << tickIndex << "] "
               << std::string(depth * 2, ' ')
               << parent->getName() << " <- child[" << index << "] "
               << child->getName() << " => " << toString(result) << '\n';
    }

private:
    bool enabled = false;
    std::size_t depth = 0;
    std::size_t tickIndex = 0;
    std::ostream *out = &std::cout;
};
