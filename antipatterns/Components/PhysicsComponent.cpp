//
// Created by dmitry on 3/31/20.
//

#include "PhysicsComponent.h"

PossibleDirections::PossibleDirections(bool left, bool right, bool up,
                                       bool down)
    : left(left), right(right), up(up), down(down) {}

PossibleDirections
PossibleDirections::operator&&(const PossibleDirections &other) {
  return {left && other.left, right && other.right, up && other.up,
          down && other.down};
}

PhysicsComponent::PhysicsComponent(
    sf::Sprite &sprite, const std::map<std::string, Json::Node> &settings)
    : sprite_(&sprite) {
  LoadFromMap(settings);
}

void PhysicsComponent::LoadFromMap(
    const std::map<std::string, Json::Node> &settings) {
  max_velocity_ = static_cast<float>(settings.at("max_velocity").AsDouble());
  acceleration_ = static_cast<float>(settings.at("acceleration").AsDouble());
  deceleration_ = static_cast<float>(settings.at("deceleration").AsDouble());
}

PhysicsComponent::~PhysicsComponent() {}

/* getters */
float PhysicsComponent::GetMaxVelocity() const { return max_velocity_; }

sf::Vector2f PhysicsComponent::GetVelocity() const { return velocity_; }

MovementState PhysicsComponent::GetMovementState() const {
  if (velocity_.x == 0 && velocity_.y == 0) {
    return MovementState::IDLE;
  }
  if (velocity_.x < 0 && std::abs(velocity_.x) >= std::abs(velocity_.y)) {
    return MovementState::MOVING_LEFT;
  }
  if (velocity_.x > 0 && std::abs(velocity_.x) >= std::abs(velocity_.y)) {
    return MovementState::MOVING_RIGHT;
  }
  if (velocity_.y < 0 && std::abs(velocity_.x) < std::abs(velocity_.y)) {
    return MovementState::MOVING_UP;
  }
  if (velocity_.y > 0 && std::abs(velocity_.x) < std::abs(velocity_.y)) {
    return MovementState::MOVING_DOWN;
  }
  throw std::runtime_error("CASE NOT HANDLED");
}

MovementState PhysicsComponent::GetLastMoveDirection() const {
  return last_direction_;
}

/* modifiers */
void PhysicsComponent::Stop() { velocity_.x = velocity_.y = 0; }

void PhysicsComponent::SetPossibleMoveDirections(
    PossibleDirections directions) {
  able_dir = directions;
}

void PhysicsComponent::UpdateSpeedMultiplier(float multiplier) {
  speed_multiplier_ = multiplier;
}

void PhysicsComponent::StopAxisMoveX() { velocity_.x = 0; }

void PhysicsComponent::StopAxisMoveY() { velocity_.y = 0; }

/* functions */
void PhysicsComponent::Accelerate(const float time_elapsed,
                                  const sf::Vector2f &direction) {
  if ((direction.x < 0 && able_dir.left) ||
      (direction.x > 0 && able_dir.right)) {
    velocity_.x += acceleration_ * direction.x * time_elapsed;
  }
  if ((direction.y < 0 && able_dir.up) || (direction.y > 0 && able_dir.down)) {
    velocity_.y += acceleration_ * direction.y * time_elapsed;
  }
}

void PhysicsComponent::Update(const float time_elapsed) {
  /* написать здесь нормальную проверку на текущую скорость */
  float abs_v = sqrtf(velocity_.x * velocity_.x + velocity_.y * velocity_.y);
  float cos_a = velocity_.x / abs_v;
  float sin_a = velocity_.y / abs_v;
  if (abs_v > max_velocity_) {
    velocity_.x = max_velocity_ * cos_a;
    velocity_.y = max_velocity_ * sin_a;
  }
  if (velocity_.x != 0) {
    velocity_.x -= deceleration_ * cos_a * time_elapsed;
    if (velocity_.x * cos_a <= 0) {
      last_direction_ = cos_a < 0 ? MOVING_LEFT : MOVING_RIGHT;
      velocity_.x = 0;
    }
  }
  if (velocity_.y != 0) {
    velocity_.y -= deceleration_ * sin_a * time_elapsed;
    if (velocity_.y * sin_a <= 0) {
      last_direction_ = sin_a < 0 ? MOVING_UP : MOVING_DOWN;
      velocity_.y = 0;
    }
  }
  sprite_->move(velocity_ * speed_multiplier_ * time_elapsed);
}

void PhysicsComponent::UpdateCopy(sf::Sprite &sprite) { sprite_ = &sprite; }
