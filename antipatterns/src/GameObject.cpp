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

/* temporary (before player realization) */
void GameObject::Update(float time_elapsed) {

}


void GameObject::Render(const std::shared_ptr<sf::RenderTarget> &target) {
    target->draw(_shape);
}





