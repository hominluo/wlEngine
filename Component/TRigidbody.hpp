#pragma once
#include "Component.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <list>
namespace wlEngine {
    class Shape {
    public:
        Shape(const glm::vec2& center);
        glm::vec2 center;
    };

    class CircleShape : public Shape{
    public:
        CircleShape(const glm::vec2& center, const float& radius);
        float radius;
    };

    class PolygonShape : public Shape {
    public:
        PolygonShape(const float& w, const float& h, const glm::vec2& center = {0,0}, const float& angle = 0);
        PolygonShape(const std::vector<glm::vec2>& points, const glm::vec2& center = {0,0});
        std::vector<glm::vec2> points;
    };

    enum class FixtureType {
        Dynamic, Static
    };

    class TRigidbody;
    class Fixture {
    public:
        Fixture(const Shape& shape, const FixtureType& fixtureType);
        Shape shape;
        int16_t mask;
        int16_t catalog;
        bool sensor;
        FixtureType type;
        TRigidbody* body;
    };

    class TRigidbody : public Component {
        COMPONENT_DECLARATION(Component, TRigidbody, 32);
    public:
        TRigidbody(Entity*);
        void addFixture(const Fixture& fixture);
        void removeFixture(Fixture* fixture);
        static std::list<Fixture*> dynamicFixtures;
    private:
        std::list<Fixture> fixtures;
    };
}
