//
// Created by Steins_Xin on 2025/8/10.
//

#ifndef COLLABORATIVE_ARM_MOTOR_DRIVE_MT_H
#define COLLABORATIVE_ARM_MOTOR_DRIVE_MT_H

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <string.h>
#include "can.h"

// application层
#include "motor_interface.h"

// X4-36 MIT24V
// ==================== 命令 ID ====================
/**
 * @brief MT 电机命令枚举
 */
typedef enum {
    UNKNOWN_CMD = 0x00,                           ///< 未知命令
} MT_CMD_ID;

void MT_GetMultiTurnAngle(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID);
void MT_HandleMultiTurnAngleFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

void MT_SpeedControl(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID, float speedControl);
void MT_HandleSpeedControlFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

void MT_PositionControlMulti(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID, float angleControl, uint16_t maxSpeed);
void MT_HandlePositionControlMultiFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

void MT_TorqueControl(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID, int16_t torqueValue);
void MT_HandleTorqueControlFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

void MT_StopMotor(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID);
void MT_HandleStopMotorFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

void MT_DisableMotor(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID);
void MT_HandleDisableMotorFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

void MT_EnableMotor(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID);
void MT_HandleEnableMotorFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

#endif //COLLABORATIVE_ARM_MOTOR_DRIVE_MT_H
