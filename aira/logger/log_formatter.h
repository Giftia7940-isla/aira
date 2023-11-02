#ifndef _AIRA_LOG_FORMATTER_H_
#define _AIRA_LOG_FORMATTER_H_

#include <fstream>
#include <vector>
#include <tuple>
#include <iostream>
#include <sstream>
#include <map>
#include <functional>
#include "log_base.h"

namespace aira 
{
	//日志具体输出的一部分
	class LogFmtItem
	{
	public:
		typedef std::shared_ptr<LogFmtItem> ptr;
		LogFmtItem(const std::string& fmt = "") {};
		virtual ~LogFmtItem() {};
		virtual void format(std::ostream& os, LogEvent::ptr event) = 0;
	};

	//文件名
	class FileLogFmtItem : public LogFmtItem
	{
	public:
		FileLogFmtItem(const std::string& fmt = "") {};
		void format(std::ostream& os, LogEvent::ptr event)override
		{
			os << event->getFile();
		}
	};

	//行数
	class LineLogFmtItem : public LogFmtItem
	{
	public:
		LineLogFmtItem(const std::string& fmt = "") {};
		void format(std::ostream& os, LogEvent::ptr event)override
		{
			os << event->getLine();
		}
	};

	//线程ID
	class ThreadIdLogFmtItem : public LogFmtItem
	{
	public:
		ThreadIdLogFmtItem(const std::string& fmt = "") {};
		void format(std::ostream& os, LogEvent::ptr event)override
		{
			os << event->getThreadId();
		}
	};

	//协程ID
	class FiberIdLogFmtItem : public LogFmtItem
	{
	public:
		FiberIdLogFmtItem(const std::string& fmt = "") {};
		void format(std::ostream& os, LogEvent::ptr event)override
		{
			os << event->getFiberId();
		}
	};

	//启动至今毫秒数
	class ElapseLogFmtItem : public LogFmtItem
	{
	public:
		ElapseLogFmtItem(const std::string& fmt = "") {};
		void format(std::ostream& os, LogEvent::ptr event)override
		{
			os << event->getElapse();
		}
	};

	//时间
	class TimeLogFmtItem : public LogFmtItem
	{
	public:
		TimeLogFmtItem(const std::string& format = "%Y:%m:%d %H:%M:%s")
			: m_format(format){}
		void format(std::ostream& os, LogEvent::ptr event)override
		{
			os << event->getTime();
		}
	private:
		std::string m_format;
	};

	//内容
	class ContentLogFmtItem : public LogFmtItem
	{
	public:
		ContentLogFmtItem(const std::string& fmt = "") {};
		void format(std::ostream& os, LogEvent::ptr event)override
		{
			os << event->getContent();
		}
	};

	class StringLogFmtItem : public LogFmtItem
	{
	public:
		StringLogFmtItem(const std::string& str) :m_string(str){}
		void format(std::ostream& os, LogEvent::ptr event)override
		{

			os << "\t";
		}
	private:
		std::string m_string;
	};

	class CRLogFmtItem : public LogFmtItem
	{
	public:
		CRLogFmtItem(const std::string& fmt = "") {};
		void format(std::ostream& os, LogEvent::ptr event)override
		{

			os << "\n";
		}
	};

	class TabLogFmtItem : public LogFmtItem
	{
	public:
		TabLogFmtItem(const std::string& fmt = "") {};
		void format(std::ostream& os, LogEvent::ptr event)override
		{
			
			os << "\t";
		}
	};

	//日志格式器
	class LogFormatter
	{
	public:
		typedef std::shared_ptr<LogFormatter> ptr;

		LogFormatter(const std::string& val) { m_pattern = val; init(); }
		std::string format(const std::string& loggerName, LogLevel::Level level, LogEvent::ptr event);
	private:

		std::string m_pattern;
		std::vector<LogFmtItem::ptr> m_items;
		void init();			//解析业务传入的输入格式	
		static std::map<std::string, std::function<LogFmtItem::ptr(const std::string& fmt)>> s_fmtMap;//创建字符和条目对应的Map
	};

}

#endif
