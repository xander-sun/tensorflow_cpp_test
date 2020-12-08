cmake_minimum_required(VERSION 3.7)
#project(TF_CPP_DETECT)

set(CMAKE_CXX_STANDARD 11)
ADD_COMPILE_OPTIONS(-fPIC)

set(SOURCE_FILES_test test.cpp ../crow_all.h ../base64.cpp ../base64.h)
add_executable(test1 ${SOURCE_FILES_test})
#SET_TARGET_PROPERTIES(test PROPERTIES PREFIX "")
#set (CMAKE_CXX_FLAGS "'curl-config  --cflags --libs'")
# crow lib
#include_directories("/usr/local/include")

# OpenCV libs
set(OpenCV_DIR /usr/local/opencv2.4/share/OpenCV)
find_package(OpenCV 2.4 REQUIRED)
#set(OpenCV_DIR /usr/local/opencv3.4/share/OpenCV)
#find_package(OpenCV 3.4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(test1 ${OpenCV_LIBS})

# boost lib
find_package(Boost REQUIRED COMPONENTS system thread)
include_directories( ${Boost_INCLUDE_DIRS} )
target_link_libraries(test1 ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY})

# libcurl
find_package(curl REQUIRED)
include_directories(/usr/local/include)
target_link_libraries(test1 -L/usr/local/lib -lcurl)
#ADD_COMPILE_OPTIONS(curl-config --cc --cflags --libs)

# jsoncpp
set(jsoncpp_DIR /home/ys/workspace/devel_release/share/jsoncpp/cmake)
find_package(jsoncpp REQUIRED)
include_directories(/home/ys/workspace/devel_release/lib/)
target_link_libraries(test1 jsoncpp)

# pthread link
target_link_libraries(test1 -lpthread -lm)
# ==================== PATHS TO SPECIFY! ==================== #

# Eigen lib headers
#include_directories("/usr/local/include/eigen3")
#include_directories("/usr/local/include/google")

# TensorFlow headers
#include_directories("/usr/local/include/tf/")
#include_directories("/usr/local/include/tf/bazel-genfiles/")
#include_directories("/usr/local/include/tf/tensorflow/")
#include_directories("/usr/local/include/tf/third-party/")

# Link TensorFlow libs
#target_link_libraries(tf_detect_crow "/usr/local/lib/libtensorflow_cc.so")
#target_link_libraries(tf_detect_crow "/usr/local/lib/libtensorflow_framework.so")
