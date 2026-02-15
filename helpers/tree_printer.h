#pragma once

#include <console_colors.h>
#include <composite.h>
#include <selector.h>
#include <sequence.h>
#include <condition.h>
#include <action.h>
#include <i_node.h>

#include <iostream>
#include <string>
#include <typeinfo>

struct TreePrinterOptions {
    bool enableColors = true;
};

inline const char *getNodeColor(const INode *node, const TreePrinterOptions options = {}) {
    if (!options.enableColors) {
        return "";
    }

    const auto &type = typeid(*node);
    if (type == typeid(Selector)) {
        return Color::yellow;
    }
    if (type == typeid(Sequence)) {
        return Color::magenta;
    }

    return Color::blue;
}

inline const Composite *asComposite(const INode *node) {
    const auto &type = typeid(*node);
    if (type == typeid(Selector) || type == typeid(Sequence) || type == typeid(Composite)) {
        return static_cast<const Composite *>(node);
    }

    return nullptr;
}

inline void printTree(const INode *node,
                      const TreePrinterOptions options = {},
                      const std::string &prefix = "",
                      const bool isLast = true) {
    if (!node) {
        return;
    }

    std::cout << prefix
              << (isLast ? "└─ " : "├─ ");

    auto* color = getNodeColor(node, options);
    std::cout << color
              << node->getName();

    if (options.enableColors) {
        std::cout << Color::reset;
    }
    std::cout << "\n";

    const auto *composite = asComposite(node);
    if (!composite) {
        return;
    }

    const auto count = composite->getChildCount();
    for (std::size_t i = 0; i < count; ++i) {
        const bool lastChild = (i + 1 == count);
        printTree(composite->getChild(i),
                  options,
                  prefix + (isLast ? "   " : "│  "),
                  lastChild);
    }
}
