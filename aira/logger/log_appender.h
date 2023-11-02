#ifndef _AIRA_LOG_APPENDER_H_
#define _AIRA_LOG_APPENDER_H_

#include "log_base.h"

namespace aira {

	class LogAppender {
	public:
		typedef std::shared_ptr<LogAppender> ptr;

		virtual ~LogAppender() {};
		virtual void log(LogLevel::Level level, LogEvent::ptr event) = 0;
	private:

	};

}


#endif
