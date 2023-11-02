#include "log_base.h"

namespace aira 
{
	const char* LogLevel::toString(LogLevel::Level level)
	{
		switch (level) 
		{

#define XX(name)	\
case LogLevel::name:	\
return #name;	\
break;	
			XX(DEBUG);
			XX(INFO);
			XX(WARN);
			XX(ERROR);
			XX(FATAL);
#undef XX
		default: return "UNKOWN";
		}
		return  "UNKOWN";
	}
}

