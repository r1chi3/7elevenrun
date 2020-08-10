#include <SFML/Graphics.hpp>

class Enemy{

public:
	Enemy();
	~Enemy();
	void init(std::string textureName, sf::Vector2f position);
	sf::Sprite getSprite();
	void setPos(int x, int y);
	void run(int x, int y);
	void update(float dt);
	void setVelocity(float x);
	sf::Vector2f getPos();
	sf::Vector2f getOrigin();
	bool x_enemyMoving = false; // ++x
	bool nx_enemyMoving = false; // --x
	bool y_enemyMoving = false; // ++y
	bool ny_enemyMoving = false; // --y

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	float pv = 300;

};