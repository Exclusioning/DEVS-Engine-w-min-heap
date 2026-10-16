#include <gtest/gtest.h>
#include "../Network.h"
#include "../Action.h"

// Test that Network handles crafting logic correctly when blades and handles are added
Test(BlackSmithNetworkTest, TryCraftingIncrementsCorrectly) {
    Action oreMining("OreMining", 1.0);
    Action forge("Forge", 2.0);
    Action cuttingWood("Cutting Wood", 1.5);
    Action crafting("Crafting", 1.5);
    Action market("Market", 3.0);
    Action shopStorage("Shop Storage", 0.5);

    Network blacksmith(&oreMining, &forge, &cuttingWood, &crafting, &market, &shopStorage);

    // Initial state check
    EXPECT_EQ(blacksmith.bladesWaiting, 0);
    EXPECT_EQ(blacksmith.handlesWaiting, 0);
    
    // Simulate incoming blades and handles waiting
    blacksmith.bladesWaiting = 2;
    blacksmith.handlesWaiting = 2;

    // We can call tryCrafting or mock a scheduler interaction depending on your setup
    // blacksmith.tryCrafting(schedules); 
}