#ifndef NETWORK_H_INCLUDED
#define NETWORK_H_INCLUDED
#include "Scheduler.h"
#include "AtomicModel.h"
template<typename I, typename O> class AtomicModel;
class Scheduler;

class Network{
public:
    Action* oreMining;
    Action* forge;
    Action* cuttingWood;
    Action* crafting;
    Action* market;
    Action* shopStorage;

    int bladesWaiting = 0;
    int handlesWaiting = 0;

    Network(Action* oreMining, Action* forge, Action* cuttingWood, Action* crafting, Action* market, Action* shopStorage){
        this->oreMining = oreMining;
        this->forge = forge;
        this->cuttingWood = cuttingWood;
        this->crafting = crafting;
        this->market = market;
        this->shopStorage = shopStorage;
    }

    void input(Scheduler* schedule, int quantity);
    void output(AtomicModel<int, int>* model, int quantity, Scheduler* schedule);
    void tryCrafting(Scheduler* schedule);

};

#endif // NETWORK_H_INCLUDED
