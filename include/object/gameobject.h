#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "object/iobject.h"

#include "raylib.h"

#include "texture/animelabel.h"
#include "texture/animation.h"

#include <iostream>
#include <map>
#include <memory>

class Sprite;
enum class Direction;

class GameObject : public Iobject
{
	public:
		GameObject(std::string ID, const Vector2 pos, const int width, const int height);
		virtual ~GameObject();
	
	
		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;

		GameObject(GameObject&&) noexcept = default;
		GameObject& operator=(GameObject&&) noexcept = default;
		
		
		virtual void Update(double dt);
		virtual void Draw();
		
		void Move(Direction dir);
		
		// Accesseur
		float GetPosX() const;
		float GetPosY() const;
		const Vector2& GetVelocity() const;
		const Rectangle& GetBox() const;
		
		void SetPos(const Vector2 pos);
		void SetPosX(const float posX);
		void SetPosY(const float posY);
		
		void ApplyVelocityX(float dt);
		void ApplyVelocityY(float dt);
		void TranslateBox(const Vector2 pos);
		void ApplyDisplacement();
		void ResetVelocityX();
		void ResetVelocityY();
		void ResetVelocity();
		
		// Component add
		//void AddSprite(std::string id, Texture2D& texture);
		void AddAnimation(ANIMELABEL label, const std::string id, Texture2D& texture, const int x, const int y, const int w, const int h, const int frameRate, const int nbrFrame);
	
	private:
		std::string m_id;
		Vector2 m_pos;
		Vector2 m_velocity;
		
		std::map<ANIMELABEL,std::unique_ptr<Animation>> m_sprite;
		ANIMELABEL m_currentAnimation;
		
		//texture et boundingBox
		Rectangle m_boundingBox;
};
#endif
