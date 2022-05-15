#ifndef Dijkstra_STRATEGY_H_
#define Dijkstra_STRATEGY_H_

/**
 * include
 */
#include "math/vector3.h"
#include <vector>
#include "IStrategy.h"
#include "entity.h"
/**
 * @brief this class inhertis from the IStrategy class and is responsible for generating the beeline that the drone will take.
 */
class DijkstraStrategy : public IStrategy {
public:
    DijkstraStrategy(Vector3 pos_, Vector3 des_, const IGraph* graph_);
    ~DijkstraStrategy();
    void Move(IEntity* entity, double dt);
    bool IsCompleted();
    std::vector<std::vector<float>> GetPath();
    void Collect(WalletDecorator* wallet); // Drone collects money from robot as they are traveling


protected:
    Vector3 des;
    Vector3 lastPos;
    std::vector<std::vector<float>> path;
    int currentIndex;
    int maxIndex;
}; //end class
#endif // Dijkstra_STRATEGY_H_