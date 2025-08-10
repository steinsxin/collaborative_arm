//
// Created by Steins_Xin on 2025/8/10.
//

#ifndef COLLABORATIVE_ARM_MOTOR_DRIVE_DM_H
#define COLLABORATIVE_ARM_MOTOR_DRIVE_DM_H

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include <string.h>
#include "can.h"

// application层
#include "motor_interface.h"

// DM10010L-MIT
// ==================== 命令 ID ====================
/**
 * @brief DM 电机命令枚举
 */
typedef enum {
    UNKNOWN_CMD = 0x00,                           ///< 未知命令
} DM_CMD_ID;

void DM_GetMultiTurnAngle(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID);
void DM_HandleMultiTurnAngleFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

void DM_SpeedControl(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID, float speedControl);
void DM_HandleSpeedControlFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

void DM_PositionControlMulti(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID, float angleControl, uint16_t maxSpeed);
void DM_HandlePositionControlMultiFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

void DM_TorqueControl(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID, int16_t torqueValue);
void DM_HandleTorqueControlFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

void DM_StopMotor(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID);
void DM_HandleStopMotorFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

void DM_DisableMotor(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID);
void DM_HandleDisableMotorFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

void DM_EnableMotor(CAN_HandleTypeDef *CAN_BUS, uint32_t CAN_ID);
void DM_HandleEnableMotorFeedback(MotorDevice *motor, const uint8_t *data, uint8_t len);

#endif //COLLABORATIVE_ARM_MOTOR_DRIVE_DM_H
