//
// Created by dmitry on 3/31/20.
//

#include "GraphicsComponent.h"

GraphicsComponent::GraphicsComponent(sf::Sprite &sprite, sf::Texture &texture_sheet,
                                     const std::map<std::string, Json::Node> &settings) : _sprite(&sprite), _texture_sheet(texture_sheet) {
    LoadFromMap(settings);
}

GraphicsComponent::~GraphicsComponent() {

}

void GraphicsComponent::LoadFromMap(const std::map<std::string, Json::Node> &settings) {
    for (const auto &[animation_key, settings_node] : settings.at("animations").AsMap()) {
        const std::map<std::string, Json::Node> &anim_settings = settings_node.AsMap();
        float anim_time = static_cast<float>(anim_settings.at("animation_time").AsDouble());
        int start_frame_x = static_cast<int>(anim_settings.at("start_frame_x").AsDouble());
        int start_frame_y = static_cast<int>(anim_settings.at("start_frame_y").AsDouble());
        int end_frame_x = static_cast<int>(anim_settings.at("end_frame_x").AsDouble());
        int end_frame_y = static_cast<int>(anim_settings.at("end_frame_y").AsDouble());
        int rect_params_x = static_cast<int>(anim_settings.at("rect_params_x").AsDouble());
        int rect_params_y = static_cast<int>(anim_settings.at("rect_params_y").AsDouble());
        AddAnimation(animation_key, anim_time, start_frame_x, start_frame_y, end_frame_x, end_frame_y,
                     sf::Vector2i(rect_params_x, rect_params_y));
    }
}


bool GraphicsComponent::IsDone(const std::string &animation_key) const {
    return _animations.at(animation_key)->IsDone();
}

void
GraphicsComponent::AddAnimation(const std::string &animation_key, float anim_time, int start_frame_x, int start_frame_y,
                                int frames_x, int frames_y, sf::Vector2i rect_params) {
    _animations[animation_key] = std::make_unique<Animation>(_sprite, _texture_sheet, anim_time, start_frame_x,
                                                             start_frame_y, frames_x, frames_y, rect_params);
}

bool GraphicsComponent::Play(const std::string &animation_key, const float time_elapsed, const float speed_modifier,
                             const bool priority) {
    if (_prior_animation != nullptr) {
        if (_animations.at(animation_key).get() == _prior_animation) {
            CheckLastAnimation(animation_key);
            if (_animations[animation_key]->Play(time_elapsed, speed_modifier)) {
                _prior_animation = nullptr;
            }
        }
    } else {
        if (priority) {
            _prior_animation = _animations.at(animation_key).get();
        }
        CheckLastAnimation(animation_key);
        _animations[animation_key]->Play(time_elapsed, speed_modifier);
    }
    return _animations[animation_key]->IsDone();
}

void GraphicsComponent::CheckLastAnimation(const std::string &animation_key) {
    if (_last_animation != _animations.at(animation_key).get()) {
        if (_last_animation == nullptr) {
            _last_animation = _animations.at(animation_key).get();
        } else {
            //ВНИМАНИЕ НА ПОРЯДОК
            _last_animation->Reset();
            _last_animation = _animations.at(animation_key).get();
        }
    }
}

void GraphicsComponent::UpdateCopy(sf::Sprite &sprite) {
    _sprite = &sprite;
    for (auto& [key, animation] : _animations) {
        animation->_sprite = &sprite;
    }
}

GraphicsComponent::GraphicsComponent(const GraphicsComponent& other) : _texture_sheet(other._texture_sheet), _sprite(other._sprite) {
    _last_animation = nullptr;
    _prior_animation = nullptr;
    for (const auto& [key, animation] : other._animations) {
        _animations[key] = std::make_unique<Animation>(*animation);
    }
}


GraphicsComponent::Animation::Animation(sf::Sprite *sprite, sf::Texture &texture_sheet, float anim_time,
                                        int start_frame_x, int start_frame_y,
                                        int end_frame_x, int end_frame_y, sf::Vector2i rect_params) : _sprite(sprite),
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
    _end_rect = sf::IntRect(end_frame_x * rect_params.x, end_frame_y * rect_params.y, rect_params.x, rect_params.y);
    _sprite->setTexture(_texture_sheet, true);
    _sprite->setTextureRect(_start_rect);
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
    _sprite->setTextureRect(_current_rect);
}

void GraphicsComponent::Animation::Reset() {
    _time = _time_to_animate;
    _current_rect = _start_rect;
}


bool GraphicsComponent::Animation::IsDone() const {
    return _is_done;
}



