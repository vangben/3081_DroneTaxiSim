#ifndef BEELINE_H_
#define BEELINE_H_

/**
 * include
 */
#include "math/vector3.h"
#include <vector>
#include "IStrategy.h"
#include "entity.h"
#include "distance_function.h"

/**
 * @brief this class inhertis from the IStrategy class and is responsible for generating the beeline that the drone will take.
 */
class Beeline : public IStrategy {
public:
    Beeline(Vector3 pos_, Vector3 des_);
    ~Beeline();
    void Move(IEntity* entity, double dt);
    bool IsCompleted();
    float getDistance();
    void Collect(WalletDecorator* wallet){ wallet->Pay(); } // Drone collects money from robot as they are traveling


protected:
    Vector3 des;
    Vector3 pos;
    Vector3 lastPos;
    float distance; 
}; //end class
#endif // BEELINE_H_