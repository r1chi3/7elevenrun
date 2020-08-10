#include <player.h>

Player::Player(){}
Player::~Player(){}

void Player::init(std::string textureName, sf::Vector2f position)
{
	m_position = position;
	// Load a Texture
	m_texture.loadFromFile(textureName.c_str());
	// Create Sprite and Attach a Texture
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texture.getSize().x/2, m_texture.getSize().y/2);
}


void Player::update(float dt){

	if (x_playerMoving)
		m_sprite.move(pv * dt, 0);
	if (nx_playerMoving)
		m_sprite.move(-pv * dt, 0);
	if (y_playerMoving)
		m_sprite.move(0, pv * dt);
	if (ny_playerMoving)
		m_sprite.move(0, -pv * dt);
}

sf::Sprite Player::getSprite(){
	return m_sprite;
}

void Player::setVelocity(float x){
	pv = x;
}