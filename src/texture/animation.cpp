#include "texture/animation.h"

Animation::Animation(const std::string id, Texture2D& texture, const int x, const int y, const int w, const int h, const int frameRate, const int nbrFrame)
{
	this->m_sprite=&texture;
	m_id=id;
	
	m_previousTime=0;
	m_currentTime=0;
	
	m_beginFrame=(Vector2){x, y};
	m_frameRec={ 0, 0, (float)w, (float)h};
	m_currentFrame=0;
	m_frameRate=frameRate;
	m_nbrFrame=nbrFrame;
}

Animation::~Animation()
{

}
		
void Animation::Update(double dt)
{
	if(m_nbrFrame>1)
	{
		m_currentTime+=dt;
		if((m_currentTime-m_previousTime)>(1/m_frameRate))
		{
			m_previousTime=m_currentTime;
			m_currentFrame=(m_currentFrame+1)%m_nbrFrame;
			m_frameRec.x=m_beginFrame.x+m_currentFrame*m_frameRec.width;
			m_frameRec.y=m_beginFrame.y;
		}
	}
}
		
void Animation::Draw(const int x, const int y, Color tint)
{
	Vector2 pos={(float)x, (float)y};
	DrawTextureRec(*m_sprite, m_frameRec, pos, tint);
}

void Animation::Draw(Vector2 pos, Color tint)
{
	DrawTextureRec(*m_sprite,m_frameRec, pos,tint);
}
