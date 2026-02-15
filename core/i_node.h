#pragma once

#include <bt_types.h>
#include <string_view>

struct INode
{
    virtual Rule tick(float dT) = 0;

    virtual void reset() = 0;

    [[nodiscard]] virtual std::string_view getName() const = 0;

    virtual ~INode() = default;
};
