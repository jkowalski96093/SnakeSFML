#pragma once
#include "GameBoard.h"
class Map :
	public GameBoard
{
	GameBoard &board;
	std::vector<std::vector<char>> tab;
	int n;
	void Map1();
	void Map2();
	void Map3();
	void Map4();
	void Map5();
	void Map6();
public:
	Map(GameBoard & board,int n);
	void setMap();
	void getMap();
	int getMapCount(); //ulatwienie dla Menu.h przy wiekszej ilosci map
	void MapClear();

};

