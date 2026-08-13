#ifndef MYCAMERA_H
#define MYCAMERA_H

#include "raylib.h"

#include "object/gameobject.h"

class Mycamera
{
	public:
		Mycamera();
		virtual ~Mycamera()=default;
		
		void Initialize(GameObject& target, Vector2 offset, float rotation, float zoom);
		void BeginDraw();
		void EndDraw();
		
		void SetTarget(GameObject& object);
		void Update();
		
		const Camera2D& GetCamera() const;
	
	private:
		Camera2D m_camera;
		GameObject *m_objtarget;
		

};
#endif
