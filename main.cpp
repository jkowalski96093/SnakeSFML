#include <iostream>
#include "Game.h"
#include "Menu.h"


int main()
{
	GameBoard board;
	Map map(board, 1);
	Snake snake(board);
	sf::RenderWindow window(sf::VideoMode(864, 864), "Snake");
	window.setVerticalSyncEnabled(true);
	SFMLBoard SFMLboard(board,window,864,864,snake.getVector());
	Menu menu(board, window);
	Game game(board, SFMLboard, snake, window);
	int mapNo=0;

	while (window.isOpen())
	{
		if (board.getIsMenu() == 0)
		{
			game.insertMapNo(menu.getMapNo());
			game.insertDiffNo(menu.getDiffNo());
			game.Play();
		}
		else if (board.getIsMenu() == 1)
			menu.displayMenu();

	}


	return 0;
}