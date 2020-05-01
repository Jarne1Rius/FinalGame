#pragma once
#include <string>
#include "Extra.h"
namespace Rius
{
	class Logger
	{
	public:
		Logger();
		static void LogInfo(std::string info);
		static void LogInfo(glm::vec2& position);
		static void LogInfo(Rectangle2D& rectangle);
		static void LogError(std::string info);
		static void LogError(glm::vec2& position);
		static void LogError(Rectangle2D& rectangle);
	private:
		static void LogInfo();
		static void LogError();
		static void LogTime();
		static HANDLE m_HConsole;
	};
}

