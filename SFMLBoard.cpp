#include "SFMLBoard.h"

SFMLBoard::SFMLBoard():board(board),window(window),v(v)
{
}

SFMLBoard::SFMLBoard(GameBoard & board, sf::RenderWindow & window, int screenWidth, int screenHeight, std::vector<Position> &v):
	board(board), window(window),screenWidth(screenWidth),screenHeight(screenHeight),v(v)
{
	fieldWidth = screenWidth / 16;
	fieldHeight = screenHeight / 16;
	field = sf::RectangleShape(sf::Vector2f(fieldWidth, fieldHeight));
	field.setFillColor(sf::Color(192, 192, 192));

	if (!font.loadFromFile("Arial.ttf"))
	{
		std::cout << "Failed to load font at: SFMLBoard";
	}

	if (!wallTexture.loadFromFile("wall.png"))
		std::cout << "Failed to load wall texture";
	if (!grassTexture.loadFromFile("grass.png"))
		std::cout << "Failed to load grass texture";
	if (!appleTexture.loadFromFile("apple.png"))
		std::cout << "Failed to load apple texture";
	if (!snakeTexture.loadFromFile("snakeBody.png"))
		std::cout << "Failed to load snakeBody texture";
	if (!curveTexture.loadFromFile("snakeCurve.png"))
		std::cout << "Failed to load snakeCurve texture";
	if (!headTexture.loadFromFile("snakeHead.png"))
		std::cout << "Failed to load snakeHead texture";
	if (!tailTexture.loadFromFile("snakeTail.png"))
		std::cout << "Failed to load snakeTail texture";
	if (!pauseScreen.loadFromFile("pauseScreen.png"))
		std::cout << "Failed to lad pauseScreen texture";

	wall.setTexture(wallTexture);
	grass.setTexture(grassTexture);
	apple.setTexture(appleTexture);
	snake.setTexture(snakeTexture);
	head.setTexture(headTexture);
	tail.setTexture(tailTexture);
	curve.setTexture(curveTexture);
	pauseSprite.setTexture(pauseScreen);

	wall.setOrigin(sf::Vector2f(fieldWidth / 2, fieldHeight / 2));
	grass.setOrigin(sf::Vector2f(fieldWidth / 2, fieldHeight / 2));
	apple.setOrigin(sf::Vector2f(fieldWidth / 2, fieldHeight / 2));
	snake.setOrigin(sf::Vector2f(fieldWidth / 2, fieldHeight / 2));
	head.setOrigin(sf::Vector2f(fieldWidth / 2, fieldHeight / 2));
	tail.setOrigin(sf::Vector2f(fieldWidth / 2, fieldHeight / 2));
	curve.setOrigin(sf::Vector2f(fieldWidth / 2, fieldHeight / 2));

}

void SFMLBoard::drawField(int x, int y)
{
	field.setPosition(x, y);
	window.draw(field);
}


void SFMLBoard::drawEmptyBoard()
{
	int width = 0;
	int height = 0;
	for (int i = 0; i < board.getBoardWidth(); i++)
	{

		for (int j = 0; j < board.getBoardHeight(); j++)
		{
			drawField(i*fieldWidth, j*fieldHeight);
		}

	}

}

void SFMLBoard::drawBoard()
{

	for (int i = 0; i < board.getBoardHeight(); ++i)
	{
		for (int j = 0; j < board.getBoardWidth(); ++j)
		{
			if (board.hasWall(i, j) == 1)
				drawSprite(wall, i*fieldWidth, j*fieldHeight);
			else if (board.hasFruit(i, j) == 1)
				drawSprite(apple, i*fieldWidth, j*fieldHeight);
			else if (board.hasSnakeHead(i, j) == 1)
			{
				rotation(head, v.at(0).heading);
				drawSprite(head, i*fieldWidth, j*fieldHeight);
			}
				
			else if (board.hasSnake(i, j) != 1)
				drawSprite(grass, i*fieldWidth, j*fieldHeight);
		}
	}
	if(v.size()>1)
	drawSnake();


}

void SFMLBoard::drawPauseInfo()
{
	window.draw(pauseSprite);
}

