#include <iostream>
#include <string>

#include <selector.h>
#include <sequence.h>

#include <reload.h>
#include <shoot.h>
#include <patrol.h>

#include <IsTargetVisible.h>
#include <IsTargetInRange.h>
#include <IsAmmoEmpty.h>

#include <console_colors.h>

namespace {
    const char* getNodeColor(const INode* node)
    {
        if (dynamic_cast<const Selector*>(node))
            return Color::yellow;

        if (dynamic_cast<const Sequence*>(node))
            return Color::cyan;

        if (dynamic_cast<const Condition*>(node))
            return Color::blue;

        if (dynamic_cast<const Action*>(node))
            return Color::green;

        return Color::white;
    }

    void printTree(const INode* node,
                          const std::string& prefix = "",
                          const bool isLast = true)
    {
        if (!node)
            return;

        // tree structure prefix
        std::cout << prefix
                  << (isLast ? "└─ " : "├─ ");

        // apply color
        const char* color = getNodeColor(node);

        std::cout << color
                  << node->getName()
                  << Color::reset
                  << "\n";

        // recurse if composite
        if (const auto comp = dynamic_cast<const Composite*>(node))
        {
            const auto count = comp->getChildCount();

            for (size_t i = 0; i < count; ++i)
            {
                const bool lastChild = (i + 1 == count);

                printTree(comp->getChild(i),
                          prefix + (isLast ? "   " : "│  "),
                          lastChild);
            }
        }
    }

}

int main() {
    BlackBoard bb
    {
        true,
        true,
        100,
        {0.f, 0.f},
        {100.f, 100.f},
    };


    const auto root = std::make_unique<Selector>();

    auto combat = std::make_unique<Sequence>();
    combat->addChild(std::make_unique<IsTargetVisible>(bb));

    auto combatSelector = std::make_unique<Selector>();

    auto reloadSeq = std::make_unique<Sequence>();
    reloadSeq->addChild(std::make_unique<IsAmmoEmpty>(bb));
    reloadSeq->addChild(std::make_unique<Reload>(bb));
    combatSelector->addChild(std::move(reloadSeq));

    auto shootSeq = std::make_unique<Sequence>();
    shootSeq->addChild(std::make_unique<IsTargetInRange>(bb));
    shootSeq->addChild(std::make_unique<Shoot>(bb));
    combatSelector->addChild(std::move(shootSeq));

    combat->addChild(std::move(combatSelector));

    root->addChild(std::move(combat));
    root->addChild(std::make_unique<Patrol>(bb));

    printTree(root.get());

    root->tick(0.f);

    return 0;
}
