#include "texture/sprite.h"


Sprite::Sprite(const std::string& id, Texture2D& texture)
{
	this->m_sprite=&texture;
	m_id=id;
}

Sprite::~Sprite()
{

}
		
void Sprite::Draw(const int x, const int y, Color tint)
{
	DrawTexture(*m_sprite,x,y,tint);
}

void Sprite::Draw(Vector2 pos, Color tint)
{
	DrawTextureV(*m_sprite,pos,tint);
}
