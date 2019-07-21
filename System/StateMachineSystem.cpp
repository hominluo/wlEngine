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
			bool same = true;
            for (auto& stateMap : sm->states[currStateTemp]) {
                if(StatePriority priority = stateMap.second() > max_) {
					const auto& exitFunc = sm->stateActions[currStateTemp][StateActionExitFuncIndex];
					if (exitFunc) exitFunc();
                    sm->currentState = stateMap.first;
                    max_ = priority;
					const auto& enterFunc = sm->stateActions[sm->currentState][StateActionEnterFuncIndex];
					if (enterFunc)enterFunc();
					same = false;
                }
            }
			if (same) {
				const auto& updateFunc = sm->stateActions[currStateTemp][StateActionUpdateFuncIndex];
				if (updateFunc)updateFunc();
			}
			
        }
    }
}
