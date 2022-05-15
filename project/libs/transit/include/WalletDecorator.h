#ifndef WALLET_DECORATOR_H_
#define WALLET_DECORATOR_H_

#include "util/json.h"
#include "math/vector3.h"
#include <vector>
#include "entity.h"
#include <time.h>

class WalletDecorator: public IEntity {
    public:
        WalletDecorator(IEntity *entity_);
        void Pay(); //called by robot; decrements money
        double GetMoney(); 
        bool GetCelebStatus(); 

        Vector3 GetPosition() const { return entity->GetPosition(); }

        Vector3 GetDirection() const { return entity->GetDirection(); }

        Vector3 GetDestination() const { return entity->GetDestination(); }

        bool GetAvailability() const { return entity->GetAvailability(); }

        JsonObject GetDetails() const { return entity->GetDetails(); }

        float GetSpeed() const { return entity->GetSpeed(); }

        std::string GetStrategyName() const { return entity->GetStrategyName(); }

        void SetAvailability(bool choice) { entity->SetAvailability(choice); }

        void SetPosition(Vector3 pos_) { entity->SetPosition(pos_); }

        void SetDirection(Vector3 dir_) { entity->SetDirection(dir_); }

        void SetDestination(Vector3 des_) { entity->SetDestination(des_); }

        void SetStrategyName(std::string strategyName_) { entity->SetStrategyName(strategyName_); }

        void Rotate(double angle) { entity->Rotate(angle); }

        bool IsCompleted(){ return money <= 0; } // return true when bot has run out of money

        void SetCostOfTrip(float cost, float unit_cost) { costOfTrip = cost; unitCost = unit_cost; }

        double GetCostOfTrip() { return costOfTrip; }

        double GetIntialMoney() { return startMoney; }

    protected:
        double money;
        double startMoney;
        IEntity* entity;
        bool celebStatus;
        double costOfTrip;
        double unitCost;
};

#endif
