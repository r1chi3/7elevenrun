#include "Main.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <player.h>
#include <Enemy.h>
#include <loot.h>
#include <sound.h>


sf::Vector2f viewSize(1024,768);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "7elevenRun",sf::Style::Default);

//declarations
Player player;

	//background
	sf::Texture bgTexture;
	sf::Sprite bgSprite;

	//sounds
	sf::Music gameOverSound;
	sf::Music quakeSounds;
	sf::Music keygenMusic;
	const float SOUND_VOLUME = 40.0;

	//loot spawns
	Loot loot1;
	Loot loot2;

	//enemy
	Enemy enemy1;
	Enemy enemy2;

	//font and score handling
	sf::Font scoreBoardFont;
	sf::Text scoreBoardText;
	sf::Font headingFont;
	sf::Text headingText;
	int SCORE = 0;
	bool GAMEOVER = false;
	int DIFFICULTY = 0;

//returns random num from 0 to x
std::random_device rd;
int random(int x){
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0,x);
	int random_int = uni(rng);
	return random_int;
}

//returns string from sound array in sound.h
std::string killStreak(){
return killSounds[random(killSounds->size())];
}


void init(){

	player.init("content/richie.png", sf::Vector2f(viewSize.x/2, viewSize.y/2));
	loot1.init("content/smokes.jpg", sf::Vector2f(random(viewSize.x), random(viewSize.y)));
	loot2.init("content/lotto.jpg", sf::Vector2f(random(viewSize.x), random(viewSize.y)));

	enemy1.init("content/enemy.png", sf::Vector2f(viewSize.x + 100 , random(viewSize.y)));
	enemy2.init("content/enemy.png", sf::Vector2f(random(viewSize.x), viewSize.y + 100));


	bgTexture.loadFromFile("content/back.jpg");
	bgSprite.setTexture(bgTexture);

	headingFont.loadFromFile("content/snes.ttf");
	headingText.setFont(headingFont);
 	headingText.setString("7 e l e v e n  R u n");
	headingText.setCharacterSize(84);
 	headingText.setFillColor(sf::Color::Green);
	sf::FloatRect headingBounds = headingText.getLocalBounds();
 	headingText.setOrigin(headingBounds.width/2,headingBounds.height / 2);
 	headingText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));

	scoreBoardFont.loadFromFile("content/snes.ttf");
	scoreBoardText.setFont(scoreBoardFont);
	scoreBoardText.setCharacterSize(84);
 	scoreBoardText.setFillColor(sf::Color::Green);
	sf::FloatRect scoreHeadingBounds = scoreBoardText.getLocalBounds();
 	scoreBoardText.setOrigin(scoreHeadingBounds.width/2,scoreHeadingBounds.height / 2);
 	scoreBoardText.setPosition(sf::Vector2f(viewSize.x * 0.10f, viewSize.y * 0.50f));

	keygenMusic.setVolume(SOUND_VOLUME);
	keygenMusic.openFromFile("content/keygen.ogg");
	keygenMusic.play();
	keygenMusic.setLoop(true);


	quakeSounds.setVolume(SOUND_VOLUME);
	quakeSounds.openFromFile("content/sounds/prepare.ogg");
	quakeSounds.play();

}
void draw(){
	window.draw(bgSprite);
	window.draw(loot1.getSprite());
	window.draw(loot2.getSprite());

	window.draw(headingText);
	window.draw(scoreBoardText);
	window.draw(player.getSprite());
	window.draw(enemy1.getSprite());
	window.draw(enemy2.getSprite());
}

void updateScore(){
	std::string scoreFromInt = std::to_string(SCORE);
	scoreBoardText.setString(scoreFromInt);
}

void restartGame(){
	SCORE = 0;
	DIFFICULTY = 0;
	enemy1.setVelocity(300);
	enemy2.setVelocity(300);
	updateScore();
	init();
	GAMEOVER = false;
}

void updateInput(){
sf::Event event;
while (window.pollEvent(event))
{
	if (event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Right:
				player.x_playerMoving = true;
				break;
			case sf::Keyboard::Left:
				player.nx_playerMoving = true;
				break;
			case sf::Keyboard::Down:
				player.y_playerMoving = true;
				break;
			case sf::Keyboard::Up:
				player.ny_playerMoving = true;
				break;
			default:
				break;
			}

		switch(event.key.code)
		{
			case sf::Keyboard::D:
				player.x_playerMoving = true;
				break;
			case sf::Keyboard::A:
				player.nx_playerMoving = true;
				break;
			case sf::Keyboard::S:
				player.y_playerMoving = true;
				break;
			case sf::Keyboard::W:
				player.ny_playerMoving = true;
				break;
			default:
				break;
			}
	}

	if (event.type == sf::Event::KeyReleased)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Right:
				player.x_playerMoving = false;
				break;
			case sf::Keyboard::Left:
				player.nx_playerMoving = false;
				break;
			case sf::Keyboard::Down:
				player.y_playerMoving = false;
				break;
			case sf::Keyboard::Up:
				player.ny_playerMoving = false;
				break;
			default:
				break;
		}

		switch(event.key.code)
		{
			case sf::Keyboard::D:
				player.x_playerMoving = false;
				break;
			case sf::Keyboard::A:
				player.nx_playerMoving = false;
				break;
			case sf::Keyboard::S:
				player.y_playerMoving = false;
				break;
			case sf::Keyboard::W:
				player.ny_playerMoving = false;
				break;
			default:
				break;
		}
	}
	if (event.key.code == sf::Keyboard::Escape ||
		event.type == sf::Event::Closed)
	{
		window.close();
	}

	if (GAMEOVER)
	{
		if (event.key.code == sf::Keyboard::Enter)
		{
			restartGame();
		}
	}
	if (event.key.code == 0 )
	{
		continue;
	}

}


}

