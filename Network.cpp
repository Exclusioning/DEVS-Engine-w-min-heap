#include "Network.h"
#include <iostream>
using namespace std;

void Network::input(Scheduler* schedule, int quantity){
    schedule->scheduleExternal(oreMining, quantity);
    schedule->scheduleExternal(cuttingWood, quantity);
}

void Network::output(AtomicModel<int, int>* model, int quantity, Scheduler* schedule){
    if(model == oreMining){
        cout << "OreMine -> Forge" << endl;
        schedule->scheduleExternal(forge, quantity);
    } else if(model == forge){
        cout << "Forge Output: " << quantity << endl;
        bladesWaiting += quantity;
        tryCrafting(schedule);
    } else if(model == cuttingWood){
        cout << "Cutting Wood -> Crafting Wood" << endl;
        schedule->scheduleExternal(crafting, quantity);
    } else if(model == crafting){
        cout << "Crafted Handles: " << quantity << endl;
        handlesWaiting += quantity;
        tryCrafting(schedule);
    } else if(model == market){
        cout << "Market added a dagger -> Storage" << endl;
        schedule->scheduleExternal(shopStorage, quantity);
    } else if(model == shopStorage){
        cout << "Storage received: " << quantity << " daggers." << endl;
        schedule->output(quantity);
    }
}

void Network::tryCrafting(Scheduler* schedule){
    while(bladesWaiting > 0 && handlesWaiting > 0){
        bladesWaiting--;
        handlesWaiting--;
        cout << "Crafting a Dagger." << endl;
        schedule->scheduleExternal(market, 1);

    }
}
