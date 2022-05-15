#ifndef ISTRATEGY_H_
#define ISTRATEGY_H_

#include <vector>
#include "graph.h"
#include "entity.h"
#include "WalletDecorator.h"

using namespace routing;

class IStrategy {
    public:
        virtual void Move(IEntity* entity, double dt) = 0;
        virtual bool IsCompleted() = 0;
        virtual void Collect(WalletDecorator* wallet) = 0;
    protected:
        // IGraph object to be used in the simulation.
        const IGraph* graph;
}; //close class 

#endif // ISTRATEGY_H_