bool checkCollision(sf::Sprite player, sf::Sprite sprite){


	sf::FloatRect shape_x = player.getGlobalBounds();
	sf::FloatRect shape_y = sprite.getGlobalBounds();

	if (shape_x.intersects(shape_y))
	{
		return true;
	}

	else
	{
		return false;
	}

}



void onLootCollision(){

	loot1.setRandPos(random(viewSize.x ),random(viewSize.y ));
	SCORE += 1;
	updateScore();
}

void onLootCollision2(){

	loot2.setRandPos(random(viewSize.x ),random(viewSize.y ));
	SCORE += 2;
	updateScore();
}



void gameOver() {
	headingText.setString("G A M E  O V E R");
	headingText.setFillColor(sf::Color::Red);
	headingText.setCharacterSize(200);
	sf::FloatRect headingBounds = headingText.getLocalBounds();
 	headingText.setOrigin(headingBounds.width / 2,headingBounds.height / 2);
	headingText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.5f));

	gameOverSound.setVolume(SOUND_VOLUME);
	gameOverSound.openFromFile("content/hum.ogg");
	gameOverSound.play();

	keygenMusic.stop();

	GAMEOVER = true;



}


void update(float dt){ //delta time

	player.update(dt);

	if(checkCollision(player.getSprite(), loot1.getSprite()) == true){
		onLootCollision();
	}
	if(checkCollision(player.getSprite(), loot2.getSprite()) == true){
		onLootCollision2();
	}
	if(checkCollision(player.getSprite(), enemy1.getSprite()) == true
	|| checkCollision(player.getSprite(), enemy2.getSprite()) == true){
		gameOver();
	}
}

void updateEnemy(float dt){
	enemy1.update(dt);

	if (DIFFICULTY >= 1){
	enemy2.update(dt);
	}


	sf::Vector2f enemyPos = enemy1.getPos();
	sf::Vector2f enemyOrigin2f = enemy1.getOrigin();

	sf::Vector2f enemy2Pos = enemy2.getPos();
	sf::Vector2f enemy2_Origin2f = enemy2.getOrigin();


	if (enemyPos.x > -enemyOrigin2f.x * 9){

		enemy1.nx_enemyMoving = true;
	}

	if (enemyPos.x < -enemyOrigin2f.x * 9){

		enemy1.nx_enemyMoving = false;
		enemy1.setPos(viewSize.x + enemyOrigin2f.x * 2 , random(viewSize.y) );
	}

	if (enemy2Pos.y > -enemy2_Origin2f.y * 9){

		enemy2.ny_enemyMoving = true;
	}

	if (enemy2Pos.y < -enemy2_Origin2f.y * 9){

		enemy2.ny_enemyMoving = false;
		enemy2.setPos(random(viewSize.x) , viewSize.y + enemyOrigin2f.y * 2);
	}


}

void updateSound(){

	if( (SCORE % 10 == 0) ){
	quakeSounds.setVolume(SOUND_VOLUME);
	std::string rSound = "content/sounds/" + killStreak();
	quakeSounds.openFromFile(rSound);
	quakeSounds.play();
	}

	if( (SCORE == 1) || (SCORE == 2) ){
	quakeSounds.setVolume(SOUND_VOLUME);
	quakeSounds.openFromFile("content/sounds/firstblood.ogg");
	quakeSounds.play();
	}
}

int checkDifficulty(){

	if ((SCORE >= 25 && SCORE < 50)){
		DIFFICULTY = 0;
		return 0;
	}
	if ((SCORE >= 50 && SCORE < 75)){
		DIFFICULTY = 1;
		return 1;
	}
	if ((SCORE >= 75 && SCORE < 100)){
		DIFFICULTY = 2;
		return 2;
	}
	if ((SCORE >= 100 && SCORE < 125)){
		DIFFICULTY = 3;
		return 3;
	}
	if ((SCORE >= 125 && SCORE < 150)){
		DIFFICULTY = 4;
		return 4;
	}

}


void updateDifficulty(){

	switch (checkDifficulty())
	{
	case 0:
		enemy1.setVelocity(400.0);
		enemy2.setVelocity(400.0);
		break;
	case 1:
		enemy1.setVelocity(500.0);
		enemy2.setVelocity(500.0);
		break;
	case 2:
		enemy1.setVelocity(600.0);
		enemy2.setVelocity(600.0);
		break;
	case 3:
		enemy1.setVelocity(700.0);
		enemy2.setVelocity(700.0);
		player.setVelocity(650.0);
		break;
	case 4:
		enemy1.setVelocity(800.0);
		enemy2.setVelocity(800.0);
		player.setVelocity(750.0);
		break;

	default:
		break;
	}

}


int main()
{
	sf::Clock clock;
	init();

	//start game loop
	while (window.isOpen())
	{

		updateInput();

		sf::Time dt = clock.restart();

		if (!GAMEOVER)
		{
			update(dt.asSeconds());
			updateEnemy(dt.asSeconds());
			updateDifficulty();
			checkDifficulty();

		if((!SCORE == 0))
		{
			updateSound();
		}}

		//Start of frame
		window.clear();

		draw();

		//End of frame
		window.display();

	}
	return 0;
}
