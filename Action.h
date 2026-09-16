#ifndef ACTION_H_INCLUDED
#define ACTION_H_INCLUDED
#include <string>
#include <limits>
#include "AtomicModel.h"

using namespace std;

class Action : public AtomicModel<int, int> {
public:
        string name;
        double processTime;

        int partsProcessing = 0;
        double timeRemaining = numeric_limits<double>::infinity();

        Action(string name, double processTime){
            this->name = name;
            this->processTime = processTime;
        }

        int lambda(){
            return 1;
        }

        void deltaInt(){

            if(partsProcessing > 0){
                partsProcessing = partsProcessing - 1;
                timeRemaining = processTime;
            } else {
                timeRemaining = numeric_limits<double>::infinity();
            }
        }

        void deltaExt(int quantity, double elapsedTime){
            int input = quantity;

            if(partsProcessing > 0){
                partsProcessing += input;
            } else {
                partsProcessing = quantity;
                    timeRemaining = processTime;
            }
        }

        void deltaCon(int quantity){
            int input = quantity;
            partsProcessing = (partsProcessing - 1) + input;
            timeRemaining = processTime;
        }

        double timeAdvance(){
            if(partsProcessing > 0){
                return timeRemaining;
            }
            return numeric_limits<double>::infinity();
        }

        string getName(){
            return name;
        }

        ~Action() override {}
};


#endif // ACTION_H_INCLUDED
