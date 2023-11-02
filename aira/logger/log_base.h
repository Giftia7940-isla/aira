#ifndef _AIRA_LOG_BASE_H_
#define _AIRA_LOG_BASE_H_

#include <string>
#include <memory>
#include "base_define.h"

namespace aira 
{

	//��־�ȼ�
	class LogLevel 
	{
	public:
		enum Level 
		{
			DEBUG = 1,
			INFO = 2,
			WARN = 3,
			ERROR = 4,
			FATAL = 5
		};
		//ת�ַ���
		static const char* toString(LogLevel::Level level);
	};

	//��־�¼�
	class LogEvent 
	{
	public:
		typedef std::shared_ptr<LogEvent> ptr;
		LogEvent(const char* file, uint32_t line, uint32_t threadId, uint32_t fiberId
			, uint64_t time, uint64_t elapse, std::string content)
			:m_file(file),
			m_line(line),
			m_threadId(threadId),
			m_fiberId(fiberId),
			m_time(time),
			m_elapse(elapse),
			m_content(content)
		{

		}

		const char* getFile() const { return m_file; }
		uint32_t getLine() const { return m_line; }
		uint32_t getThreadId() const { return m_threadId; }
		uint32_t getFiberId() const { return m_fiberId; }
		uint64_t getTime() const { return m_time; }
		uint64_t getElapse() const { return m_elapse; }
		std::string getContent() const { return m_content; }
	private:
		const char* m_file = nullptr;	//�ļ���
		uint32_t m_line = 0;			//����
		uint32_t m_threadId = 0;		//�߳�ID
		uint32_t m_fiberId = 0;			//Э��ID
		uint32_t m_elapse = 0;			//�������������ڵĺ�����
		uint64_t m_time = 0;			//ʱ��
		std::string m_content;			//����
	};
}
#endif
