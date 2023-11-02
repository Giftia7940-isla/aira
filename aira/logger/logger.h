#ifndef _AIRA_LOGGER_H_
#define _AIRA_LOGGER_H_

#include <list>
#include "log_base.h"
#include "log_appender.h"

namespace aira 
{

	//��־��
	class Logger {
	public:
		Logger(const std::string& name);
		~Logger();

		void log(LogLevel::Level  level, LogEvent::ptr event);

		void debug(LogEvent::ptr event);
		void info(LogEvent::ptr event);
		void warn(LogEvent::ptr event);
		void error(LogEvent::ptr event);
		void fatal(LogEvent::ptr event);

		void setLowestLevel(LogLevel::Level val);
		LogLevel::Level getLowestLevel();

		bool addAppender(LogAppender::ptr appender);		//���Appender
		void delAppender(LogAppender::ptr appender);		//ɾ��Appender
	private:

		std::string m_name;									//��־����
		LogLevel::Level m_lowestLevel;						//����ܽ��ܵ���־����
		std::list<LogAppender::ptr> m_appenders;			//Appender����
	};

}

#endif
