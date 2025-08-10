//
// Created by Steins_Xin on 2025/8/10.
//

#ifndef COLLABORATIVE_ARM_MOTOR_INTERFACE_H
#define COLLABORATIVE_ARM_MOTOR_INTERFACE_H

#include "can.h"
#include <stdint.h>

/**
    使用示例
    MotorDevice shoulder_motor = {
        .name = "shoulder",
        .type = MOTOR_DM,
        .can_id = 0x001,
        .can_bus = &hcan1,
        .ops = &dm_motor_ops,
        .context = NULL,
    };
    Motor_SpeedControl(&shoulder_motor, 100);
*/

#define Motor_GetMultiTurnAngle(m)          ((m)->ops->get_angle(m))
#define Motor_PositionControl(m, a, s)      ((m)->ops->position_control(m, a, s))
#define Motor_SpeedControl(m, s)            ((m)->ops->speed_control(m, s))
#define Motor_TorqueControl(m, t)          ((m)->ops->torque_control(m, t))
#define Motor_Stop(m)                       ((m)->ops->stop(m))
#define Motor_Enable(m)                     ((m)->ops->enable(m))
#define Motor_Disable(m)                    ((m)->ops->disable(m))

typedef enum {
    MOTOR_DM,
    // 后续可以扩展：MOTOR_XXX
} MotorType;

/**
 * @brief 电机模式枚举
 */
typedef enum {
    UNKNOWN_MODE,       /* 未知模式 */
    SPEED_MODE,         /* 速度模式 */
    POS_MODE,           /* 位置模式 */
    TOR_MODE,           /* 力矩模式 */
} motor_mode_t;

// 电机运行状态枚举（如运行、停止、关闭）
typedef enum {
    MOTOR_STATE_UNKNOWN = 0,
    MOTOR_STATE_RUNNING,
    MOTOR_STATE_STOPPED,
    MOTOR_STATE_DISABLED
} motor_run_state_t;

struct MotorDevice;

// 定义操作函数接口（行为接口）
typedef struct {
    void (*get_angle)(struct MotorDevice *motor);
    void (*speed_control)(struct MotorDevice *motor, float speed);
    void (*position_control)(struct MotorDevice *motor, float angleControl, uint16_t maxSpeed);
    void (*torque_control)(struct MotorDevice *motor, int16_t torque);
    void (*stop)(struct MotorDevice *motor);
    void (*enable)(struct MotorDevice *motor);
    void (*disable)(struct MotorDevice *motor);

    // 新增反馈处理函数指针，按命令区分
    void (*handle_get_angle_feedback)(struct MotorDevice *motor, const uint8_t *data, uint8_t len);
    void (*handle_speed_control_feedback)(struct MotorDevice *motor, const uint8_t *data, uint8_t len);
    void (*handle_position_control_feedback)(struct MotorDevice *motor, const uint8_t *data, uint8_t len);
    void (*handle_torque_control_feedback)(struct MotorDevice *motor, const uint8_t *data, uint8_t len);
    void (*handle_stop_feedback)(struct MotorDevice *motor, const uint8_t *data, uint8_t len);
    void (*handle_enable_feedback)(struct MotorDevice *motor, const uint8_t *data, uint8_t len);
    void (*handle_disable_feedback)(struct MotorDevice *motor, const uint8_t *data, uint8_t len);
} MotorOps;

// 电机状态对象定义
typedef struct MotorStatus {
    // ---- 通用运行信息 ----
    uint32_t last_master_cmd;        // 主控命令时间戳
    uint32_t last_motor_resp;        // 电机响应时间戳

    motor_mode_t mode;               // 控制模式（角度、速度等）
    motor_run_state_t run_state;     // 运行状态（运行/停止/关闭）

    // ---- 电机反馈数据 ----
    double current_angle_deg;        // 电机角度
    uint16_t encoder;                // 电机编码器
    int32_t current_speed_rpm;       // 电机速度
    int16_t current_torque;          // 电机力矩
    int16_t current_iq;              // 电机电流
    int16_t temperature_celsius;     // 电机温度
    int16_t voltage;                 // 电机电压

    // ---- 电源控制 ----
    GPIO_TypeDef* mos_port;          // MOS 控制端口
    uint16_t mos_pin;                // MOS 控制引脚

    // ---- 扩展字段（可选）----
    uint8_t fault_code;              // 故障码
    uint8_t warning_code;            // 警告码
} MotorStatus;

// 电机设备对象定义
typedef struct MotorDevice {
    const char *name;                 // 电机角色名，如 "left_shoulder"
    MotorType type;                   // 电机类型
    uint32_t can_id;                  // 电机对应的 CAN ID
    CAN_HandleTypeDef *can_bus;       // CAN 句柄
    const MotorOps *ops;              // 行为接口集（函数指针表）
    MotorStatus status;

    // 可选字段（便于扩展）
    void *context;                    // 用户上下文，指向配置或状态结构体
} MotorDevice;

#endif //COLLABORATIVE_ARM_MOTOR_INTERFACE_H
