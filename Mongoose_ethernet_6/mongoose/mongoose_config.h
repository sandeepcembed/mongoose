/*
 * mongoose_config.h
 *
 *  Created on: 25-Jul-2024
 *      Author: DELL
 */

#ifndef MONGOOSE_MONGOOSE_CONFIG_H_
#define MONGOOSE_MONGOOSE_CONFIG_H_



#pragma once

// See https://mongoose.ws/documentation/#build-options
#define MG_ARCH MG_ARCH_NEWLIB

#define MG_ENABLE_TCPIP 1
#define MG_ENABLE_CUSTOM_MILLIS 1
#define MG_IO_SIZE 256
#define MG_ENABLE_PACKED_FS 1
#define MG_ENABLE_DRIVER_TM4C 1
//#define MG_ENABLE_LINES 1

#endif /* MONGOOSE_MONGOOSE_CONFIG_H_ */
