#pragma once

#include <memory>
#include <cstdint>
#include <string_view>

enum class Rule : std::uint8_t {
    SUCCESS,
    RUNNING,
    FAILURE
};

constexpr std::string_view toString(const Rule status) noexcept
{
    switch (status)
    {
        case Rule::SUCCESS: return "SUCCESS";
        case Rule::FAILURE: return "FAILURE";
        case Rule::RUNNING: return "RUNNING";
    }

    return "UNKNOWN";
}

struct INode;

using INodePtr = std::unique_ptr<INode>;
