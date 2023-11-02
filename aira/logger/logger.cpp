#include "logger.h"

namespace aira
{
	Logger::Logger(const std::string& name)
		: m_name(name)
	{

	}

	Logger::~Logger()
	{
		m_appenders.clear();
	}

	void Logger::log(LogLevel::Level level, LogEvent::ptr event)
	{
		if (level >= m_lowestLevel)
		{
			for (auto& appender : m_appenders)
			{
				appender->log(level, event);
			}
		}
	}

	void Logger::debug(LogEvent::ptr event)
	{
		log(LogLevel::Level::DEBUG, event);
	}

	void Logger::info(LogEvent::ptr event)
	{
		log(LogLevel::Level::INFO, event);
	}

	void Logger::warn(LogEvent::ptr event)
	{
		log(LogLevel::Level::WARN, event);
	}

	void Logger::error(LogEvent::ptr event)
	{
		log(LogLevel::Level::ERROR, event);
	}

	void Logger::fatal(LogEvent::ptr event)
	{
		log(LogLevel::Level::FATAL, event);
	}

	void Logger::setLowestLevel(LogLevel::Level val)
	{
		m_lowestLevel = val;
	}

	LogLevel::Level Logger::getLowestLevel()
	{
		return m_lowestLevel;
	}

	bool Logger::addAppender(LogAppender::ptr appender)
	{
		if (appender == nullptr) { return false; }			//指针为空
		for (auto it = m_appenders.begin(); it != m_appenders.end(); ++it)
		{
			if (*it == appender) return false;				//已经添加
		}
		m_appenders.push_back(appender);
		return true;
	}

	void Logger::delAppender(LogAppender::ptr appender)
	{
		for (auto it = m_appenders.begin(); it != m_appenders.end(); ++it)
		{
			if (*it == appender)
			{
				m_appenders.erase(it);
				break;
			}
		}
	}

}

