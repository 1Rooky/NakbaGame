#include "Grid_Tools.h"

int Grid_Tools::GetIndex2D(int x, int y, int columnNumber,int row_num)
{
	if (x<0 || y<0 || x>columnNumber - 1 || y>row_num - 1) {
		return -1;
	}

	return x + y * columnNumber;
}

int Grid_Tools::random(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	int randomNum = distribution(gen);
	return randomNum;
}
