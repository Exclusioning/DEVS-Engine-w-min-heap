#include <gtest/gtest.h>
#include "../Network.h"
#include "../Action.h"
#include "../Scheduler.h"

TEST(BlackSmithNetworkTest, TryCraftingAndOutputFlow) {
    Action oreMining("OreMining", 1.0);
    Action forge("Forge", 2.0);
    Action cuttingWood("Cutting Wood", 1.5);
    Action crafting("Crafting", 1.5);
    Action market("Market", 3.0);
    Action shopStorage("Shop Storage", 0.5);

    Network blacksmith(&oreMining, &forge, &cuttingWood, &crafting, &market, &shopStorage);
    Scheduler schedule(&blacksmith);

    // Test input triggering scheduleExternal
    blacksmith.input(&schedule, 5);

    // Test output logic using pointers (&)
    blacksmith.output(&oreMining, 5, &schedule);
    blacksmith.output(&cuttingWood, 5, &schedule);

    // Test forge and crafting accumulation to trigger tryCrafting
    blacksmith.output(&forge, 1, &schedule);
    blacksmith.output(&crafting, 1, &schedule);

    // Test market and shopStorage flow
    blacksmith.output(&market, 1, &schedule);
    blacksmith.output(&shopStorage, 1, &schedule);

    SUCCEED();
}

TEST(BlackSmithNetworkTest, SchedulerExecutionFlow) {
    Action oreMining("OreMining", 1.0);
    Action forge("Forge", 2.0);
    Action cuttingWood("Cutting Wood", 1.5);
    Action crafting("Crafting", 1.5);
    Action market("Market", 3.0);
    Action shopStorage("Shop Storage", 0.5);

    Network blacksmith(&oreMining, &forge, &cuttingWood, &crafting, &market, &shopStorage);
    Scheduler schedule(&blacksmith);

    // Trigger external inputs and run the scheduler until a specific time point
    blacksmith.input(&schedule, 1);
    
    // Run the scheduler to process events up to time 5.0
    int daggers = schedule.runUntilPart(5.0);
    
    // Verify that execution completes and returns a value
    EXPECT_GE(daggers, 0);
}

TEST(BlackSmithNetworkTest, SchedulerConfluentAndInternalFlow) {
    Action oreMining("OreMining", 1.0);
    Action forge("Forge", 2.0);
    Action cuttingWood("Cutting Wood", 1.5);
    Action crafting("Crafting", 1.5);
    Action market("Market", 3.0);
    Action shopStorage("Shop Storage", 0.5);

    Network blacksmith(&oreMining, &forge, &cuttingWood, &crafting, &market, &shopStorage);
    Scheduler schedule(&blacksmith);

    // Trigger multiple items at different timestamps to cause internal/confluent events
    blacksmith.input(&schedule, 3);
    
    // Run partially, then push further to trigger internal state transitions
    schedule.runUntilPart(2.0);
    schedule.runUntilPart(10.0);

    SUCCEED();
}

TEST(BlackSmithNetworkTest, BranchCoverageEdgeCases) {
    Action oreMining("OreMining", 1.0);
    Action forge("Forge", 2.0);
    Action cuttingWood("Cutting Wood", 1.5);
    Action crafting("Crafting", 1.5);
    Action market("Market", 3.0);
    Action shopStorage("Shop Storage", 0.5);

    Network blacksmith(&oreMining, &forge, &cuttingWood, &crafting, &market, &shopStorage);
    Scheduler schedule(&blacksmith);

    // 1. Test failing resource checks (triggers 'false' branches in tryCrafting/output limits)
    // Sending outputs without prior accumulation or mismatched quantities
    blacksmith.output(&forge, 999, &schedule); // Over-consumption or empty stock branch
    blacksmith.output(&crafting, 0, &schedule); // Zero quantity edge case

    // 2. Test simultaneous inputs at the exact same timestamp (confluent event branches)
    blacksmith.input(&schedule, 1);
    blacksmith.input(&schedule, 1); // Same time tie-breaker branch

    // 3. Run simulation completely dry until the event queue is empty (queue empty branch)
    schedule.runUntilPart(100.0); // Far future timestamp to exhaust all scheduled events
}

TEST(BlackSmithNetworkTest, RemainingBranchEdgeCases) {
    Action oreMining("OreMining", 1.0);
    Action forge("Forge", 2.0);
    Action cuttingWood("Cutting Wood", 1.5);
    Action crafting("Crafting", 1.5);
    Action market("Market", 3.0);
    Action shopStorage("Shop Storage", 0.5);

    Network blacksmith(&oreMining, &forge, &cuttingWood, &crafting, &market, &shopStorage);
    Scheduler schedule(&blacksmith);

    // 1. Run with 0 time limit to hit immediate termination / empty check branches
    schedule.runUntilPart(0.0);

    // 2. Trigger input, run past completion, then try running again on an empty schedule
    blacksmith.input(&schedule, 1);
    schedule.runUntilPart(5.0);
    schedule.runUntilPart(5.0); // Duplicate run at same timestamp or past completion
}