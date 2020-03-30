//
// Created by dmitry on 3/28/20.
//

#include "GameObject.h"

GameObject::GameObject() {
    _move_speed = 100;
}

GameObject::~GameObject() {

}



/* temporary (before player realization) */
void GameObject::Update(float time_elapsed) {

}

void GameObject::Render(const std::shared_ptr<sf::RenderTarget> &target) {
    target->draw(_sprite);
}

void GameObject::Move(const float time_elapsed, const sf::Vector2f &direction) {
    _sprite.move(direction * time_elapsed * _move_speed);
}


void GameObject::InitSprite(std::shared_ptr<sf::Texture> texture) {
    _texture = std::move(texture);
    _sprite.setTexture(*_texture);
}





