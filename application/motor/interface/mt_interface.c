//
// Created by Steins_Xin on 2025/8/10.
//

#include "motor_interface.h"
#include "driver/motor_drive_mt.h"

// ======================== 电机发送处理 ========================
static void motor_mt_get_angle(MotorDevice *motor) {
    MT_GetMultiTurnAngle(motor->can_bus, motor->can_id);
}

static void motor_mt_speed_control(MotorDevice *motor, float speed) {
    MT_SpeedControl(motor->can_bus, motor->can_id, speed);
}

static void motor_mt_position_control(MotorDevice *motor, float angleControl, uint16_t maxSpeed) {
    MT_PositionControlMulti(motor->can_bus, motor->can_id, angleControl, maxSpeed);
}

static void motor_mt_torque_control(MotorDevice *motor, int16_t torque) {
    MT_TorqueControl(motor->can_bus, motor->can_id, torque);
}

static void motor_mt_stop(MotorDevice *motor) {
    MT_StopMotor(motor->can_bus, motor->can_id);
}

static void motor_mt_enable(MotorDevice *motor) {
    MT_EnableMotor(motor->can_bus, motor->can_id);
}

static void motor_mt_disable(MotorDevice *motor) {
    MT_DisableMotor(motor->can_bus, motor->can_id);
}

// ======================== 电机回复处理 ========================
static void motor_mt_get_angle_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    MT_HandleMultiTurnAngleFeedback(motor, data, len);
}

static void motor_mt_speed_control_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    MT_HandleSpeedControlFeedback(motor, data, len);
}

static void motor_mt_position_control_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    MT_HandlePositionControlMultiFeedback(motor, data, len);
}

static void motor_mt_torque_control_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    MT_HandleTorqueControlFeedback(motor, data, len);
}

static void motor_mt_stop_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    MT_HandleStopMotorFeedback(motor, data, len);
}

static void motor_mt_enable_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    MT_HandleEnableMotorFeedback(motor, data, len);
}

static void motor_mt_disable_feedback(MotorDevice *motor, const uint8_t *data, uint8_t len) {
    MT_HandleDisableMotorFeedback(motor, data, len);
}


// 定义 MT 电机的操作表
const MotorOps MTMotorOps = {
        .get_angle = motor_mt_get_angle,
        .speed_control = motor_mt_speed_control,
        .position_control = motor_mt_position_control,
        .torque_control = motor_mt_torque_control,
        .stop = motor_mt_stop,
        .enable = motor_mt_enable,
        .disable = motor_mt_disable,

        .handle_get_angle_feedback = motor_mt_get_angle_feedback,
        .handle_speed_control_feedback = motor_mt_speed_control_feedback,
        .handle_position_control_feedback = motor_mt_position_control_feedback,
        .handle_torque_control_feedback = motor_mt_torque_control_feedback,
        .handle_stop_feedback = motor_mt_stop_feedback,
        .handle_enable_feedback = motor_mt_enable_feedback,
        .handle_disable_feedback = motor_mt_disable_feedback
};