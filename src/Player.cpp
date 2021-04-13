#include "Player.h"
#include "TextureManager.h"
#include <algorithm>

Player::Player() : m_currentAngle(0)
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png", 
		"spritesheet");

	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));
	
	// set frame width
	setWidth(53);

	// set frame height
	setHeight(58);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	m_currentDirection = glm::vec2(1.0f, 1.0f);
	m_maxSpeed = 7;
	m_direction = 0;
	force = -18.0f;
	setType(PLAYER);
	setAnimationState(PLAYER_RUN_RIGHT);
	m_buildAnimations();
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the player according to animation state
	switch(m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, m_currentAngle, 255, false);
		break;
	case PLAYER_IDLE_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, m_currentAngle, 255, false, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_RIGHT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
			x, y, 0.25f, m_currentAngle, 255, false);
		break;
	case PLAYER_RUN_LEFT:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("run"),
			x, y, 0.25f, m_currentAngle, 255, false, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_IDLE_PRONE:
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("idle"),
			x, y, 0.12f, m_currentAngle, 255, false);
		setWidth(getWidth()/2);
		break;
	default:
		break;
	}
	
}

void Player::update()
{
	UpdateGravity();
	//PlayerJump();
}

void Player::UpdateGravity()
{
	getRigidBody()->velocity.y += getRigidBody()->acceleration.y + gravity * 0.075;
	getRigidBody()->velocity.y = std::min(std::max(getRigidBody()->velocity.y, force), gravity);
	getTransform()->position.y += getRigidBody()->velocity.y;
	getRigidBody()->acceleration.y = 0.0f;
}

void Player::clean()
{
}

void Player::move()
{
	getRigidBody()->velocity.x = m_currentDirection.x * m_maxSpeed;
	getTransform()->position.x += getRigidBody()->velocity.x;
}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::setCurrentDirection(glm::vec2 newDirection)
{
	m_currentDirection = newDirection;
}

glm::vec2 Player::getCurrentDirection()
{
	return m_currentDirection;
}

void Player::setisGorunded(bool grounded)
{
	isGrounded = grounded;
}

bool Player::getisGrounded()
{
	return isGrounded;
}

void Player::PlayerJump()
{

}

float Player::getAngel()
{
	return m_currentAngle;
}

void Player::setAngle(float x)
{
	m_currentAngle = x;
}

void Player::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-0"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-1"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-2"));
	idleAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-idle-3"));

	setAnimation(idleAnimation);

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-0"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-1"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-2"));
	runAnimation.frames.push_back(getSpriteSheet()->getFrame("megaman-run-3"));

	setAnimation(runAnimation);
}
