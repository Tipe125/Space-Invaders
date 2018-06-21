#include "Gameobject.h"

void GameObject::Attack()
{
}



void GameObject::SetPosX(float newPosX)
{
	posX = newPosX;
}

void GameObject::SetPosY(float newPosY)
{
	posY = newPosY;
}

float GameObject::GetPosX()
{
	return posX;
}

float GameObject::GetPosY()
{
	return posY;
}

void GameObject::SetWidth(float newWidth)
{
	width = newWidth;
}

void GameObject::SetHeight(float newHeight)
{
	height = newHeight;
}

float GameObject::GetWidth()
{
	return width;
}

float GameObject::GetHeight()
{
	return height;
}

bool GameObject::GetIsAlive()
{
	return isAlive;
}

void GameObject::SetIsAlive(bool isItAlive)
{
	isAlive = isItAlive;
	
}
