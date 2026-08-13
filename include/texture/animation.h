#ifndef ANIMATION_H
#define ANIMATION_H

#include "raylib.h"

#include "iostream"

class Animation
{
	public:
		Animation(const std::string id, Texture2D& texture, const int x, const int y, const int w, const int h, const int frameRate, const int nbrFrame);
		virtual ~Animation();
		
		void Update(double dt);
		
		virtual void Draw(const int x, const int y, Color tint=BLANK);
		virtual void Draw(Vector2 pos, Color tint=BLANK);
	
	private:
		std::string m_id;
		Texture2D* m_sprite;
		
		//Sprite parameter
		Rectangle m_frameRec;
		Vector2 m_beginFrame;
		
		double m_previousTime;
		double m_currentTime;
		
		int m_currentFrame;
		int m_frameRate;
		int m_nbrFrame;
	
};

#endif
