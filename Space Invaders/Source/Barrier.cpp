#include "Barrier.h"
#include <Engine/Renderer.h>

Barrier::Barrier(std::shared_ptr<ASGE::Renderer> temp_renderer)
{
	renderer = temp_renderer;
	barrierSprite = renderer->createSprite();
	barrierSprite->loadTexture("..\\..\\Resources\\Textures\\barrier.png");
	barrierSprite->size[0] = 75;
	barrierSprite->size[1] = 50;
	this->SetPosY(420);
	
}

Barrier::~Barrier()
{
}

bool Barrier::render()
{
	barrierSprite->position[0] = GetPosX();

	barrierSprite->position[1] = GetPosY();
	barrierSprite->render(renderer);

	return true;
}
