cmake_minimum_required(VERSION 3.0.2)
project(test_receive_images)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
        std_msgs
        cv_bridge
        image_transport
  message_generation
)

find_package(OpenCV 4 REQUIRED)

 generate_messages(
   DEPENDENCIES
   sensor_msgs  # Or other packages containing msgs
 )


catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp
        message_runtime
        sensor_msgs
        std_msgs
        cv_bridge
        image_transport
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)


#add_executable(receive_images src/receive_images.cpp)
#target_link_libraries(receive_images ${catkin_LIBRARIES} ${OpenCV_INCLUDE_DIRS})
#add_dependencies(receive_images beginner_tutorials_generate_messages_cpp)

add_executable(show_images src/show_images.cpp)
target_link_libraries(show_images ${catkin_LIBRARIES} ${OpenCV_INCLUDE_DIRS})

add_executable(show_images_merged src/show_images_merged.cpp)
target_link_libraries(show_images_merged ${catkin_LIBRARIES} ${OpenCV_INCLUDE_DIRS})

add_executable(image_publisher src/image_publisher.cpp)
target_link_libraries(image_publisher ${catkin_LIBRARIES} ${OpenCV_INCLUDE_DIRS})
