#include "physic/collisionhandler.h"

#include "object/gameobject.h"
#include "level/layer.h"
#include "level/tilemap.h"
#include "level/tilelayer.h"

#include <array>

CollisionInfo CollisionHandler::CheckX(const Rectangle& r1, const Rectangle& r2)
{	
	CollisionInfo info={
	false, 
	COLLISIONSIDE::NONE,
	{0.0f,0.0f},
	0
	};
	
	if (CheckCollisionRecs(r1, r2))
	{
		info.collided=true;
		Rectangle overlap=GetCollisionRec(r1, r2);
		
		//Check overlaping direction
		//RIGHT or LEFT
		if(overlap.width<=overlap.height)
		{
			info.penetration=overlap.width;
			//Check overlaping direction
			// r1 right r2 --> LEFT
			if (r1.x>=r2.x)
			{
				info.side=COLLISIONSIDE::LEFT;
				info.normal={1.0f, 0.0f};
			}
			// r1 below r2 --> RIGHT
			else
			{
				info.side=COLLISIONSIDE::RIGHT;
				info.normal={-1.0f, 0.0f};
			}
			return info;
		}
		
	}
	return info;
}

CollisionInfo CollisionHandler::CheckY(const Rectangle& r1, const Rectangle& r2)
{	
	CollisionInfo info={
	false, 
	COLLISIONSIDE::NONE,
	{0.0f,0.0f},
	0
	};
	
	if (CheckCollisionRecs(r1, r2))
	{
		Rectangle overlap=GetCollisionRec(r1, r2);
		
		//Check overlaping direction
		//UP or DOWN
		if(overlap.width>=overlap.height)
		{
			info.collided=true;
			info.penetration=overlap.height;
			//Check overlaping direction
			// r1 above r2 --> DOWN
			if (r1.y<r2.y)
			{
				info.side=COLLISIONSIDE::DOWN;
				info.normal={0.0f, -1.0f};
			}
			// r1 below r2 --> UP
			else
			{
				info.side=COLLISIONSIDE::UP;
				info.normal={0.0f, 1.0f};
			}
			return info;
		}	
	}

	return info;
}

CollisionInfo CollisionHandler::CheckMapXSide(const GameObject& object, TileMap& map)
{
	float epsilon=1.0f;
    CollisionInfo bestInfo{
        false,
        COLLISIONSIDE::NONE,
        {0.0f, 0.0f},
        10000       // très grande pénétration initiale
    };
    CollisionInfo info{
        false,
        COLLISIONSIDE::NONE,
        {0.0f, 0.0f},
        10000       // très grande pénétration initiale
    };
    
    const Rectangle& r1=object.GetBox();
    if(object.GetVelocity().x==0)
    {
		return bestInfo;
	}
	
	 else
	 {
		std::array<Vector2, 2> corners = {{ {0,0}, {0,0} }};
		
		if(object.GetVelocity().x<0)
		{
			//LEFT
			corners[0] ={r1.x+epsilon,    r1.y+epsilon};
			corners[1] ={r1.x+epsilon,    r1.y + r1.height-epsilon};
			
			info.side=COLLISIONSIDE::LEFT;
			info.normal={1.0f,0.0f};
		}
		
		else
		{
			//RIGHT
			corners[0] ={r1.x + r1.width-epsilon,               r1.y+epsilon};
			corners[1] ={r1.x + r1.width-epsilon,    r1.y + r1.height-epsilon};
			
			info.side=COLLISIONSIDE::RIGHT;
			info.normal={-1.0f,0.0f};
		}

		for (const auto& p : corners)
		{
			TileLayer& layer = map.GetTileLayer(LAYER::COLLISION);
			if (layer.GetTileID(p) != 1)
				continue;

			Rectangle tileRect = layer.GetTileRect(p);

			Rectangle overlap = GetCollisionRec(r1, tileRect);

			if (overlap.width <= 0 || overlap.height <= 0)
				continue;

			info.collided = true;
			info.penetration = overlap.width;

			// On garde la collision ayant la plus faible pénétration
			if (info.penetration < bestInfo.penetration)
				bestInfo = info;
		}

		return bestInfo;
	}
}

