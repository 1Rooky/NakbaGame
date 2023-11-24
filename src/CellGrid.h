#pragma once
#include "Cell_Class.h"
#include <random>
#include <iostream>
#include <stack>
#include "Grid_Tools.h"
using namespace std;
#define wallWidth 200
#define wallHieght 50

class CellGrid
{
public:
	int row_num;
	int column_num;
	sf::Texture* texture = new sf::Texture;
	sf::Texture* textureright = new sf::Texture;
	sf::Texture* texturedown = new sf::Texture;
	sf::Texture* texturetop = new sf::Texture;
	
	
	Cell_Class* Grid;
	int cellsize;
	Cell_Class* Current;
	stack<Cell_Class*> backtrackstack;
	vector<sf::FloatRect> allboundries;
	
	CellGrid(int rowNum, int columnNum, int cellSize);
	void Display(sf::RenderWindow& window);
	Cell_Class* checkAndGetNeigbors(Cell_Class current);
	void removewalls(Cell_Class* Current, Cell_Class* Next);
};

