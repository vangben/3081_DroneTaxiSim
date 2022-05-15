#define _USE_MATH_DEFINES
#include "drone.h"
#include "robot.h"
#include "Beeline.h"
#include "AstarStrategy.h"
#include "DijkstraStrategy.h"
#include "DfsStrategy.h"
#include "SpinDecorator.h"
#include "WalletDecorator.h"
#include <cmath>
#include <limits>

Drone::Drone(JsonObject obj) : details(obj) {
    JsonArray pos(obj["position"]);
    position = {pos[0], pos[1], pos[2]};

    JsonArray dir(obj["direction"]);
    direction = {dir[0], dir[1], dir[2]};

    speed = obj["speed"];

    available = true;
}

Drone::~Drone() {
    // Delete dynamically allocated variables
}

IEntity* Drone::GetNearestEntity(std::vector<IEntity*> scheduler) {
    float minDis = std::numeric_limits<float>::max();
    for(auto entity : scheduler){
        if(entity->GetAvailability()){
            float disToEntity = this->position.Distance(entity->GetPosition());
            if(disToEntity <= minDis){
                minDis = disToEntity;
                nearestEntity = new WalletDecorator(entity); // Decorate each robot
            }
        }
    }
    if(nearestEntity){               // Set strategy for the nearest entity
        nearestEntity->SetAvailability(false);  // set availability to the entity that the drone is picking up
        available = false;                      // set this drone availability as false
        SetDestination(nearestEntity->GetPosition());
        toTargetPosStrategy = new Beeline(this->GetPosition(), nearestEntity->GetPosition());
        std::string targetStrategyName = nearestEntity->GetStrategyName();
        std::cout << "Robot's celebrity status: " << nearestEntity->GetCelebStatus() << "\n";
        if(!nearestEntity->GetCelebStatus()){         //if bot is not celeb(aka 0 value)
             if (targetStrategyName.compare("astar") == 0){
                AstarStrategy* myStrategy = new AstarStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph); //inherits "graph" from entity.h
                toTargetDesStrategy = new SpinDecorator(myStrategy); // add decorator
                std::cout << "Cost of trip: " << myStrategy->GetPath().size() * 0.25<< "\n";
                std::cout << "Robot's start money: " << nearestEntity->GetMoney() << "\n";
                nearestEntity->SetCostOfTrip(myStrategy->GetPath().size() *0.25, 0.25);
            } else if (targetStrategyName.compare("dfs") == 0){
                DfsStrategy* myStrategy = new DfsStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
                toTargetDesStrategy = new SpinDecorator(myStrategy); // add decorator
                std::cout << "Cost of trip: " << myStrategy->GetPath().size() * 0.25<< "\n";
                std::cout << "Robot's start money: " << nearestEntity->GetMoney() << "\n";
                nearestEntity->SetCostOfTrip(myStrategy->GetPath().size() *0.25, 0.25);
            } else if (targetStrategyName.compare("dijkstra") == 0){
                DijkstraStrategy* myStrategy = new DijkstraStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
                toTargetDesStrategy = new SpinDecorator(myStrategy); // add decorator
                std::cout << "Cost of trip: " << myStrategy->GetPath().size() * 0.25<< "\n";
                std::cout << "Robot's start money: " << nearestEntity->GetMoney() << "\n";
                nearestEntity->SetCostOfTrip(myStrategy->GetPath().size() *0.25, 0.25);
            } else {
                // if beeline strategy selected and not a celebrity, default to Dijkstra
                std::cout << "you are a peasant! you cannot use beeline! \nyou've defaulted to dijkstra" << "\n" ;
                DijkstraStrategy* myStrategy = new DijkstraStrategy(nearestEntity->GetPosition(), nearestEntity->GetDestination(), graph);
                toTargetDesStrategy = myStrategy;
                std::cout << "Cost of trip: " << myStrategy->GetPath().size() * 0.25<< "\n";
                std::cout << "Robot's start money: " << nearestEntity->GetMoney() << "\n";
                nearestEntity->SetCostOfTrip(myStrategy->GetPath().size() *0.25, 0.25);
            }
        } else {        //always use beeline if celeb (aka 1 value)
                std::cout << "you are privileged! you have upgraded to beeline and your cost of trip is free!" << "\n";
                Beeline* myStrategy = new Beeline(nearestEntity->GetPosition(), nearestEntity->GetDestination());
                toTargetDesStrategy = myStrategy;
                nearestEntity->SetCostOfTrip(0, 0);
        }
    }
}

void Drone::Update(double dt, std::vector<IEntity*> scheduler) {
    if(available) {
        GetNearestEntity(scheduler);
    }

    if (toTargetPosStrategy) {  // Move drone toward the entity's position
        toTargetPosStrategy->Move(this, dt);
        if(toTargetPosStrategy->IsCompleted()){
          if(nearestEntity)
          {
            nearestEntity->Pay(); // initial payment
          }

            delete toTargetPosStrategy;
            toTargetPosStrategy = NULL;
        }

    } else if (toTargetDesStrategy) {
      // Move drone and entity toward the entity's destination
        toTargetDesStrategy->Move(this, dt);
        toTargetDesStrategy->Collect(nearestEntity); // drone collects payment after it moves
        nearestEntity->SetPosition(this->GetPosition());
        nearestEntity->SetDirection(this->GetDirection());
        if(toTargetDesStrategy->IsCompleted()){ //if bot reaches dest
            std::cout << "You have reached your destination!" <<"\n";
            std::cout << "Money you have left: " << nearestEntity->GetMoney() << "\n";
            std::cout << "Receipt: $" << nearestEntity->GetCostOfTrip() << "\n";

            delete toTargetDesStrategy;
            toTargetDesStrategy = NULL;
            available = true;
            nearestEntity = NULL;
        }
        if(nearestEntity){ // if bot still exist check if bot has enough money
            if (nearestEntity->IsCompleted()){
                //bot has run out of money
                std::cout << "You've run out of money. I can no longer carry you. Bye." << "\n";
                std::cout<< "Money you have left: " << nearestEntity->GetMoney() << "\n";
                std::cout << "Reciept: $" << nearestEntity->GetIntialMoney() << "\n";

                delete toTargetDesStrategy; //drops bot
                toTargetDesStrategy = NULL;
                available = true;
                nearestEntity = NULL;
            }
        }
    }
}

void Drone::Rotate(double angle){
    direction.x = direction.x*std::cos(angle) - direction.z*std::sin(angle);
    direction.z = direction.x*std::sin(angle) + direction.z*std::cos(angle);
}
