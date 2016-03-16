#pragma once

#include "Renderable2D.h"

namespace ao
{
	class Renderer;

	class Group : public Renderable2D
	{
	public:
		Group();
		virtual ~Group();

		void add(Renderable2D* child);
		virtual void submit(Renderer2D* renderer) override;

		const std::vector<Renderable2D*>& getChildren() { return m_Children; }
	private:
		std::vector<Renderable2D*> m_Children;
	};
}