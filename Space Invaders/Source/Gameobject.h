#pragma once

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void Attack();
	void SetPosX(float newPosX);
	void SetPosY(float newPosY);
	float GetPosX();
	float GetPosY();
	void SetWidth(float newWidth);
	void SetHeight(float newHeight);
	float GetWidth();
	float GetHeight();
	bool GetIsAlive();
	void SetIsAlive(bool isItAlive);
	

private:

	bool isAlive;
	float posX;
	float posY;
	float height;
	float width;
	

};
