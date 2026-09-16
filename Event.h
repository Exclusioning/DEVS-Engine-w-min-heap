#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED
#include "TimeMoment.h"
#include "AtomicModel.h"
#include "EventType.h"
struct Event{
    TimeMoment time;
    AtomicModel<int, int>* model;
    EventType type;
    int quantity;

    Event(TimeMoment t, AtomicModel<int, int>* m, EventType ty){
        time = t;
        model = m;
        type = ty;
        quantity = 0;
    }

    Event(TimeMoment t, AtomicModel<int, int>* m, EventType ty, int q){
        time = t;
        model = m;
        type = ty;
        quantity = q;
    }

    bool operator<(const Event& other) const{
        return time < other.time;
    }
};


#endif // EVENT_H_INCLUDED
