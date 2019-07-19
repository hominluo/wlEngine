#include "StateMachineSystem.hpp"
#include "../Component/StateMachine.hpp"
namespace wlEngine {
    SYSTEM_DEFINATION(StateMachineSystem);

    StateMachineSystem::StateMachineSystem() {

    }

    void StateMachineSystem::update() {
        for(auto& sm : StateMachine::collection) {
            StatePriority max_ = 0;
            StateType currStateTemp = sm->currentState;
            for (auto& stateMap : sm->states[currStateTemp]) {
                if(StatePriority priority = stateMap.second() > max_) {
                    sm->currentState = stateMap.first;
                    max_ = priority;
                }
            }
        }
    }
}
