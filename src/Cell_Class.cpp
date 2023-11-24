#include "Cell_Class.h"
#include <iostream>



Cell_Class::Cell_Class() {
}

Cell_Class::Cell_Class(sf::Vector2f My_Pos, sf::Texture* texture, float wall_width, float wall_height)
{
	this->lineup = sf::VertexArray(sf::Lines, 2);
	this->LineRight = sf::VertexArray(sf::Lines, 2);
	this->LineDown = sf::VertexArray(sf::Lines, 2);
	this->LineLeft = sf::VertexArray(sf::Lines, 2);

	//top wall
	wallSprite[0].setSize(sf::Vector2f(wall_width, wall_height + 50));


	//right wall
	wallSprite[1].setSize(sf::Vector2f(wall_height, wall_width + (wall_height * 2)));

	//down wall
	wallSprite[2].setSize(sf::Vector2f(wall_width, wall_height));

	//left wall//
	wallSprite[3].setSize(sf::Vector2f(wall_height, wall_width + (wall_height * 2)));

	this->My_Pos = My_Pos;
}