#include "Camera.h"

namespace ao
{
	Camera::Camera(float width, float height)
	{
		m_Projection = mat4::orthographic(0, width, 0, height, -1, 1);
		m_Width = width;
		m_Height = height;
	}

	Camera::~Camera()
	{

	}

	void Camera::translate(float x, float y)
	{
		m_View = m_View * mat4::translation(x, y, 0);
		update();
	}

	void Camera::translate(const vec2& amount)
	{
		translate(amount.x, amount.y);
	}

	void Camera::setZoom(float amount)
	{
		m_Zoom = mat4::scale(amount, amount, amount);
		update();
	}

	void Camera::update()
	{
		m_InverseView = (m_View * m_Zoom).inverse();
	}

	mat4 Camera::getCombinedMatrix()
	{
		return m_Projection * m_InverseView;
	}
}