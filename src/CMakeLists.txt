cmake_minimum_required(VERSION 3.27)
project(LeetCode)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES "02.linkedList/linked_list.cpp" "06.binary_tree/binary_tree.cpp"
        "06.binary_tree/n_ary_tree.cpp")

# 使用文件通配符查找符合条件的 .cpp 文件
file(GLOB CPP_SOURCES "./*/day*.cpp")

# 遍历所有的 .cpp 文件，为每个文件创建可执行文件
foreach(CPP_FILE ${CPP_SOURCES})
    # 获取文件名（不包含扩展名）
    get_filename_component(FILE_NAME ${CPP_FILE} NAME_WE)

    # 添加可执行文件
    add_executable(${FILE_NAME} ${SOURCES} ${CPP_FILE})
endforeach()
