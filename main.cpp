#include <iostream>

#include <selector.h>
#include <sequence.h>

#include <reload.h>
#include <shoot.h>
#include <patrol.h>

#include <IsTargetVisible.h>
#include <IsTargetInRange.h>
#include <IsAmmoEmpty.h>

#include <behaviour_tree.h>
#include <bt_tracer.h>
#include <tree_printer.h>

int main() {
    BlackBoard bb
    {
        true,
        true,
        100,
        {0.f, 0.f},
        {100.f, 100.f},
    };


    auto root = std::make_unique<Selector>();

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

    constexpr TreePrinterOptions printerOptions{.enableColors = true};
    printTree(root.get(), printerOptions);

    std::cout << "\n--- TICKING BEHAVIOUR TREE ---\n\n";

    const BehaviourTree tree(std::move(root));

    BTTracer::instance().setEnabled(true);
    tree.tick(0.2f);

    return 0;
}
