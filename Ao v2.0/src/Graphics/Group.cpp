#include "Group.h"
#include "Renderer2D.h"

namespace ao
{
	Group::Group() : Renderable2D()
	{
	}

	Group::~Group()
	{
	}

	void Group::add(Renderable2D* child)
	{
		m_Children.push_back(child);
	}

	void Group::submit(Renderer2D* renderer)
	{
		renderer->push(m_Transformation);

		for (Renderable2D* renderable : m_Children)
			renderable->submit(renderer);

		renderer->pop();
	}
}