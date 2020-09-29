// Wall.h
// Zixuan Shi
// Wall object, player cannot passing through

#include "CollidableStaticObject.h"

///////////////////////////////////////////////
// Solid walls
///////////////////////////////////////////////
class Wall : public CollidableStaticObject
{
private:
public:
	Wall(SDL_Rect wallRectangle, CollisionReferee* pReferee);

	virtual void Render(SDL_Renderer* pRenderer) override;
};
