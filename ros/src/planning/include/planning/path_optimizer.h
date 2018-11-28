#pragma once

#include <Eigen/Dense>
#include <vector>
#include <iostream>
#include <math.h>
#include "car_msgs/trajectory.h"
#include "car_msgs/trajectory_point.h"
#include "planning/Interpolating.h"
#include "planning/Fitting.h"
#include "planning/car_model.h"
#include "yaml-cpp/yaml.h"

class path_optimizer_Conf{
public:
    float step_t;
    float planning_t;
    float keep_t;
    float aim_speed;
};

class path_optimizer{
public:
    path_optimizer(YAML::Node yaml_conf);

    Spline_Out* get_refrenceline(const car_msgs::trajectory& trajectory_in, car_msgs::trajectory& trajectory_out);
    void get_sampling_line(const Car_State_SL& status_sl, const Spline_Out* refrenceline_Sp, car_msgs::trajectory& trajectory_out);

    void process(const Car_State_SL& status_sl, const Spline_Out* refrenceline_Sp, car_msgs::trajectory& trajectory_out);
private:
    /******path_planning******/
    //指定两个SL坐标系中的点进行planning_t时间的规划
    //起点中的所有数据用到，终点的s，没有用到会被时间覆盖
    void path_planning(const Car_State_SL& start_sl,const Car_State_SL& end_sl,const float planning_t,
 const Spline_Out* refrenceline_Sp, car_msgs::trajectory& trajectory_out,
 int start_index=0);
    /********配置参数************/
    path_optimizer_Conf conf;
    /**********模块************/
    Interpolating* interpolating;
    /*********车体参数************/
    VectorXf QP4; //速度规划
    VectorXf QP5; //位置规划
    Car_State_SL car_last_sl;
};