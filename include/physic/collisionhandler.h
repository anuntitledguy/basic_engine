#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "raylib.h"

#include "physic/collisionside.h"

class TileMap;
class GameObject;

typedef struct{
	bool collided;
	COLLISIONSIDE side;
	Vector2 normal;
	float penetration;

}CollisionInfo;

class CollisionHandler
{
	public:
		CollisionHandler(){}
		virtual ~CollisionHandler()=default;
		
		CollisionInfo CheckX(const Rectangle& r1, const Rectangle& r2);
		CollisionInfo CheckY(const Rectangle& r1, const Rectangle& r2);
		CollisionInfo CheckMapXSide(const GameObject& object, TileMap& map);
		CollisionInfo CheckMapYSide(const GameObject& object, TileMap& map);
		
		void CheckOutMap(GameObject& object, TileMap& map);
		void CollisionSolverObj(GameObject& object1, GameObject& object2, float dt);
		void CollisionSolverMap(GameObject& object, TileMap& map, float dt);

};
#endif
