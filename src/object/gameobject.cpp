#include "object/gameobject.h"
#include "texture/animation.h"
#include "input/direction.h"

#include "texture/animelabel.h"


GameObject::GameObject(std::string ID, const Vector2 pos, const int width, const int height):
Iobject()
{
	m_id=ID;
	this->m_pos=pos;
	m_velocity=(Vector2){0,0};
	m_boundingBox={pos.x, pos.y, width, height};
	
	m_currentAnimation=ANIMELABEL::NOANIMATION;
}

GameObject::~GameObject()
{

}

void GameObject::Update(double dt)
{
	//Physic management
	
	m_sprite.at(m_currentAnimation)->Update(dt);
}

void GameObject::Draw()
{
	m_sprite.at(m_currentAnimation)->Draw(m_pos.x, m_pos.y, WHITE);
	//DrawRectangle(m_posX, m_posY, 16, 16,MAROON);
}

void GameObject::Move(Direction dir)
{
	if(dir==Direction::RIGHT)
	{
		this->m_velocity.x=100;
	}
	if(dir==Direction::LEFT)
	{
		this->m_velocity.x=-100;
	}
	if(dir==Direction::DOWN)
	{
		this->m_velocity.y=100;
	}
	if(dir==Direction::UP)
	{
		this->m_velocity.y=-100;
	}
}
		
		// Accesseur
float GameObject::GetPosX() const
{
	return m_pos.x;
}

float GameObject::GetPosY() const 
{
	return m_pos.y;
}

const Vector2& GameObject::GetVelocity() const
{
	return m_velocity;
}

const Rectangle& GameObject::GetBox() const
{
	return m_boundingBox;
}

void GameObject::SetPos(const Vector2 pos)
{
	m_pos=pos;
	m_boundingBox.x=pos.x;
	m_boundingBox.y=pos.y;
}

void GameObject::SetPosX(const float posX)
{
	m_pos.x=posX;
	m_boundingBox.x=posX;
}

void GameObject::SetPosY(const float posY)
{
	m_pos.y=posY;
	m_boundingBox.y=posY;
}

void GameObject::ApplyVelocityX(float dt)
{
	m_boundingBox.y=m_pos.y;
	m_boundingBox.x+=m_velocity.x*dt;
}

void GameObject::ApplyVelocityY(float dt)
{
	m_boundingBox.x=m_pos.x;
	m_boundingBox.y+=m_velocity.y*dt;
}
		
void GameObject::TranslateBox(const Vector2 pos)
{
	m_boundingBox.x+=pos.x;
	m_boundingBox.y+=pos.y;
}

void GameObject::ApplyDisplacement()
{
	m_pos.x=m_boundingBox.x;
	m_pos.y=m_boundingBox.y;
}

void GameObject::ResetVelocity()
{
	this->m_velocity.x=0;
	this->m_velocity.y=0;
}

void GameObject::ResetVelocityX()
{
	this->m_velocity.x=0;
}

void GameObject::ResetVelocityY()
{
	this->m_velocity.y=0;
}

/*void Character::AddSprite(std::string id, Texture2D& texture)
{
	this->m_sprite=new Sprite(id, texture);
}*/

void GameObject::AddAnimation(ANIMELABEL label, const std::string id, Texture2D& texture, const int x, const int y, const int w, const int h, const int frameRate, const int nbrFrame)
{
	m_sprite.emplace(label,std::make_unique<Animation>(id, texture, x, y, w, h, frameRate, nbrFrame));
}
