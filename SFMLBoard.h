#pragma once
#include "GameBoard.h"
#include "Snake.h"
#include "SFML/Graphics.hpp"
class SFMLBoard :
	public GameBoard
{
	std::vector<Position> &v;
	GameBoard &board;
	sf::RenderWindow &window;
	int screenWidth;// = 864
	int screenHeight;// = 864
	int fieldWidth;
	int fieldHeight;
	sf::RectangleShape field;
	sf::Font font;
	sf::Texture wallTexture;
	sf::Texture grassTexture;
	sf::Texture appleTexture;
	sf::Texture headTexture;
	sf::Texture snakeTexture;
	sf::Texture curveTexture;
	sf::Texture tailTexture;
	sf::Texture pauseScreen;
	sf::Sprite wall;
	sf::Sprite grass;
	sf::Sprite apple;
	sf::Sprite head;
	sf::Sprite snake;
	sf::Sprite curve;
	sf::Sprite tail;
	sf::Sprite pauseSprite;
	void rotation(sf::Sprite &s, int heading);
	void drawSprite(sf::Sprite &s, int x, int y);
	void drawEmptyBoard();
	void drawField(int x, int y);
	void drawSnake();

public:
	SFMLBoard();
	SFMLBoard(GameBoard &board, sf::RenderWindow &window,int screenWidth, int screenHeight, std::vector<Position> &v);
	void drawBoard();
	void drawPauseInfo();


};

