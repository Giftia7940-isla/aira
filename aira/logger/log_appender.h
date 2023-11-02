#ifndef _AIRA_LOG_APPENDER_H_
#define _AIRA_LOG_APPENDER_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include "log_formatter.h"

namespace aira 
{
	//��־�����
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
		LogLevel::Level m_lowestLevel;			//��ӡ��־����͵ȼ�
		LogFormatter::ptr m_formatter;			//��־��ʽ
	private:

	};

	//���������̨����־
	class ConsoleLogAppender : public LogAppender
	{
	public:
		typedef std::shared_ptr<ConsoleLogAppender> ptr;
		//ConsoleLogAppender();
		void log(const std::string& loggerName, LogLevel::Level level, LogEvent::ptr event) override;
	private:
	};

	//������ļ�����־
	class FileLogAppender : public LogAppender
	{
	public:
		typedef std::shared_ptr<FileLogAppender> ptr;
		FileLogAppender(std::string name, std::ostream m_fileStream);
		void log(const std::string& loggerName, LogLevel::Level level, LogEvent::ptr event) override;
		bool reopen();  //���´��ļ����򿪳ɹ�����true
	private:
		std::string m_name;
		std::ofstream m_fileStream;
	};

}


#endif
