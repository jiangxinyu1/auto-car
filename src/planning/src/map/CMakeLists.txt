
# 生成链接库
add_library(map
            A_star.cpp
            Image.cpp
            road.cpp
            map_convert.cpp)
add_dependencies(map
    car_msgs_gencpp
)   