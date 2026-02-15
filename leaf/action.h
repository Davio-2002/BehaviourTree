#pragma once

#include <i_node.h>

class Action : public INode {
public:
    Rule tick(float dT) override = 0;

    void reset() override {};

    ~Action() override = default;
};
