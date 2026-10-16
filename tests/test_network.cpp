#include <gtest/gtest.h>
#include "../Network.h"
#include "../Action.h"

TEST(BlackSmithNetworkTest, InitialStateCheck) {
    Action oreMining("OreMining", 1.0);
    Action forge("Forge", 2.0);
    Action cuttingWood("Cutting Wood", 1.5);
    Action crafting("Crafting", 1.5);
    Action market("Market", 3.0);
    Action shopStorage("Shop Storage", 0.5);

    Network blacksmith(&oreMining, &forge, &cuttingWood, &crafting, &market, &shopStorage);

    EXPECT_EQ(blacksmith.bladesWaiting, 0);
    EXPECT_EQ(blacksmith.handlesWaiting, 0);
}