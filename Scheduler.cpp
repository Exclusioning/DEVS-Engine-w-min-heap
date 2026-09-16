#include "Scheduler.h"
#include "Action.h"
#include "TimeMoment.h"
#include "AtomicModel.h"
#include "EventType.h"
#include <limits>
#include <stdexcept>
#include <iostream>

using namespace std;
//TimeMoment* input = new TimeMoment(0.0, 0);

Scheduler::Scheduler(Network* network){
        this->network = network;
        this->input = TimeMoment(0.0, 0);
        this->counter = 0;
        this->finishedParts = 0;
}

void Scheduler::scheduleExternal(AtomicModel<int, int>* model, int quantity){
        bool confluentChecker = false;

        for (auto& eventCheck : queue.data) {
            if (eventCheck.model == model && eventCheck.type == EventType::INTERNAL && eventCheck.time.time == input.time) {
                eventCheck.type = EventType::CONFLUENT;
                eventCheck.quantity += quantity;
                confluentChecker = true;
                break;
            }
        }

        if(!confluentChecker){
        Event event(TimeMoment(input.time, counter++), model, EventType::EXTERNAL, quantity);
        queue.insert(event);
        }

}

void Scheduler::output(int amount){
    finishedParts += amount;
}


int Scheduler::runUntilPart(double timeToFinish){

    while (!queue.isEmpty()){
        Event event = queue.extractMin();


        if(event.time.time > timeToFinish){
            queue.insert(event);
            break;
        }

        double timeElapsed = event.time.time - input.time;
        input = event.time;

        AtomicModel<int, int>* model = event.model;

        if(event.type == EventType::EXTERNAL){
            model->deltaExt(event.quantity, timeElapsed);

        } else if (event.type == EventType::INTERNAL){

            int out = model->lambda();
            model->deltaInt();
            if(out >= 0){
                network->output(model, out, this);
            }

        } else if (event.type == EventType::CONFLUENT){
            model->deltaCon(event.quantity);
            int out = model->lambda();
            if(out >= 0){
            network->output(model, out, this);
    }
        }

        double timeAdvance = model->timeAdvance();
        if(timeAdvance < numeric_limits<double>::infinity() && timeAdvance > 0){
            bool hasExisting = false;

            for(const Event& ev : queue.data){
                if(ev.model == model && ev.type == EventType::INTERNAL){
                    hasExisting = true;
                    break;
                }
            }
            if(!hasExisting || event.type == EventType::INTERNAL){
                TimeMoment next(input.time + timeAdvance, counter++);
                queue.insert(Event(next, model, EventType::INTERNAL, 0));

            }
        }
    }

    input = TimeMoment(timeToFinish, counter++);
    int result = finishedParts;
    finishedParts = 0;
    return result;
}
