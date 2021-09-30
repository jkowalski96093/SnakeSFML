#pragma once
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
struct Position
{
	int x;
	int y;
	int heading = 0;
};


struct Field
{
	bool hasSnakeHead;
	bool hasSnake;
	bool hasWall;
	bool hasFruit;
};

class GameBoard
{
	int boardWidth=16;
	int boardHeight=16;
	std::vector<std::vector<Field>> board;
	int gameSpeed; //Sleep(gamespeed)
	bool isPaused;
	bool isFruit;
	bool isMenu; //default 1

public:
	GameBoard();
	GameBoard(const GameBoard *board2);
	void setSnake(int x, int y);
	void setSnakePosition(Position p);
	void setSnakeHead(int headX, int headY); //domyslnie(6,8) 
	void setSnakeHeadPosition(Position p);
	void deleteSnakeHeadPosition(Position p);
	void clearAllSnakeFields();
	void togglePause();
	void setFruit(int x, int y);
	void deleteFruit(int x, int y);
	void deleteFruitPosition(Position p);
	void setWall(int x, int y);
	void removeWall(int x, int y);
	void randomFruit();
	void setGameSpeed(int n); // 0-value, 1- EASY(300) 2-MEDIUM(200) 3-HARD(100)
	void showBoardConsole();
	void toggleMenu();
	int getBoardWidth();
	int getBoardHeight();
	int getGamespeed();
	bool getIsPaused();
	bool getIsMenu();
	bool onBoard(int x, int y);
	bool hasWall(int x, int y);
	bool hasFruit(int x, int y);
	bool hasSnakeHead(int x, int y);
	bool hasSnake(int x, int y);
	bool isHeadWallCollision();
	bool isHeadFruitCollision(); //po tym snake length++
	bool isHeadSnakeCollision();
	Position getHeadPosition();
};

