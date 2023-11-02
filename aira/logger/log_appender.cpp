#include "log_appender.h"

namespace aira
{
	void ConsoleLogAppender::log(const std::string& loggerName, LogLevel::Level level, LogEvent::ptr event)
	{
		if (level >= m_lowestLevel)
		{
			std::cout << m_formatter->format(loggerName, level, event);
		}
	}

	FileLogAppender::FileLogAppender(std::string name, std::ostream m_fileStream)
	{

	}

	void FileLogAppender::log(const std::string& loggerName, LogLevel::Level level, LogEvent::ptr event)
	{
		if (level >= m_lowestLevel)
		{
			m_fileStream << m_formatter->format(loggerName, level, event);
		}
	}

	bool FileLogAppender::reopen()
	{
		if (m_fileStream)
		{
			m_fileStream.close();
		}
		m_fileStream.open(m_name);
		return !!m_fileStream;          //转换为真正的bool
	}
}
