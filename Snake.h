#pragma once
#include "GameBoard.h"


class Snake :
	public GameBoard
{
	GameBoard &board;
	int length;
	std::vector<Position> v;
	bool isAlive;
	int heading; //1 - up 2 - right 3 - down 4 - left
	int lastHeading;
	bool error1(Position p); //czasami przy szybkim wciscnieciu dwoch klawiszy waz sam w siebie wchodzil
	void moveForward();
	void moveUp();
	void moveRight();
	void moveDown();
	void moveLeft();
	void drawSnake();
	void endMove(Position p);
	void updateVector(Position p);
	void resizeV();

public:
	explicit Snake(GameBoard &board);
	void move(int n);//0-nothing, 1-up 2-right 3-down 4-left
	void setHeading(int n);
	void showVector();
	void reset();
	int getLength();
	int getHeading();
	bool getIsAlive();
	Position getPosition(int n);
	std::vector<Position>& getVector();

};

