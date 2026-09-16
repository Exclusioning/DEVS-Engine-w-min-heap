#ifndef ATOMICMODEL_H_INCLUDED
#define ATOMICMODEL_H_INCLUDED
template<typename I, typename O>
class AtomicModel{
public:
    virtual int lambda() = 0;
    virtual void deltaInt() = 0;
    virtual void deltaExt(int input, double elapsedTime) = 0;
    virtual void deltaCon(int input) = 0;
    virtual double timeAdvance() = 0;

    virtual ~AtomicModel(){}

};


#endif // ATOMICMODEL_H_INCLUDED
