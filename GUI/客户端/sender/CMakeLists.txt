cmake_minimum_required(VERSION 3.12)
project(test2)

set(CMAKE_CXX_STANDARD 11)

#设置工程包含当前目录，非必需
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

#设置自动生成moc文件，一定要设置
set(CMAKE_AUTOMOC ON)

set (CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.12.0/lib/cmake")
#查找需要的Qt库文件，最好每一个库都要写，Qt也会根据依赖关系自动添加
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)

#查找当前文件夹中的所有源代码文件，也可以通过Set命令将所有文件设置为一个变量
FILE(GLOB SRC_FILES "./*.cxx")
#同理，查找当前文件夹中所有的头文件
FILE(GLOB HEAD_FILES "./*.h")
#同理，查找当前文件夹中所有的ui文件
FILE(GLOB UI_FILES "./*.ui")

#通过Ui文件生成对应的头文件，一定要添加
qt5_wrap_ui(WRAP_FILES ${UI_FILES})

#将ui文件和生成文件整理在一个文件夹中，非必须
source_group("Ui" FILES ${UI_FILES} ${WRAP_FILES} )

add_executable(test2 main.cpp MyWidget.cpp MyWidget.h ListWidget.cpp ListWidget.h RegisterWidget.cpp RegisterWidget.h InputIpWidget.cpp InputIpWidget.h client.cpp client.h ChatWidget.cpp ChatWidget.h)

#添加Qt5依赖项
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui)