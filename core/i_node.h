#pragma once

#include <bt_types.h>
#include <string>
#include <typeinfo>
#include <cxxabi.h>

struct INode {
    virtual Rule tick(float dT) = 0;

    virtual void reset() = 0;

    [[nodiscard]] virtual std::string getName() const {
        int status = 0;

        const std::unique_ptr<char, void(*)(void *)> demangled(
            abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, &status),
            std::free
        );

        if (status == 0 && demangled) {
            return demangled.get();
        }

        return typeid(*this).name(); // fallback
    }

    virtual ~INode() = default;
};

using INodePtr = std::unique_ptr<INode>;
