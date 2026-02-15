#pragma once

#include <algorithm>
#include <vector>
#include <i_node.h>

class Composite : public INode {
public:
    void addChild(INodePtr child) {
        children.emplace_back(std::move(child));
    }

    // Accessors for tree traversal/visualization
    [[nodiscard]] std::size_t getChildCount() const { return children.size(); }
    [[nodiscard]] const INode *getChild(const std::size_t idx) const { return children[idx].get(); }

protected:
    std::vector<INodePtr> children;
};
