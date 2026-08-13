#include "level/mycamera.h"

Mycamera::Mycamera()
{
	m_objtarget=nullptr;
}
void Mycamera::Initialize(GameObject& object, Vector2 offset, float rotation, float zoom)
{
	m_objtarget=&object;
	m_camera.offset=offset;
	m_camera.target=(Vector2){m_objtarget->GetPosX(), m_objtarget->GetPosY()};
	m_camera.rotation=rotation;
	m_camera.zoom=zoom;
}

void Mycamera::BeginDraw()
{
	BeginMode2D(this->m_camera);
}

void Mycamera::EndDraw()
{
	EndMode2D();
}

void Mycamera::Update()
{
	if (!m_objtarget)
        return;

    m_camera.target =
    {
        static_cast<float>(m_objtarget->GetPosX()),
        static_cast<float>(m_objtarget->GetPosY())
    };
}

void Mycamera::SetTarget(GameObject& object)
{
	m_objtarget=&object;
	m_camera.target=(Vector2){object.GetPosX(), object.GetPosY()};
}
		
const Camera2D& Mycamera::GetCamera() const
{
	return m_camera;
}
