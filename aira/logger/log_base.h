#ifndef _AIRA_LOG_BASE_H_
#define _AIRA_LOG_BASE_H_

#include <stdio.h>
#include <string>
#include <fstream>
#include "base_define.h"

namespace aira {

	//��־�ȼ�
	class LogLevel {
	public:
		enum Level {
			DEBUG = 1,
			INFO = 2,
			WARN = 3,
			ERROR = 4,
			FATAL = 5
		};
		//ת�ַ���
		const char* toString(LogLevel::Level level);
	};

	//��־�¼�
	class LogEvent {
	public:
		typedef std::shared_ptr<LogEvent> ptr;

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

	class LogFormatter {
	public:
		typedef std::shared_ptr<LogFormatter> ptr;

		std::string format(LogLevel::Level level, LogEvent::ptr event);
	private:
	};

}
#endif
