//
// Created by Steins_Xin on 2025/8/10.
//

#ifndef COLLABORATIVE_ARM_CAN_HANDLE_H
#define COLLABORATIVE_ARM_CAN_HANDLE_H

#include "can.h"

/**
 * 发送CAN消息
 * @param hcan CAN总线
 * @param CAN_ID 消息ID
 * @param data 消息数据
 * @param len 数据长度
 */
void CAN_Send(CAN_HandleTypeDef *hcan, uint32_t CAN_ID, uint8_t *data, uint8_t len);

#endif //COLLABORATIVE_ARM_CAN_HANDLE_H
