//
// Created by Steins_Xin on 2025/8/10.
//

#include "motor_interface.h"
#include "driver/motor_drive_dm.h"


// ======================== 电机发送处理 ========================
static void motor_dm_get_angle(MotorDevice *motor) {
    DM_GetMultiTurnAngle(motor->can_bus, motor->can_id);
}

static void motor_dm_speed_control(MotorDevice *motor, float speed) {
    DM_SpeedControl(motor->can_bus, motor->can_id, speed);
}

static void motor_dm_position_control(MotorDevice *motor, float angleControl, uint16_t maxSpeed) {
    DM_PositionControlMulti(motor->can_bus, motor->can_id, angleControl, maxSpeed);
}

static void motor_dm_torque_control(MotorDevice *motor, int16_t torque) {
    DM_TorqueControl(motor->can_bus, motor->can_id, torque);
}

static void motor_dm_stop(MotorDevice *motor) {
    DM_StopMotor(motor->can_bus, motor->can_id);
}

static void motor_dm_enable(MotorDevice *motor) {
    DM_EnableMotor(motor->can_bus, motor->can_id);
}

static void motor_dm_disable(MotorDevice *motor) {
    DM_DisableMotor(motor->can_bus, motor->can_id);
}

// ======================== 电机回复处理 ========================
static void motor_dm_get_angle_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    DM_HandleMultiTurnAngleFeedback(motor, data, len);
}

static void motor_dm_speed_control_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    DM_HandleSpeedControlFeedback(motor, data, len);
}

static void motor_dm_position_control_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    DM_HandlePositionControlMultiFeedback(motor, data, len);
}

static void motor_dm_torque_control_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    DM_HandleTorqueControlFeedback(motor, data, len);
}

static void motor_dm_stop_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    DM_HandleStopMotorFeedback(motor, data, len);
}

static void motor_dm_enable_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    DM_HandleEnableMotorFeedback(motor, data, len);
}

static void motor_dm_disable_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    DM_HandleDisableMotorFeedback(motor, data, len);
}


// 定义 DM 电机的操作表
const MotorOps DMMotorOps = {
        .get_angle = motor_dm_get_angle,
        .speed_control = motor_dm_speed_control,
        .position_control = motor_dm_position_control,
        .torque_control = motor_dm_torque_control,
        .stop = motor_dm_stop,
        .enable = motor_dm_enable,
        .disable = motor_dm_disable,

        .handle_get_angle_feedback = motor_dm_get_angle_feedback,
        .handle_speed_control_feedback = motor_dm_speed_control_feedback,
        .handle_position_control_feedback = motor_dm_position_control_feedback,
        .handle_torque_control_feedback = motor_dm_torque_control_feedback,
        .handle_stop_feedback = motor_dm_stop_feedback,
        .handle_enable_feedback = motor_dm_enable_feedback,
        .handle_disable_feedback = motor_dm_disable_feedback
};