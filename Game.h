#pragma once
#include "SFMLBoard.h"
#include "Snake.h"
#include "Map.h"
#include <chrono>
#include <thread>
#include <fstream>
class Game :
	public SFMLBoard
{
	int mapNo;
	int diffNo;
	GameBoard &board;
	SFMLBoard &sfmlboard;
	Snake &snake;
	sf::RenderWindow &window;
	sf::Texture deathScreen;
	sf::Texture deathHighScoreScreen;
	sf::Texture scoreBoardScreen;
	sf::Sprite death;
	sf::Sprite deathHighScore;
	sf::Sprite scoreBoardSprite;
	sf::Font deathFont;
	sf::Font funnyFont;
	sf::Text txt;
	int highScores[5][3];
	int score;
	bool isHighScore;
	void readScoreBoard();
	void writeScoreBoard();
	void drawStats();
	void GameOver();
	void Scoreboard();
public:
	Game(GameBoard &board, SFMLBoard &sfmlboard, Snake &snake, sf::RenderWindow &window);
	void Play();
	void insertMapNo(int n);
	void insertDiffNo(int n);

};

