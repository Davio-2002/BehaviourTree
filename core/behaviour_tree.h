#pragma once

#include <blackboard.h>
#include <bt_tracer.h>
#include <i_node.h>

class BehaviourTree
{
public:
    explicit BehaviourTree(INodePtr root)
        : rootNode(std::move(root)) {}

    void tick(const float dt, const BlackBoard &bb) const {
        if (rootNode) {
            auto &tracer = BTTracer::instance();
            tracer.beginTreeTick(rootNode.get(), dt);
            tracer.logBlackboardBefore(bb);
            const auto result = rootNode->tick(dt);
            tracer.logBlackboardAfter(bb);
            tracer.endTreeTick(rootNode.get(), result);
        }
    }

private:
    INodePtr rootNode;
};
