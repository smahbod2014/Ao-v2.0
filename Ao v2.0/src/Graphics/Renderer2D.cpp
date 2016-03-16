#include "Renderer2D.h"

namespace ao
{
	Renderer2D::Renderer2D()
	{
		m_TransformationStack.push_back(mat4::identity());
		m_TransformationBack = &m_TransformationStack.back();
	}

	void Renderer2D::push(const mat4& matrix)
	{
		m_TransformationStack.push_back(*m_TransformationBack * matrix);
		m_TransformationBack = &m_TransformationStack.back();
	}

	void Renderer2D::pop()
	{
		if (m_TransformationStack.size() > 1)
		{
			m_TransformationStack.pop_back();
			m_TransformationBack = &m_TransformationStack.back();
		}
	}
}