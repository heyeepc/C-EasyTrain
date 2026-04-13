cmake_minimum_required(VERSION 3.10)
project(C_EasyTrain)

# 设置 C 语言标准
set(CMAKE_C_STANDARD 11)

# 将所有相关的源文件和头文件都写在这里
# 这样链接器就能找到 Traininfo 等函数的实现了
add_executable(C_EasyTrain
        main.c
        train_manager.c
        book_manager.c
        model.h
)