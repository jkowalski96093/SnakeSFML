#pragma once
#include "GameBoard.h"
#include "Map.h"
#include "SFML/Graphics.hpp"
class Menu :
	public GameBoard
{
	sf::RenderWindow &window;
	GameBoard &board;
	sf::Font funnyFont;
	sf::Texture defaultBackground;
	sf::Texture playBackground;
	sf::Texture diffBackground;
	sf::Texture mapBackground;
	sf::Sprite backgroundSprite;
	sf::Vector2f mousePosition;
	sf::Text mapTxt;
	sf::Text diffTxt;
	int mapNo;
	int diffNo;
	void drawStats();
	void playClick();
	void mapClick();
	void difficultyClick();

public:
	Menu(GameBoard &board, sf::RenderWindow &window);
	void displayMenu();
	int getMapNo();
	int getDiffNo();

};

