#pragma once

#include <i_node.h>

class BehaviourTree
{
public:
    explicit BehaviourTree(INodePtr root)
        : rootNode(std::move(root)) {}

    void tick(const float dt) const {
        if (rootNode) {
            rootNode->tick(dt);
        }
    }

private:
    INodePtr rootNode;
};
