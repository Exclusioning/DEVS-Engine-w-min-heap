#include <iostream>
#include "Scheduler.h"
#include "Action.h"
#include "Network.h"

using namespace std;

int main()
{
    cout << "Welcome to BlackSmith Network" << endl;

    Action oreMining("OreMining", 1.0);
    Action forge("Forge", 2.0);
    Action cuttingWood("Cutting Wood", 1.5);
    Action crafting("Crafting", 1.5);
    Action market("Market", 3.0);
    Action shopStorage("Shop Storage", 0.5);
    int profit = 0;

    Network blacksmith(&oreMining, &forge, &cuttingWood, &crafting, &market, &shopStorage);

    Scheduler schedule(&blacksmith);
    cout << "Enter <Time>, <Quantity of Ore/Wood>" << endl;
    cout << "-1 -1 to quit." << endl;

    while(true){

        double time;
        int quantity;
        cin >> time >> quantity;
        if(time || quantity == -1){
            break;
        }
        if(time < schedule.input.time){
            time = schedule.input.time;
        }

        blacksmith.input(&schedule, quantity);

        int daggers = schedule.runUntilPart(time);

        cout << "Daggers finished: " << daggers << endl;
        profit += daggers * 10;
        cout << "Profit: " << profit << endl;
    }
    cout << "Network over." << endl;
    return 0;
}
