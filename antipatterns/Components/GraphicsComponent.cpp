//
// Created by dmitry on 3/31/20.
//

#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(sf::Sprite &sprite, sf::Texture &texture_sheet) : _sprite(sprite),
                                                                                       _texture_sheet(texture_sheet) {

}

GraphicsComponent::~GraphicsComponent() {

}

bool GraphicsComponent::IsDone(const std::string &animation_key) {
    return _animations.at(animation_key)->IsDone();
}

void
GraphicsComponent::AddAnimation(const std::string &animation_key, float anim_time, int start_frame_x, int start_frame_y,
                                int frames_x, int frames_y, sf::Vector2i rect_params) {
    _animations[animation_key] = std::make_shared<Animation>(_sprite, _texture_sheet, anim_time, start_frame_x,
                                                             start_frame_y, frames_x, frames_y, rect_params);
}

bool GraphicsComponent::Play(const std::string &animation_key, const float time_elapsed, const float speed_modifier,
                             const bool priority) {
    if (_prior_animation != nullptr) {
        if (_animations.at(animation_key) == _prior_animation) {
            CheckLastAnimation(animation_key);
            if (_animations[animation_key]->Play(time_elapsed, speed_modifier)) {
                _prior_animation = nullptr;
            }
        }
    } else {
        if (priority) {
            _prior_animation = _animations.at(animation_key);
        }
        CheckLastAnimation(animation_key);
        _animations[animation_key]->Play(time_elapsed, speed_modifier);
    }
    return _animations[animation_key]->IsDone();
}

void GraphicsComponent::CheckLastAnimation(const std::string &animation_key) {
    if (_last_animation != _animations.at(animation_key)) {
        if (_last_animation == nullptr) {
            _last_animation = _animations.at(animation_key);
        } else {
            _last_animation->Reset();
            _last_animation = _animations.at(animation_key);
        }
    }
}

GraphicsComponent::Animation::Animation(sf::Sprite &sprite, sf::Texture &texture_sheet, float anim_time,
                                        int start_frame_x, int start_frame_y,
                                        int frames_x, int frames_y, sf::Vector2i rect_params) : _sprite(sprite),
                                                                                                _texture_sheet(
                                                                                                        texture_sheet),
                                                                                                _time_to_animate(
                                                                                                        anim_time),
                                                                                                _rect_params(
                                                                                                        rect_params),
                                                                                                _is_done(false) {
    _start_rect = sf::IntRect(start_frame_x * rect_params.x, start_frame_y * rect_params.y, rect_params.x,
                              rect_params.y);
    _current_rect = _start_rect;
    _end_rect = sf::IntRect(frames_x * rect_params.x, frames_y * rect_params.y, rect_params.x, rect_params.y);
    _sprite.setTexture(_texture_sheet, true);
    _sprite.setTextureRect(_start_rect);
}

bool GraphicsComponent::Animation::Play(const float time_elapsed, const float speed_modifier) {
    _time += TIME_NORMALIZE * time_elapsed * speed_modifier;
    _is_done = false;
    if (_time >= _time_to_animate) {
        _time = 0;
        Animate();
    }
    return _is_done;
}

void GraphicsComponent::Animation::Animate() {
    if (_current_rect != _end_rect) {
        _current_rect.left += _rect_params.x;
    } else {
        _current_rect.left = _start_rect.left;
        _is_done = true;
    }
    _sprite.setTextureRect(_current_rect);
}

void GraphicsComponent::Animation::Reset() {
    _time = _time_to_animate;
    _current_rect = _start_rect;
}


bool GraphicsComponent::Animation::IsDone() {
    return _is_done;
}



