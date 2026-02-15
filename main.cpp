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
        3,
        {0.f, 0.f},
        {3.f, 4.f},
        {10.f, 0.f},
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

    std::cout << "\n--- COMBAT TICKS ---\n\n";
    tree.tick(0.2f, bb);
    tree.tick(0.2f, bb);

    std::cout << "\n--- PATROL TICKS ---\n\n";
    bb.targetVisible = false;
    for (int i = 0; i < 5; ++i) {
        tree.tick(0.2f, bb);
    }

    return 0;
}
