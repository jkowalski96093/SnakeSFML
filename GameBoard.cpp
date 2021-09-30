#include "GameBoard.h"

GameBoard::GameBoard()
{
	board.resize(boardHeight);
	for (int i = 0; i < boardHeight; ++i)
		board[i].resize(boardWidth);

	for (int i = 0; i < boardHeight; ++i)
	{
		for (int j = 0; j < boardWidth; ++j)
		{
			board.at(i).at(j).hasFruit = 0;
			board.at(i).at(j).hasSnake = 0;
			board.at(i).at(j).hasSnakeHead = 0;
			board.at(i).at(j).hasWall = 0;
		}
	}
	gameSpeed = 200;
	isPaused = 0;
	isFruit = 0;
	isMenu = 1;
}

GameBoard::GameBoard(const GameBoard * board2)
{
	this->board = board2->board;
	this->boardHeight = board2->boardHeight;
	this->boardWidth = board2->boardWidth;
	this->gameSpeed = board2->gameSpeed;
	this->isFruit = board2->isFruit;
	this->isPaused = board2->isPaused;
}

void GameBoard::setSnake(int x, int y)
{
	board.at(x).at(y).hasSnake = 1;
}

void GameBoard::setSnakePosition(Position p)
{
	setSnake(p.x, p.y);
}

void GameBoard::setSnakeHead(int headX, int headY)
{
	board.at(headX).at(headY).hasSnakeHead = 1;
}

void GameBoard::setSnakeHeadPosition(Position p)
{
	setSnakeHead(p.x, p.y);
}

void GameBoard::deleteSnakeHeadPosition(Position p)
{
	if (board.at(p.x).at(p.y).hasSnakeHead == 1)
		board.at(p.x).at(p.y).hasSnakeHead = 0;
}

void GameBoard::clearAllSnakeFields()
{
	for (int i = 0; i < boardHeight; ++i)
	{
		for (int j = 0; j < boardWidth; ++j)
		{
			board.at(i).at(j).hasSnake = 0;
		}
	}
}

void GameBoard::togglePause()
{
	if (isPaused == 0)
		isPaused = 1;
	else isPaused = 0;
}


void GameBoard::setFruit(int x, int y)
{
	if (onBoard(x, y) == 1) 
		board.at(x).at(y).hasFruit = 1;
	
}


void GameBoard::deleteFruit(int x, int y)
{
	if (board.at(x).at(y).hasFruit == 1)
		board.at(x).at(y).hasFruit = 0;
	isFruit = 0;
}

void GameBoard::deleteFruitPosition(Position p)
{
	deleteFruit(p.x, p.y);
}

void GameBoard::setWall(int x, int y)
{
	board.at(x).at(y).hasWall = 1;
}

void GameBoard::removeWall(int x, int y)
{
	board.at(x).at(y).hasWall = 0;
}

void GameBoard::randomFruit()
{
	srand(time(0));
	while (isFruit == 0)
	{
		int x = rand() % 16;
		int y = rand() % 16;
		if (board.at(x).at(y).hasSnake == 0 && board.at(x).at(y).hasWall == 0 && board.at(x).at(y).hasSnakeHead == 0)
		{
			setFruit(x, y);
			isFruit = 1;
		}
	}
}

void GameBoard::setGameSpeed(int n)
{
	switch (n)
	{
	case 1:
		gameSpeed = 200;
		break;
	case 2:
		gameSpeed = 150;
		break;
	case 3:
		gameSpeed = 100;
		break;
	default:
		if(n>0)
		gameSpeed = n;
		break;
	}
}

void GameBoard::showBoardConsole()
{
	for (int i = 0; i < boardHeight; ++i)
	{
		for (int j = 0; j < boardWidth; ++j)
		{
			if (board.at(j).at(i).hasWall == 1)
				std::cout << "w";
			else if (board.at(j).at(i).hasFruit == 1)
				std::cout << "f";
			else if (board.at(j).at(i).hasSnakeHead == 1)
				std::cout << "h";
			else if (board.at(j).at(i).hasSnake == 1)
				std::cout << "s";
			else std::cout << ".";
		}
		std::cout << std::endl;
	}
}

void GameBoard::toggleMenu()
{
	if (isMenu == 0)
		isMenu = 1;
	else isMenu = 0;
}

int GameBoard::getBoardWidth()
{
	return boardWidth;
}

int GameBoard::getBoardHeight()
{
	return boardHeight;
}

int GameBoard::getGamespeed()
{
	return gameSpeed;
}

bool GameBoard::getIsPaused()
{
	return isPaused;
}

bool GameBoard::getIsMenu()
{
	return isMenu;
}

bool GameBoard::onBoard(int x, int y)
{
	if (0 <= x < boardWidth && 0 <= y < boardHeight)
		return 1;
	else
	return 0;
}


bool GameBoard::hasWall(int x, int y)
{
	while (onBoard(x, y)) {
		if (board.at(x).at(y).hasWall == 1)
			return 1;
		else return 0;
	}
}

bool GameBoard::hasFruit(int x, int y)
{
	while (onBoard(x, y)) {
		if (board.at(x).at(y).hasFruit == 1)
			return 1;
		else return 0;
	}
}

bool GameBoard::hasSnakeHead(int x, int y)
{
	while (onBoard(x, y)) {
		if (board.at(x).at(y).hasSnakeHead == 1)
			return 1;
		else return 0;
	}
}

bool GameBoard::hasSnake(int x, int y)
{
	while (onBoard(x, y)) {
		if (board.at(x).at(y).hasSnake == 1)
			return 1;
		else return 0;
	}
}

bool GameBoard::isHeadWallCollision()
{
	for (int i = 0; i < boardHeight; ++i)
	{
		for (int j = 0; j < boardWidth; ++j)
		{
			if (board.at(i).at(j).hasSnakeHead == 1 && board.at(i).at(j).hasWall == 1)
			{
				return 1;
			}
		}
	}
	return 0;
}

bool GameBoard::isHeadFruitCollision()
{
	for (int i = 0; i < boardHeight; ++i)
	{
		for (int j = 0; j < boardWidth; ++j)
		{
			if (board.at(i).at(j).hasSnakeHead == 1 && board.at(i).at(j).hasFruit == 1)
			{
				return 1;
			}
		}
	}
	return 0;
}

bool GameBoard::isHeadSnakeCollision()
{
	for (int i = 0; i < boardHeight; ++i)
	{
		for (int j = 0; j < boardWidth; ++j)
		{
			if (board.at(i).at(j).hasSnakeHead == 1 && board.at(i).at(j).hasSnake == 1)
			{
				return 1;
			}
		}
	}
	return 0;
}

Position GameBoard::getHeadPosition()
{
	Position p;
	for (int i = 0; i < boardHeight; ++i)
	{
		for (int j = 0; j < boardWidth; ++j)
		{
			if (board.at(i).at(j).hasSnakeHead == 1)
			{
				p.x = i;
				p.y = j;
				return p;
			}
		}
	}
	std::cout << "BLADgetHeadPosition";
	return Position();
}
