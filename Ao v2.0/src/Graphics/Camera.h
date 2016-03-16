#pragma once

#include "../Math/AoMath.h"

namespace ao
{
	class Camera
	{
	public:
		Camera(float width, float height);
		~Camera();

		void translate(float x, float y);
		void translate(const vec2& amount);
		void setZoom(float amount);
		void update();

		mat4 getCombinedMatrix();
		float getWidth() const { return m_Width; }
		float getHeight() const { return m_Height; }

	private:
		float m_Width, m_Height;
		mat4 m_Projection;
		mat4 m_View;
		mat4 m_InverseView;
		mat4 m_Zoom;
	};
}