
#include <gflags/gflags.h>
#include <glog/logging.h>
#include "common/base/global_gflags/global_gflags.h"
#include "common/base/file_path/file_path.h"
#include "planning/src/common/planning_gflags.h"
#include "planning/common.h"
#include "planning/planning.h"

#define PLANNING_CONF_DIR "src/planning/planning_conf.yaml"

bool DEBUG = 0;
using autocar::common::FilePathTool;
int main(int argc, char **argv)
{
    google::InitGoogleLogging(argv[0]);
    google::ParseCommandLineFlags(&argc, &argv, true);
    ROS_INFO("PLANNING start!!!!!");
    LOG(INFO) << "INFO　PLANNING start!!!!!";
    LOG(ERROR) << "ERROR　PLANNING start!!!!!";
    cout << "FLAGS_log_dir:" << FLAGS_log_dir << endl;
    cout << "FLAGS_test_flag_1:" << FLAGS_test_flag_1 << endl;
    // //判断是否为debug模式
    // Common::debug_check();

    /* code for main function */
    ros::init(argc, argv, "planning");
    ros::NodeHandle car_planning_NodeHandle;

    /*planning模块初始化*/
    Car_Planning planning(YAML::LoadFile(FLAGS_planning_conf_path));
    debugger = new Debugger();

    /*订阅*/
    planning.localization_subscriber =
        car_planning_NodeHandle.subscribe("localization_topic", 1, &Car_Planning::localization_callback, &planning);
    planning.chassis_subscriber =
        car_planning_NodeHandle.subscribe("chassis_topic", 1, &Car_Planning::chassis_callback, &planning);
    planning.obstacle_subscriber =
        car_planning_NodeHandle.subscribe("obstacle_topic", 1, &Car_Planning::obstacle_callback, &planning);
    /*发布*/
    planning.refrenceline_publisher =
        car_planning_NodeHandle.advertise<car_msgs::trajectory>("refrenceline_topic", 1000);
    planning.trajectory_publisher =
        car_planning_NodeHandle.advertise<car_msgs::trajectory>("trajectory_topic", 1000);

    //debugger
    debugger->set_NodeHandle(&car_planning_NodeHandle);

    //planning_init
    planning.Init();
    // 创建ros定时器
    ros::Timer cycle_timer;
    if (planning.conf.mode == "send")
    {
        cycle_timer = car_planning_NodeHandle.createTimer(ros::Duration(planning.conf.period), &Car_Planning::OnTimer, &planning);
    }
    ros::spin();

    return 0;
}
