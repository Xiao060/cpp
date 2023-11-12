# cmake 的最小版本
cmake_minimum_required(VERSION 3.6)

# 设置 工程名
project (Server)

# 设置 可执行程序的输出路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 添加可执行文件
add_executable(Server 
    src/CloudiskServer.cc
    src/token.cc
    src/main.cc
) 

# 设置 头文件目录
target_include_directories(Server PRIVATE
    include
)

# 设置 链接库
target_link_libraries(Server PRIVATE 
    wfrest
    crypt
    crypto
)

