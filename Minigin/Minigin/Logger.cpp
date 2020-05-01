#include "MiniginPCH.h"
#include "Logger.h"
#include <ctime>

HANDLE Rius::Logger::m_HConsole = GetStdHandle(STD_OUTPUT_HANDLE);
Rius::Logger::Logger()
{
}

void Rius::Logger::LogInfo(std::string info)
{
	LogInfo();
	std::cout << info << "\n";
}

void Rius::Logger::LogInfo(glm::vec2& position)
{
	LogInfo();
	std::cout << "X: " << position.x << " - Y: " << position.y << "\n";
}

void Rius::Logger::LogInfo(Rectangle2D& rectangle)
{
	LogInfo();
	std::cout << "X: " << rectangle.pos.x << " - Y: " << rectangle.pos.y << " - Width: " << rectangle.width<< " - Height: " << rectangle.height << "\n";
}

void Rius::Logger::LogError(std::string info)
{
	LogError();
	std::cout << info << "\n";
}

void Rius::Logger::LogError(Rectangle2D& rectangle)
{
	LogError();
	std::cout << "X: " << rectangle.pos.x << " - Y: " << rectangle.pos.y << " - Width: " << rectangle.width << " - Height: " << rectangle.height << "\n";
}

void Rius::Logger::LogError(glm::vec2& position)
{
	LogError();
	std::cout << "X: " << position.x << " - Y: " << position.y << "\n";
}

void Rius::Logger::LogInfo()
{

	SetConsoleTextAttribute(m_HConsole, 7);
	LogTime();
	std::cout << "-INFO: ";
}

void Rius::Logger::LogError()
{
	SetConsoleTextAttribute(m_HConsole, 4);
	LogTime();
	//system("Color 1A");
	std::cout << "-ERROR: ";
}

void Rius::Logger::LogTime()
{
	time_t now = time(0);
	tm ltm;
	localtime_s(&ltm,&now);
	std::cout << "[" << 1 + ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << "]";
}
