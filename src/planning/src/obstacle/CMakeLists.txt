
# 生成链接库
add_library(obstacle
    obstacle.cpp
    obstacle_list.cpp
    obstacle_method.cpp)
add_dependencies(obstacle
    car_msgs_gencpp
)   