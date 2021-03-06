cmake_minimum_required(VERSION 3.7)
#project(TF_CPP_DETECT)

set(CMAKE_CXX_STANDARD 11)
ADD_COMPILE_OPTIONS(-fPIC)

set(SOURCE_FILES detect.cpp main.cpp base64.cpp base64.h)
add_executable(tf_detect_crow ${SOURCE_FILES})
SET_TARGET_PROPERTIES(tf_detect_crow PROPERTIES PREFIX "")

# crow lib
#include_directories("/usr/local/include")

# OpenCV libs
set(OpenCV_DIR /usr/local/opencv3.4/share/OpenCV)
find_package(OpenCV 3.4 REQUIRED)
#set(OpenCV_DIR /usr/local/opencv3.4/share/OpenCV)
#find_package(OpenCV 3.4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(tf_detect_crow ${OpenCV_LIBS})

# boost lib
find_package(Boost REQUIRED COMPONENTS system thread)
include_directories( ${Boost_INCLUDE_DIRS} )
target_link_libraries(tf_detect_crow ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY})

# pthread link
target_link_libraries(tf_detect_crow -lpthread -lm)
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

# ==================== PATHS TO SPECIFY! ==================== #

# Eigen lib headers
include_directories("/home/ys/tensorflow_test/include/eigen3")
#include_directories("/usr/include/absl")

# TensorFlow headers
include_directories("/home/ys/tensorflow_test/include")
include_directories("/home/ys/tensorflow_test/include/tensorflow")
include_directories("/home/ys/tensorflow_test/include/google")
include_directories("/home/ys/tensorflow_test/include/third-party")
#include_directories("/home/ys/")
# Link TensorFlow libs

link_directories("/home/ys/tensorflow_test/lib")
target_link_libraries(tf_detect_crow tensorflow_cc)
target_link_libraries(tf_detect_crow tensorflow_framework)
#target_link_libraries(tf_detect "/usr/lib/libabsl.a")
