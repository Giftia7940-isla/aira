// aira.cpp: 定义应用程序的入口点。
//

#include <thread>
#include <chrono>

#include "aira.h"
#include "logger/logger.h"

using namespace std;

int main()
{
	aira::Logger::ptr logger(new aira::Logger("server"));
	logger->addAppender(aira::LogAppender::ptr(new aira::ConsoleLogAppender));

	// 获取当前时间
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();

	// 计算程序从启动到现在的运行时间
	std::chrono::duration<uint64_t, std::micro> elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
	aira::LogEvent::ptr event(new aira::LogEvent(__FILE__, __LINE__, 1, 0, now.time_since_epoch().count(), elapsedTime.count(), "aira > <"));
	cout << "Hello CMake." << endl;
	return 0;
}
