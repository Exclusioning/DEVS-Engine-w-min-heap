#ifndef TIMEMOMENT_H_INCLUDED
#define TIMEMOMENT_H_INCLUDED
struct TimeMoment{
    double time;
    int order;

    TimeMoment(){
        time = 0;
        order = 0;
    }
    TimeMoment(double t, int o){
        time = t;
        order = o;
    }

    bool operator<(const TimeMoment &other) const{
        if(time < other.time){
            return true;
        }
        if(time > other.time){
            return false;
        }
        return order < other.order;
    }

    bool operator>(const TimeMoment &other) const{
        if(time > other.time){
            return true;
        }
        if(time < other.time){
            return false;
        }
        return order > other.order;
    }

};


#endif // TIMEMOMENT_H_INCLUDED
