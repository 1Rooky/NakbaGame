#include "Animation.h"

Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0; 
	texRec.width = texture->getSize().x / float(imageCount.x);
	texRec.height= texture->getSize().y / float(imageCount.y);

}

void Animation::update(int row, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x) {
			currentImage.x  = 0;
		}
	}
	texRec.left = currentImage.x * texRec.width;
	texRec.top = currentImage.y * texRec.height;
}
