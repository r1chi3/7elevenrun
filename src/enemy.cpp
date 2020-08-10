#include <Enemy.h>

Enemy::Enemy(){}
Enemy::~Enemy(){}

void Enemy::init(std::string textureName, sf::Vector2f position)
{
	m_position = position;
	m_texture.loadFromFile(textureName.c_str());
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texture.getSize().x/2, m_texture.getSize().y/2);
}

sf::Sprite Enemy::getSprite(){
	return m_sprite;
}

sf::Vector2f Enemy::getPos(){
	sf::Vector2f position = m_sprite.getPosition();
	return position;
}

sf::Vector2f Enemy::getOrigin(){
	sf::Vector2f origin = m_sprite.getOrigin();
	return origin;
}

void Enemy::setPos(int x,int y){
	m_sprite.setPosition(x, y);
}

void Enemy::update(float dt){


	if (x_enemyMoving)
		m_sprite.move(pv * dt, 0);
	if (nx_enemyMoving)
		m_sprite.move(-pv * dt, 0);
	if (y_enemyMoving)
		m_sprite.move(0, pv * dt);
	if (ny_enemyMoving)
		m_sprite.move(0, -pv * dt);
}

void Enemy::setVelocity(float x){
	pv = x;
}