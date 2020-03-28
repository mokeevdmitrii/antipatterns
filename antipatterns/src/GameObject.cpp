//
// Created by dmitry on 3/28/20.
//

#include "GameObject.h"

GameObject::GameObject() {
    _shape.setSize(sf::Vector2f(50.f, 50.f));
    _shape.setFillColor(sf::Color::White);
    _move_speed = 100;
}

GameObject::~GameObject() {

}

void GameObject::Move(const float time_elapsed, const sf::Vector2f &direction) {
    _shape.move(direction * time_elapsed * _move_speed);
}

void GameObject::Render(const std::shared_ptr<sf::RenderTarget> &target) {
    target->draw(_shape);
}

void GameObject::Update(float time_elapsed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        Move(time_elapsed, sf::Vector2f(-1.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        Move(time_elapsed, sf::Vector2f(1.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        Move(time_elapsed, sf::Vector2f(0.f, 1.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        Move(time_elapsed, sf::Vector2f(0.f, -1.f));
    }
}




