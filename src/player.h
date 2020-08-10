#include <SFML/Graphics.hpp>

class Player{

public:
	Player();
	~Player();
	void init(std::string textureName, sf::Vector2f position);
	void update(float dt);
	sf::Sprite getSprite();
	void setVelocity(float x);
	bool x_playerMoving = false; // ++x
	bool nx_playerMoving = false; // --x
	bool y_playerMoving = false; // ++y
	bool ny_playerMoving = false; // --y

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
	float pv = 500;

};