#include <SFML/Graphics.hpp>

class Loot{

public:
	Loot();
	~Loot();
	void init(std::string textureName, sf::Vector2f position);
	sf::Sprite getSprite();
	void setRandPos(int x, int y);
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;

};