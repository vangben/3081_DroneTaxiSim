#include "WalletDecorator.h"

WalletDecorator::WalletDecorator(IEntity *entity_){
    entity = entity_;
    srand(time(NULL));
    money = rand() % 100 + 1; // starting drone wallet balance: 1-100 dollars randomly determined
    startMoney = money;
    celebStatus = rand() % 2;
}
void WalletDecorator::Pay(){        // called by robot, takes in drone to notify drone to pay or not
    money = money - unitCost;
} 
double WalletDecorator::GetMoney(){
    return money;
}
bool WalletDecorator::GetCelebStatus(){
    return celebStatus;
}
