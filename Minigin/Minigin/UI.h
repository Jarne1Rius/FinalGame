#pragma once
#include "Singleton.h"
#include "TextRenderer.h"

namespace Rius
{
	class UI :public Singleton<UI>
	{
	public:
		friend  class Singleton<UI>;
		void Initialize();
		void Update();
		void Render();
		void Cleanup();
	private:
		TextRenderer* m_TextRenderer{};
		UI() = default;
	};
}
