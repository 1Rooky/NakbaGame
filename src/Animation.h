#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Animation
{
public:
	Animation(Texture* texture, Vector2u imageCount, float switchTime );
	void update(int row, float deltaTime);
	IntRect texRec;
      
private:
	Vector2u imageCount;
	Vector2u currentImage;
	float totalTime;
	float switchTime;
};