void SFMLBoard::drawSnake() //funkcja wyglada jak wyglada ale spedzilem mnostwo czasu zeby dzialala idealnie i boje sie jej teraz dotykac
{
	int r = v.at(1).heading;
	for (int i = 1; i < v.size(); ++i)
	{
		if (i == v.size() - 1)
			int a = 0;
		if (v.at(i).heading < 0 && i !=v.size()-1)
		{
			rotation(curve, v.at(i).heading);
			drawSprite(curve, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);
		}

		else if (i <= v.size() - 2)
		{
			int n = v.at(i-1).heading;

			if (r == n || n<0)
			{
				rotation(snake, v.at(i).heading);
				drawSprite(snake, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);
			}
			else
			{
			//kierunek glowy weza poprzednio,kierunek skretu
				if ((r == 1 && n == 2) || (r == 4 && n == 3))
				{
					rotation(curve, 1);
					drawSprite(curve, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);
					if (r == 1)
						v.at(i).heading = -5;
					if (r == 4)
						v.at(i).heading = -1;

					if (i == v.size() - 2)
					{
						if (r == 1)
						{
							i++;
							rotation(tail, 1);
							drawSprite(tail, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);
						}
						if (r == 4)
						{
							i++;
							rotation(tail, 4);
							drawSprite(tail, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);
						}
					}
				}
				else if ((r == 1 && n == 4) || (r == 2 && n == 3))
				{
					rotation(curve, 2);
					drawSprite(curve, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);
					if (r == 1)
						v.at(i).heading = -6;
					if (r == 2)
						v.at(i).heading = -2;
					if (i == v.size() - 2)
					{
						if (r == 1)
						{
							i++;
							rotation(tail, 1);
							drawSprite(tail, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);

						}
						if (r == 2)
						{
							i++;
							rotation(tail, 2);
							drawSprite(tail, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);

						}
					}
				}
				else if ((r == 3 && n == 2) || (r == 4 && n == 1))
				{
					rotation(curve, 4);
					drawSprite(curve, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);
					if (r == 3)
						v.at(i).heading = -8;
					if (r == 4)
						v.at(i).heading = -4;
					if (i == v.size() - 2)
					{
						if (r == 3)
						{
							i++;
							rotation(tail, 3);
							drawSprite(tail, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);

						}
						if (r == 4)
						{
							i++;
							rotation(tail, 4);
							drawSprite(tail, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);

						}
					}
					
				}
				else if ((r == 3 && n == 4) || (r==2 && n==1))
				{
					rotation(curve, 3);
					drawSprite(curve, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);
					if (r == 3)
						v.at(i).heading = -7;
					if (r == 2)
						v.at(i).heading = -3;
					if (i == v.size() - 2)
					{
						if (r == 3)
						{
							i++;
							rotation(tail, 3);
							drawSprite(tail, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);

						}
						if (r == 2)
						{
							i++;
							rotation(tail, 2);
							drawSprite(tail, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);

						}
					}
				}
			}
			r = v.at(i).heading;
		}
		else if (i == v.size() - 1)
		{
			if (v.size() == 2)
			{
				rotation(tail, v.at(0).heading);
				drawSprite(tail, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);
				
			}
			else 
			{
				if (v.at(i).heading < 0)
				{
					if (v.at(i-1).heading > 0)
						rotation(tail, v.at(i - 1).heading);
					else
					{
						if (v.at(i - 1).heading == -2)
						{
							if (v.at(i).heading == -1 || v.at(i).heading == -4 || v.at(i).heading == -8 || v.at(i).heading == -5)
								rotation(tail, 2);
							else if (v.at(i).heading == -3 || v.at(i).heading == -2)
								rotation(tail, 1);
						}
						else if (v.at(i - 1).heading == -1)
						{
							if (v.at(i).heading == -2 || v.at(i).heading == -3 || v.at(i).heading == -7 || v.at(i).heading == -6)
								rotation(tail, 4);
							else if (v.at(i).heading == -4 || v.at(i).heading == -1)
								rotation(tail, 1);
						}
						else if (v.at(i - 1).heading == -4)
						{
							if (v.at(i).heading == -1 || v.at(i).heading == -2)
								rotation(tail, 3);
							else if (v.at(i).heading == -3 || v.at(i).heading == -4 || v.at(i).heading == -6 || v.at(i).heading == -7)
								rotation(tail, 4);
						}
						else if (v.at(i - 1).heading == -3)
						{
							if (v.at(i).heading == -4 || v.at(i).heading == -3 || v.at(i).heading == -5)
								rotation(tail, 2);
							else if (v.at(i).heading == -2 || v.at(i).heading == -1)
								rotation(tail, 3);							
						}
						else if (v.at(i - 1).heading == -6)
						{
							if (v.at(i).heading == -4 || v.at(i).heading == -3)
								rotation(tail, 1);
						}
						else if (v.at(i - 1).heading == -5)
						{
							if (v.at(i).heading == -3 || v.at(i).heading == -4)
								rotation(tail, 1);
						}
						else if (v.at(i - 1).heading == -8)
						{
							if (v.at(i).heading == -2 || v.at(i).heading == -1)
								rotation(tail, 3);
						}
						else if (v.at(i - 1).heading == -7)
						{
							if (v.at(i).heading == -1 || v.at(i).heading == -2)
								rotation(tail, 3);
						}
					}

					drawSprite(tail, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);
				}
				else
				{
					rotation(tail, v.at(i).heading);
					drawSprite(tail, v.at(i).x*fieldWidth, v.at(i).y*fieldHeight);
				}
			}
		}
	}
		
}


void SFMLBoard::rotation(sf::Sprite &s, int heading)
{
	switch (heading)
	{
	case 1:
		s.setRotation(0);
		break;
	case 2:
		s.setRotation(90);
		break;
	case 3:
		s.setRotation(180);
		break;
	case 4:
		s.setRotation(270);
		break;
	case -1:
		s.setRotation(0);
		break;
	case -2:
		s.setRotation(90);
		break;
	case -3:
		s.setRotation(180);
		break;
	case -4:
		s.setRotation(270);
		break;
	case -5:
		s.setRotation(0);
		break;
	case -6:
		s.setRotation(90);
		break;
	case -7:
		s.setRotation(180);
		break;
	case -8:
		s.setRotation(270);
		break;
	default:
		std::cout << "BLAD rotation\n";

	}
}

void SFMLBoard::drawSprite(sf::Sprite & s, int x, int y)
{
	s.setPosition(x+fieldWidth/2, y+fieldHeight/2);
	window.draw(s);
}



