# CMakeList.txt: aira 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 将源代码添加到此项目的可执行文件。
add_executable (aira "aira.cpp" "aira.h" "logger/logger.h" "logger/logger.cpp" "logger/log_appender.h" "logger/log_appender.cpp" "logger/log_base.h" "logger/log_base.cpp" "base/base_define.h" "logger/log_formatter.h" "logger/log_formatter.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET aira PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。

# 添加base文件夹
target_include_directories(aira PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/base")

# 添加logger文件夹
target_include_directories(aira PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/logger")