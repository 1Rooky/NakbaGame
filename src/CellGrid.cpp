#include "CellGrid.h"


CellGrid::CellGrid(int rowNum, int columnNum, int cellSize)
{

	
	this->texture->loadFromFile("./assets/Tiles/leftWall.png");
	this->textureright->loadFromFile("./assets/Tiles/rightWall.png");
	this->texturedown->loadFromFile("./assets/Tiles/down.png");
	this->texturetop->loadFromFile("./assets/Tiles/top.png");
	

	this->row_num = rowNum;
	this->column_num = columnNum;
	this->cellsize = cellSize;
	this->Grid= new Cell_Class[rowNum*columnNum];
	int append = 0;
	for (int y = 0; y < row_num; y++) {
		for (int x = 0; x < column_num; x++) {
			int relative_x = (x * cellSize);
			int relative_y = (y * cellSize);

			Cell_Class cell(sf::Vector2f(relative_x, relative_y),texture,wallWidth,wallHieght);

			cell.wallSprite[0].setPosition(relative_x, relative_y);
			

			cell.wallSprite[1].setPosition(relative_x + cellsize-wallHieght, relative_y-wallHieght);

			cell.wallSprite[2].setPosition(relative_x, relative_y+cellsize-wallHieght);

			cell.wallSprite[3].setPosition(relative_x, relative_y-wallHieght);

			
			cell.wallSpiteBoundries[0]= (cell.wallSprite[0].getGlobalBounds());
			cell.wallSpiteBoundries[1] = (cell.wallSprite[1].getGlobalBounds());
			cell.wallSpiteBoundries[2] = (cell.wallSprite[2].getGlobalBounds());
			cell.wallSpiteBoundries[3] = (cell.wallSprite[3].getGlobalBounds());

			this->Grid[append++] = cell;


		}


	}
	this->Current = &Grid[0];
	
}



Cell_Class* CellGrid::checkAndGetNeigbors(Cell_Class current)
{
	vector<Cell_Class*> Neighbors;

	int i = current.My_Pos.x / cellsize;
	int j = current.My_Pos.y / cellsize;
	
	Cell_Class* top = &Grid[Grid_Tools::GetIndex2D(i, j - 1,column_num,row_num)];
	Cell_Class* right = &Grid[Grid_Tools::GetIndex2D(i + 1, j,column_num, row_num)];
	Cell_Class* bottom = &Grid[Grid_Tools::GetIndex2D(i, j + 1, column_num, row_num)];
	Cell_Class* left = &Grid[Grid_Tools::GetIndex2D(i-1, j, column_num, row_num)];

	if (top && !top->visited) {
		Neighbors.push_back(top);
	}
	if (right && !right->visited) {
		Neighbors.push_back(right);
	}
	if (bottom && !bottom->visited) {
		Neighbors.push_back(bottom);
	}
	if (left && !left->visited) {
		Neighbors.push_back(left);
	}
	if (Neighbors.size() > 0) {
		int n = Grid_Tools::random(0,Neighbors.size()-1);
		return Neighbors[n];
	}
	else {

		return NULL;
	}
	
	
}


void CellGrid::removewalls(Cell_Class* Current, Cell_Class* Next)
{
	int x = Current->My_Pos.x/cellsize - Next->My_Pos.x/cellsize;
	if (x == 1) {
		Current->Build_wall[3] = false;
		Current->wallSpiteBoundries[3] = sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);

		Next->Build_wall[1] = false;
		Next->wallSpiteBoundries[1]= sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (x == -1) {
		Current->Build_wall[1] = false;
		Current->wallSpiteBoundries[1] = sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);

		Next->Build_wall[3] = false;
		Next->wallSpiteBoundries[3] = sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);
	}
	int y = Current->My_Pos.y/cellsize - Next->My_Pos.y/cellsize;
	if (y == 1) {
		Current->Build_wall[0] = false;
		Current->wallSpiteBoundries[0] = sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);

		Next->Build_wall[2] = false;
		Next->wallSpiteBoundries[2] = sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);
	}
	else if (y == -1) {
		Current->Build_wall[2] = false;
		Current->wallSpiteBoundries[2] = sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);

		Next->Build_wall[0] = false;
		Next->wallSpiteBoundries[0] = sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);
	}

}

void CellGrid::Display(sf::RenderWindow& window)
{
	Current->visited = true;

	//STEP 1
	Cell_Class* next = checkAndGetNeigbors(*Current);
	if (next) {
		
		next->visited = true;
		//STEP 2
		backtrackstack.push(Current);
		
		//STEP 3
		removewalls(Current, next);

		//STEP 4
		Current = next;
	}
	else if (!backtrackstack.empty())
	{
		Current = backtrackstack.top();
		backtrackstack.pop();
	}

	for (int i = 0; i < this->row_num * this->column_num; i++) {
		
		if (Grid[i].Build_wall[0] == true) {
			Grid[i].wallSprite[0].setTexture(texturetop);
			window.draw(Grid[i].wallSprite[0]);
			
		}

		if (Grid[i].Build_wall[2] == true) {
			Grid[i].wallSprite[2].setTexture(texturedown);
			window.draw(Grid[i].wallSprite[2]);
		}

		if (Grid[i].Build_wall[1] == true) {
			Grid[i].wallSprite[1].setTexture(textureright);
			window.draw(Grid[i].wallSprite[1]);
		}

		if (Grid[i].Build_wall[3] == true) {
			
			Grid[i].wallSprite[3].setTexture(texture);
			window.draw(Grid[i].wallSprite[3]);
		}



	}
	
	
}


