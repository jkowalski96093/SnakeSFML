#include "Menu.h"


Menu::Menu(GameBoard & board, sf::RenderWindow &window) :board(board),window(window)
{
	if (!funnyFont.loadFromFile("MATURASC.TTF"))
		std::cout << "Failed to load funnyFont\n";
	if (!defaultBackground.loadFromFile("menuBackground.png"))
		std::cout << "Failed to load menuBackground texture\n";
	if (!playBackground.loadFromFile("menuBackgroundPlay.png"))
		std::cout << "Failed to load menuBackgroundPlay texture\n";
	if (!diffBackground.loadFromFile("menuBackgroundDiff.png"))
		std::cout << "Failed to load menuBackgroundDiff texture\n";
	if (!mapBackground.loadFromFile("menuBackgroundMap.png"))
		std::cout << "Failed to load menuBackgroundMap texture\n";
	backgroundSprite.setTexture(defaultBackground);

	mapTxt.setFont(funnyFont);
	diffTxt.setFont(funnyFont);

	mapNo = 1;
	diffNo = 1;
}

void Menu::displayMenu()
{
	while (board.getIsMenu() == 1) {

		sf::RectangleShape playButton = sf::RectangleShape(sf::Vector2f(736 - 153, 746 - 539));
		playButton.setPosition(153, 539);
		sf::RectangleShape difficultyButton = sf::RectangleShape(sf::Vector2f(546 - 50, 485 - 421));
		difficultyButton.setPosition(50, 421);
		sf::RectangleShape mapButton = sf::RectangleShape(sf::Vector2f(335 - 116, 398 - 314));
		mapButton.setPosition(116, 314);

			mousePosition = sf::Vector2f(sf::Mouse::getPosition(window)); //https://forum.pasja-informatyki.pl/209615/sfml-po-najechaniu-myszka-na-tekst-kolor-sie-nie-zmienia
			sf::Event event;
			bool end = 0;
			while (window.pollEvent(event)==1 && end==0)
			{
				if (event.type == sf::Event::Closed)
					window.close();
				//std::cout << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << std::endl;
				if (playButton.getGlobalBounds().contains(mousePosition))
				{
					backgroundSprite.setTexture(playBackground);
					if (event.type == sf::Event::MouseButtonPressed)
					{
						playClick();
						end = 1;
					}
				}
				else if (difficultyButton.getGlobalBounds().contains(mousePosition))
				{
					backgroundSprite.setTexture(diffBackground);
					if (event.type == sf::Event::MouseButtonPressed)
						difficultyClick();
				}
				else if (mapButton.getGlobalBounds().contains(mousePosition))
				{
					backgroundSprite.setTexture(mapBackground);
					if (event.type == sf::Event::MouseButtonPressed)
						mapClick();
				}
				else backgroundSprite.setTexture(defaultBackground);

			}

			window.clear();
			window.draw(backgroundSprite);
			drawStats();
			window.display();
		
	}
}

void Menu::drawStats()
{
	mapTxt.setString(std::to_string(mapNo));
	mapTxt.setPosition(374,286);
	mapTxt.setFillColor(sf::Color::Red);
	mapTxt.setOutlineThickness(2);
	mapTxt.setOutlineColor(sf::Color::Black);
	mapTxt.setCharacterSize(100);
	window.draw(mapTxt);
	switch (diffNo)
	{
	case 1: 
		diffTxt.setString("easy");
		break;
	case 2: 
		diffTxt.setString("medium");
		break;
	case 3:
		diffTxt.setString("hard");
		break;
	}
	diffTxt.setPosition(582, 403);
	diffTxt.setFillColor(sf::Color(200, 191, 231));
	diffTxt.setOutlineThickness(2);
	diffTxt.setOutlineColor(sf::Color::Black);
	diffTxt.setCharacterSize(80);
	window.draw(diffTxt);
}

void Menu::playClick()
{
	Map map(board, mapNo);
	map.setMap();
	board.setGameSpeed(diffNo);
	board.toggleMenu();
}

void Menu::mapClick()
{
	Map map(board, 0);
	if (mapNo < map.getMapCount())
		mapNo++;
	else if (mapNo == map.getMapCount())
		mapNo = 1;
}

void Menu::difficultyClick()
{
	if (diffNo < 3)
		diffNo++;
	else if (diffNo == 3)
		diffNo = 1;
}

int Menu::getMapNo()
{
	return mapNo;
}

int Menu::getDiffNo()
{
	return diffNo;
}

