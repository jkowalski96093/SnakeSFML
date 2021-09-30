#include "Snake.h"

bool Snake::error1(Position p)
{
	if (v.size() < 2)
		return 0;
	else if (p.x == v.at(1).x && p.y == v.at(1).y)
		return 1;
	else if (v.size() < 3)
		return 0;
	else if (p.x == v.at(2).x && p.y == v.at(2).y)
		return 1;
	else return 0;
}

Snake::Snake(GameBoard & board):board(board)
{
	length = 2;
	resizeV();
	v.at(0) = board.getHeadPosition();
	isAlive = 1;
	heading = 1;
	lastHeading = 1;
	v.at(0).heading = 1;

}

void Snake::resizeV()
{
	v.resize(length);
}

void Snake::move(int n)
{
	if (isAlive == 1) {
		switch (n) {
		case 0:moveForward();
			break;
		case 1:moveUp();
			break;
		case 2:moveRight();
			break;
		case 3:moveDown();
			break;
		case 4:moveLeft();
			break;
		default: std::cout << "BLADmove";
		}
	}
}

void Snake::setHeading(int n)
{
	//switch zapobiegajacy zawracaniu ktore powoduje natychmiastowa przegrana
	switch (n) {
	case 1: if (heading != 3)
		lastHeading = heading;
		heading = n;
		break;
	case 2: if (heading != 4)
		lastHeading = heading;
		heading = n;
		break;
	case 3: if (heading != 1)
		lastHeading = heading;
		heading = n;
		break;
	case 4: if (heading != 2)
		lastHeading = heading;
		heading = n;
		break;
	}
}

void Snake::moveForward()
{
	switch (heading) {

	case 1:moveUp();
		break;
	case 2:moveRight();
		break;
	case 3:moveDown();
		break;
	case 4:moveLeft();
		break;
	default: std::cout << "BLADmoveForward";
	}
}

void Snake::moveUp()
{

	Position p0 = board.getHeadPosition();
	Position p1;
	p1.x = p0.x;
	if(p0.y == 0)
		p1.y = 15;
	else p1.y = p0.y - 1;
	if (error1(p1) == 1)
	{
		heading = lastHeading;
		return;
	}
	p1.heading = 1;
	board.deleteSnakeHeadPosition(p0);
	endMove(p1);
}

void Snake::moveRight()
{
	Position p0 = board.getHeadPosition();
	Position p1;
	if (p0.x == 15)
		p1.x = 0;
	else p1.x = p0.x + 1;
	p1.y = p0.y;
	if (error1(p1) == 1)
	{
		heading = lastHeading;
		return;
	}
	p1.heading = 2;
	board.deleteSnakeHeadPosition(p0);
	endMove(p1);
}

void Snake::moveDown()
{
	Position p0 = board.getHeadPosition();
	Position p1;
	p1.x = p0.x;
	if (p0.y == 15)
		p1.y = 0;
	else p1.y = p0.y + 1;
	if (error1(p1) == 1)
	{
		heading = lastHeading;
		return;
	}
	p1.heading = 3;
	board.deleteSnakeHeadPosition(p0);
	endMove(p1);

}

void Snake::moveLeft()
{
	Position p0 = board.getHeadPosition();
	Position p1;
	if (p0.x == 0)
		p1.x = 15;
	else p1.x = p0.x - 1;
	p1.y = p0.y;
	if (error1(p1) == 1)
	{
		heading = lastHeading;
		return;
	}
	p1.heading = 4;
	board.deleteSnakeHeadPosition(p0);
	endMove(p1);
}

void Snake::updateVector(Position p)
{
	v.insert(v.begin(), p);
	v.resize(length);
}

void Snake::showVector()
{
	for (int i = 0; i < v.size(); i++)
	{
		std::cout << "[" << v.at(i).x << "," << v.at(i).y << "] ";
	}
}

void Snake::drawSnake()
{
	board.clearAllSnakeFields();
	if (length > 1)
		for (int i = 1; i < v.size(); i++)
			board.setSnakePosition(v.at(i));
}

void Snake::endMove(Position p)
{
	board.setSnakeHeadPosition(p);
	if (board.isHeadFruitCollision() == 1)
	{
		length++;
		//board.showBoardConsole();
		board.deleteFruitPosition(p);
		board.randomFruit();
	}
	updateVector(p);
	drawSnake();
	if (board.isHeadWallCollision() == 1 || board.isHeadSnakeCollision() == 1)
	{
		//board.showBoardConsole();
		isAlive = 0;
	}
}

void Snake::reset()
{
	length = 2;
	resizeV();
	board.deleteSnakeHeadPosition(board.getHeadPosition());
	board.setSnakeHead(6, 8);
	v.at(0) = board.getHeadPosition();
	isAlive = 1;
	heading = 1;
	lastHeading = 1;
}

int Snake::getLength()
{
	return length;
}

int Snake::getHeading()
{
	return heading;
}

bool Snake::getIsAlive()
{
	return isAlive;
}

Position Snake::getPosition(int n)
{
	if(n<length)
		return v.at(n);
	else 
		return Position();
}

std::vector<Position>& Snake::getVector()
{
	return v;
}

