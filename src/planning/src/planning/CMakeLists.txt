
# 生成链接库
add_library(planning
    planning.cpp
    )
target_link_libraries(planning
   file_tool
   )
add_dependencies(planning
    car_msgs_gencpp
)   