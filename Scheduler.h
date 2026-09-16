#ifndef SCHEDULER_H_INCLUDED
#define SCHEDULER_H_INCLUDED

#include "Heap.h"
#include "Event.h"
#include "Action.h"
#include "TimeMoment.h"
#include "Network.h"
class Network;
class Scheduler{
public:
    Heap<Event> queue;
    Network* network;

    TimeMoment input;
    int counter = 0;
    int finishedParts = 0;
    int finishedXOR = 0;

    Scheduler(Network* network);

    void scheduleExternal(AtomicModel<int, int>* model, int quantity);

    void output(int amount);
    int runUntilPart(double timeToFinish);

};


#endif // SCHEDULER_H_INCLUDED
