#include "StateMachine.hpp"
namespace wlEngine {
	COMPONENT_DEFINATION(Component, StateMachine,8);
    StateMachine::StateMachine(GameObject* go, const StateType& initialState) : Component(go), currentState(initialState){

    }

    void StateMachine::addState(const StateType& from, const StateType& to, StateConditionType condition) {
        states[from][to] = condition;
    }

    const StateType& StateMachine::getCurrentState() {
        return currentState;
    }
}
