#ifndef _AIRA_LOG_APPENDER_H_
#define _AIRA_LOG_APPENDER_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include "log_formatter.h"

namespace aira 
{
	//日志输出地
	class LogAppender 
	{
	public:
		typedef std::shared_ptr<LogAppender> ptr;

		virtual ~LogAppender() {};
		virtual void log(const std::string& loggerName, LogLevel::Level level, LogEvent::ptr event) = 0;

		void setLevel(LogLevel::Level val) { m_lowestLevel = val; }
		LogLevel::Level getLevel() { return m_lowestLevel; }
		void setFormatter(LogFormatter::ptr val) { m_formatter = val; }
		LogFormatter::ptr getFormatter() { return m_formatter; }
	protected:
		LogLevel::Level m_lowestLevel;			//打印日志的最低等级
		LogFormatter::ptr m_formatter;			//日志格式
	private:

	};

	//输出到控制台的日志
	class ConsoleLogAppender : public LogAppender
	{
	public:
		typedef std::shared_ptr<ConsoleLogAppender> ptr;
		//ConsoleLogAppender();
		void log(const std::string& loggerName, LogLevel::Level level, LogEvent::ptr event) override;
	private:
	};

	//输出到文件的日志
	class FileLogAppender : public LogAppender
	{
	public:
		typedef std::shared_ptr<FileLogAppender> ptr;
		FileLogAppender(std::string name, std::ostream m_fileStream);
		void log(const std::string& loggerName, LogLevel::Level level, LogEvent::ptr event) override;
		bool reopen();  //重新打开文件，打开成功返回true
	private:
		std::string m_name;
		std::ofstream m_fileStream;
	};

}


#endif
