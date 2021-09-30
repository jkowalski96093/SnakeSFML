#include "Game.h"

Game::Game(GameBoard & board, SFMLBoard & sfmlboard, Snake & snake, sf::RenderWindow &window):board(board),sfmlboard(sfmlboard),snake(snake),window(window)
{
	if (!funnyFont.loadFromFile("MATURASC.TTF"))
		std::cout << "Failed to load funnyFont\n";
	if (!deathScreen.loadFromFile("deathScreen.png"))
		std::cout << "Failed to load deathScreen\n";
	if (!deathFont.loadFromFile("VINERITC.TTF"))
		std::cout << "Failed to load deathFont\n";
	if (!deathHighScoreScreen.loadFromFile("DeathHighScoreScreen.png"))
		std::cout << "Failed to load DeathHighScoreScreen\n";
	if (!scoreBoardScreen.loadFromFile("scoreboardScreen.png"))
		std::cout << "Failed to load scoreboardScreen\n";
	death.setTexture(deathScreen);
	deathHighScore.setTexture(deathHighScoreScreen);
	scoreBoardSprite.setTexture(scoreBoardScreen);
	board.randomFruit();
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			highScores[i][j] = 0;
		}
		
	}
	score = 0;
	diffNo = 0;
	isHighScore = 0;
}

void Game::Play()
{
	readScoreBoard();
		sf::Event event;
		while (board.getIsMenu() == 0)
		{
			while (snake.getIsAlive() == 1)
			{
				board.randomFruit();
				while (window.pollEvent(event))
				{
					bool lockMove = 0;
					if (event.type == sf::Event::Closed)
						window.close();
					if (event.type == sf::Event::LostFocus)
						board.togglePause();
					if (event.type == sf::Event::KeyPressed)
					{
						switch (event.key.code)
						{
						case sf::Keyboard::W:
						case sf::Keyboard::Up:
							snake.setHeading(1);
							break;
						case sf::Keyboard::D:
						case sf::Keyboard::Right:
							snake.setHeading(2);
							break;
						case sf::Keyboard::S:
						case sf::Keyboard::Down:
							snake.setHeading(3);
							break;
						case sf::Keyboard::A:
						case sf::Keyboard::Left:
							snake.setHeading(4);
							break;
						case sf::Keyboard::P:
							board.togglePause();
							break;
						default:
							break;
						}
					}
				}

				if (board.getIsPaused() == 0)
				{
					snake.move(0);
					sfmlboard.drawBoard();
					window.display();
					std::this_thread::sleep_for(std::chrono::milliseconds(board.getGamespeed())); //https://stackoverflow.com/questions/4184468/sleep-for-milliseconds
				}
				if (board.getIsPaused() == 1)
				{
					window.clear();
					sfmlboard.drawPauseInfo();
					window.display();
				}
				
			}
			GameOver();
			board.toggleMenu();
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				
			}
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			Scoreboard();
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(6000));
			
		}
	
}

void Game::GameOver()
{
	if (snake.getIsAlive() == 0)
	{
		score = snake.getLength()-2;
		if (score > highScores[mapNo-1][diffNo-1])
		{
			highScores[mapNo-1][diffNo-1] = score;
			isHighScore = 1;
		}
		txt.setFont(deathFont);
		txt.setString(std::to_string(score));
		txt.setOutlineThickness(0);
		txt.setFillColor(sf::Color(127, 127, 127));
		txt.setPosition(500, 650);
		txt.setCharacterSize(72);
		if (isHighScore == 1)
			window.draw(deathHighScore);
		else
			window.draw(death);
		window.draw(txt);
		snake.reset();
		isHighScore = 0;
	}
}

void Game::Scoreboard()
{
	readScoreBoard();
	writeScoreBoard();
	window.draw(scoreBoardSprite);
	txt.setFont(funnyFont);
	txt.setCharacterSize(40);
	txt.setFillColor(sf::Color::White);
	txt.setOutlineColor(sf::Color::Black);
	txt.setOutlineThickness(3);
	drawStats();

}

void Game::insertMapNo(int n)
{ 
	mapNo = n;
}

void Game::insertDiffNo(int n)
{
	diffNo = n;
}

void Game::readScoreBoard()
{
	std::string s;
	std::ifstream file("Scoreboard.txt");
	for (int i = 1; i < 7; i++)
	{
		file >> s;
		std::string str = "Map"+std::to_string(i);
		if (s == str)
		{
			for (int j = 0; j < 3; j++)
			{
				file >> s;
				int a = std::stoi(s);
				if (a > highScores[i - 1][j])
					highScores[i - 1][j] = a;
			}
		}
		else std::cout << "BLAD readScoreBoard\n";
	}
}

void Game::writeScoreBoard()
{
	std::ofstream write;
	for (int i = 1; i < 7; i++)
	{
		if (i == 1)
		{
			write.open("Scoreboard.txt");
			std::string str = "Map" + std::to_string(i);
			write << str << std::endl;
			write << highScores[i - 1][0] << std::endl;
			write << highScores[i - 1][1] << std::endl;
			write << highScores[i - 1][2] << std::endl;
			write.close();
		}
		else
		{
			write.open("Scoreboard.txt", std::ios_base::app);
			std::string str = "Map" + std::to_string(i);
			write << str << std::endl;
			write << highScores[i - 1][0] << std::endl;
			write << highScores[i - 1][1] << std::endl;
			write << highScores[i - 1][2] << std::endl;
			write.close();
		}


	}
}

void Game::drawStats()
{
	bool rightSide = 0;
	for (int i = 0; i < 6; i++)
	{
		if (rightSide == 0)
		{
			int y;
			switch (i)
			{
			case 0:y = 225;
				break;
			case 2: y = 478;
				break;
			case 4: y = 726;
				break;
			}
			txt.setString(std::to_string(highScores[i][0]));
			txt.setPosition(138, y);
			window.draw(txt);
			txt.setString(std::to_string(highScores[i][1]));
			txt.setPosition(170, y+41);
			window.draw(txt);
			txt.setString(std::to_string(highScores[i][2]));
			txt.setPosition(122, y+75);
			window.draw(txt);
			rightSide = 1;
		}
		else if (rightSide == 1)
		{
			int y;
			switch (i)
			{
			case 1:y = 225;
				break;
			case 3: y = 478;
				break;
			case 5: y = 726;
				break;
			}
			txt.setString(std::to_string(highScores[i][0]));
			txt.setPosition(598, y);
			window.draw(txt);
			txt.setString(std::to_string(highScores[i][1]));
			txt.setPosition(630, y + 41);
			window.draw(txt);
			txt.setString(std::to_string(highScores[i][2]));
			txt.setPosition(582, y+75);
			window.draw(txt);
			rightSide = 0;
		}
	}
}
