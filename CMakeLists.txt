# CMake 最低版本要求
cmake_minimum_required(VERSION 3.15)

# 项目名称
project(AD5293_Driver C)

# 设置 C 标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ==============================
# 添加 include 目录
# ==============================
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# ==============================
# AD5293 驱动库
# ==============================
file(GLOB AD5293_SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.c
)

add_library(AD5293 STATIC ${AD5293_SOURCES})

# ==============================
# 示例程序
# ==============================
file(GLOB EXAMPLE_SOURCES
    ${PROJECT_SOURCE_DIR}/example/*.c
)

add_executable(example ${EXAMPLE_SOURCES})

# 链接 AD5293 静态库
target_link_libraries(example PRIVATE AD5293)

# ==============================
# 可选：编译选项
# ==============================
# 例如开启优化，关闭调试信息
# target_compile_options(AD5293 PRIVATE -O2)