CollisionInfo CollisionHandler::CheckMapYSide(const GameObject& object, TileMap& map)
{
	float epsilon=1.0f;
    CollisionInfo bestInfo{
        false,
        COLLISIONSIDE::NONE,
        {0.0f, 0.0f},
        10000       // très grande pénétration initiale
    };
    
        CollisionInfo info{
        false,
        COLLISIONSIDE::NONE,
        {0.0f, 0.0f},
        10000       // très grande pénétration initiale
    };
    
    const Rectangle& r1=object.GetBox();
    if(object.GetVelocity().y==0)
    {
		return bestInfo;
	}
	
	 else
	 {
		std::array<Vector2, 2> corners = {{ {0,0}, {0,0} }};
		
		if(object.GetVelocity().y<0)
		{
			//UP
			corners[0] ={r1.x + r1.width-epsilon,    r1.y+epsilon};
			corners[1] ={r1.x+epsilon,    r1.y+epsilon};
			
			info.side=COLLISIONSIDE::UP;
			info.normal={0.0f,1.0f};
		}
		
		else
		{
			//DOWN
			corners[0] ={r1.x+epsilon,               r1.y + r1.height-epsilon};
			corners[1] ={r1.x + r1.width-epsilon,    r1.y + r1.height-epsilon};
			
			info.side=COLLISIONSIDE::DOWN;
			info.normal={0.0f,-1.0f};
		}

		for (const auto& p : corners)
		{
			TileLayer& layer = map.GetTileLayer(LAYER::COLLISION);

			if (layer.GetTileID(p) != 1)
				continue;

			Rectangle tileRect = layer.GetTileRect(p);

			Rectangle overlap = GetCollisionRec(r1, tileRect);

			if (overlap.width <= 0 || overlap.height <= 0)
				continue;

			info.collided = true;
			info.penetration = overlap.height;

			// On garde la collision ayant la plus faible pénétration
			if (info.penetration < bestInfo.penetration)
				bestInfo = info;
		}

		return bestInfo;
	}
}

void CollisionHandler::CheckOutMap(GameObject& object, TileMap& map)
{
	const Rectangle rect=object.GetBox();
	
	if(rect.x<=0)
	{
		object.SetPosX(0.0f);
	}
	else if ((rect.x+rect.width)>=map.GetSizeX())
	{
		object.SetPosX(map.GetSizeX()-rect.width);
	}
	
	if(rect.y<=0)
	{
		object.SetPosY(0.0f);
	}
	else if ((rect.y+rect.height)>=map.GetSizeY())
	{
		object.SetPosY(map.GetSizeY()-rect.height);
	}
}

void CollisionHandler::CollisionSolverObj(GameObject& object1, GameObject& object2, float dt)
{
	object1.ApplyVelocityX(dt);
	
	CollisionInfo info=CheckX(object1.GetBox(),object2.GetBox());
	if(info.collided)
	{
		object1.TranslateBox((Vector2){info.normal.x*info.penetration,0});
		object1.ResetVelocityX();
	}
	
	object1.ApplyDisplacement();	
	object1.ApplyVelocityY(dt);
	
	info=CheckY(object1.GetBox(),object2.GetBox());
	if(info.collided)
	{
		object1.TranslateBox((Vector2){0,info.normal.y*info.penetration});
		object1.ResetVelocityY();
	}
	
	object1.ApplyDisplacement();
}

void CollisionHandler::CollisionSolverMap(GameObject& object, TileMap& map, float dt)
{
	object.ApplyVelocityX(dt);
	
	CollisionInfo info=CheckMapXSide(object,map);
	if(info.collided)
	{
		object.TranslateBox((Vector2){int(info.normal.x*info.penetration),0});
		object.ResetVelocityX();
	}
	
	object.ApplyDisplacement();
	CheckOutMap(object, map);
	
	object.ApplyVelocityY(dt);
	
	info=CheckMapYSide(object,map);
	if(info.collided)
	{
		object.TranslateBox((Vector2){0,int(info.normal.y*info.penetration)});
		object.ResetVelocityY();
	}
	
	object.ApplyDisplacement();
	CheckOutMap(object, map);
	
	object.ResetVelocity();
}
