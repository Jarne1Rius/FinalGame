#pragma once
#include <string>
#include "Extra.h"
namespace Rius
{
	class Logger final
	{
	public:
		Logger();
		static void LogInfo(std::string info);
		static void LogInfo(const glm::vec2& position);
		static void LogInfo(const Rectangle2D& rectangle);
		static void LogError(std::string info);
		static void LogError(const glm::vec2& position);
		static void LogError(const Rectangle2D& rectangle);
	private:
		static void LogInfo();
		static void LogError();
		static void LogTime();
		static HANDLE m_HConsole;
	};
}

