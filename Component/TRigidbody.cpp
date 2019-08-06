#include "TRigidbody.hpp"
#include <algorithm>
namespace wlEngine {
    /* Shape ***********************************/
    Shape::Shape(const glm::vec2& center) : center(center) {

    }
    /* CircleShape *******************************/
    CircleShape::CircleShape(const glm::vec2& center, const float& radius) : Shape(center), radius(radius){

    }
    /* PolygonShape *******************************/
    PolygonShape::PolygonShape(const float& w, const float& h, const glm::vec2& center, const float& angle) : Shape(center){
        float ww = w / 2;
        float hh = h / 2;
        float s = sin(angle);
        float c = cos(angle);

        auto rotateFunc = [&](glm::vec2 p) {
            // rotate point
            float xnew = p.x * c - p.y * s;
            float ynew = p.x * s + p.y * c;

            // translate point back:
            p.x = xnew + center.x;
            p.y = ynew + center.y;
            points.push_back(p);        
        };
        rotateFunc({ww, hh});
        rotateFunc({ww, -hh});
        rotateFunc({-ww, -hh});
        rotateFunc({-ww, hh});
    }

    PolygonShape::PolygonShape(const std::vector<glm::vec2>& points, const glm::vec2& center) : Shape(center), points(points) {
        for(auto& p : points) {
            this->points.emplace_back(p.x + center.x, p.y + center.y);
        }
    }

    /* Fixture ***********************************/
    Fixture::Fixture(const Shape& shape, const FixtureType& fixtureType) : shape(shape), mask(0), catalog(0), sensor(false), type(fixtureType), body(nullptr) {
        
    }
    
    /* TRigidbody ***********************************/
    COMPONENT_DEFINATION(Component, TRigidbody, 32);
    TRigidbody::TRigidbody(Entity* entity) : Component(entity) {

    }

    void TRigidbody::addFixture(const Fixture& fixture) {
        fixtures.push_back(fixture);
        fixtures.back().body = this;
        if (fixture.type == FixtureType::Dynamic) {
            dynamicFixtures.push_back(&fixtures.back());
        }
    }

    void TRigidbody::removeFixture(Fixture* fixture) {
        fixtures.remove_if([&](const Fixture& t) { return &t == fixture;});
    }

    std::list<Fixture*> TRigidbody::dynamicFixtures = std::list<Fixture*>();
}
