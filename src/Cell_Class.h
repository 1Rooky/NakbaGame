#pragma once
#include "SFML/Graphics.hpp"
#define thicknessOffset 5
class Cell_Class
{
public:
	sf::Vector2f My_Pos = { 0,0 };
	sf::VertexArray lineup;
	sf::VertexArray LineRight;
	sf::VertexArray LineDown;
	sf::VertexArray LineLeft;
	float wall_width;
	float wall_height;
	
	bool visited = false;
	bool Build_wall[4] = {true,true,true,true};
	sf::RectangleShape* wallSprite=new sf::RectangleShape[4];
	sf::FloatRect* wallSpiteBoundries = new sf::FloatRect[4];

	Cell_Class(sf::Vector2f My_Pos, sf::Texture* texture,float wall_width,float wall_height);

	Cell_Class();
	
};

