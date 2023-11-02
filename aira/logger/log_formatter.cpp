#include "log_formatter.h"

namespace aira
{

	std::string LogFormatter::format(const std::string& loggerName, LogLevel::Level level, LogEvent::ptr event)
	{
		//loggerName��˵

		std::stringstream ss;
		ss << LogLevel::toString(level) << ":";
		for (auto& i : m_items)
		{
			i->format(ss, event);
		}
		return ss.str();
	}

	void LogFormatter::init()
	{
		//%% %xxx %xxx{xxx}
		//����
		//%m -- ��Ϣ��
		//%p -- level
		//%r -- �������ʱ��
		//%c -- ��־����
		//%t -- �߳�id
		//%n -- ����
		//%f -- �ļ���
		//%l -- �к�
		//%T -- �Ʊ��
		//%d -- ʱ��

		std::vector<std::string> items;

		std::string tstr;

		size_t i = 0;
		while (i < m_pattern.size())
		{
			if (m_pattern[i] == '%')            //�����û������%
			{
				if (!tstr.empty())
				{
					items.push_back(tstr);
					tstr.clear();
				}
				size_t n = i + 1;                    //���ƣ���������¼%��ֻ��¼%����ʲô�����������%d��һ����¼{}��ĸ�ʽ
				if (m_pattern[n] == '%')                     //˵����Ϊ%%
				{
					tstr.append(1, '%');
					i = n;
					continue;
				}
				else if (m_pattern[n] == 'd' && m_pattern[n + 1] == '{')
				{
					n = n + 2;                      //���d��{
					while (n < m_pattern.size() && m_pattern[n] != '}')
					{
						tstr.append(1, m_pattern[n]);
						++n;
					}
					items.push_back(tstr);
					tstr.clear();
					i = n;
					continue;
				}
				while (n < m_pattern.size())          //��%��d֮���
				{
					if (m_pattern[n] == ' ' || m_pattern[n] == '%')
					{
						items.push_back(tstr);
						tstr.clear();
						break;
					}
					tstr.append(1, m_pattern[n]);
					++n;
				}
				i = n;
			}
			else
			{
				tstr.append(1, m_pattern[i]);
				++i;
			}
		}

		//std::vector<std::tuple<std::string, std::string, int>> vec;
		//std::string nstr;
		//for (size_t i = 0; i < m_pattern.size(); ++i)
		//{
		//	if (m_pattern[i] != '%')
		//	{
		//		nstr.append(1, m_pattern[i]);
		//		continue;
		//	}

		//	if ((i + 1) < m_pattern.size())
		//	{
		//		if (m_pattern[i + 1] == '%')
		//		{
		//			nstr.append(1, '%');
		//			continue;
		//		}
		//	}

		//	size_t n = i + 1;
		//	int fmt_status = 0;			//0��ʼλ��1�ҵ�{��2�ҵ�}����
		//	size_t fmt_begin = 0;

		//	std::string str;
		//	std::string fmt;
		//	while (n < m_pattern.size())
		//	{
		//		if (!isalpha(m_pattern[n]) && m_pattern[n] != '{' && m_pattern[n] != '}') break;
		//		if (fmt_status == 0)
		//		{
		//			if (m_pattern[n] == '{')
		//			{
		//				str = m_pattern.substr(i + 1, n - i - 1);
		//				fmt_status = 1;
		//				fmt_begin = n;
		//				++n;
		//				continue;
		//			}
		//		}
		//		if (fmt_status == 1)
		//		{
		//			if (m_pattern[n] == '}')
		//			{
		//				fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
		//				fmt_status = 2;
		//				break;
		//			}
		//		}
		//		++n;
		//	}

		//	if (fmt_status == 0)
		//	{
		//		if (!nstr.empty())
		//		{
		//			vec.push_back(std::make_tuple(nstr, "", 0));
		//			nstr.clear();
		//		}
		//		str = m_pattern.substr(i + 1, n - i - 1);
		//		vec.push_back(std::make_tuple(str, fmt, 1));
		//		i = n;
		//	}
		//	else if (fmt_status == 1)
		//	{
		//		std::cout << "pattern parse error: " << m_pattern << " - " << m_pattern.substr(i) << std::endl;
		//		vec.push_back(std::make_tuple("<<parttern_error>>", fmt, 0));
		//	}
		//	else if (fmt_status == 2)
		//	{
		//		if (!nstr.empty())
		//		{
		//			vec.push_back(std::make_tuple(nstr, "", 0));
		//			nstr.clear();
		//		}
		//		vec.push_back(std::make_tuple(str, fmt, 1));
		//		i = n;
		//	}
		//}

		//for (auto& i : vec)
		//{
		//	if (std::get<2>(i) == 0)
		//	{
		//		m_items.push_back(LogFmtItem::ptr(std::make_shared<StringLogFmtItem>(std::get<0>(i))));
		//	}
		//	else
		//	{
		//		auto it = s_fmtMap.find(std::get<0>(i));
		//		if (it == s_fmtMap.end())
		//		{
		//			m_items.push_back(LogFmtItem::ptr(std::make_shared<StringLogFmtItem>("<<error_format %" + std::get<0>(i) + ">>")));
		//		}
		//		else
		//		{
		//			m_items.push_back(it->second(std::get<1>(i)));
		//		}
		//	}
		//	std::cout << '(' << std::get<0>(i) << ") - (" << std::get<1>(i) << ") - (" << std::get<2>(i) << ')' << std::endl;
		//}

	}

	//�����ַ�����Ŀ��Ӧ��Map
		std::map<std::string, std::function<LogFmtItem::ptr(const std::string& fmt)>> LogFormatter::s_fmtMap =
		{
	#define XX(str, className) \
	{#str, [](const std::string& fmt) {return LogFmtItem::ptr(std::make_shared<className>(fmt)); }}

			XX(m, ContentLogFmtItem),
			XX(r, ElapseLogFmtItem),
			XX(t, ThreadIdLogFmtItem),
			XX(l, LineLogFmtItem),
			XX(f, FileLogFmtItem),
			XX(F, FiberIdLogFmtItem),
			XX(T, TabLogFmtItem),
			XX(n, CRLogFmtItem),
#undef XX
		};
}