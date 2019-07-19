#pragma once
#include "Component.hpp"
#include <map>
#include <string>
#include <functional>
namespace wlEngine {
    using StateType = std::string;
    using StatePriority = uint8_t;
    using StateConditionType = std::function<StatePriority(void)>;
    using StateMachineType = std::map<StateType, std::map<StateType, StateConditionType>>;

    class StateMachine : public Component {
        COMPONENT_DECLARATION(Component, StateMachine, 8);
    public:
        StateMachine(GameObject*, const StateType& initialState);
        /**
         * @brief set the states from state to state with their condition
         *
         * @param from
         * @param to
         * @param condition
         */
        void addState(const StateType& from, const StateType& to, StateConditionType condition);
        const StateType& getCurrentState();
    private:
        StateType currentState;
        StateMachineType states;   

        friend class StateMachineSystem;
    };
}
