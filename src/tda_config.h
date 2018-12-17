/*
 * config.h
 *
 *  Created on: 02.01.2017
 *      Author: ZumkehrAdm
 */

#ifndef TDA_CONFIG_H_
#define TDA_CONFIG_H_

typedef enum {
		CFG_MAGIC_NUMBER = 0,
		CFG_CHANNEL,
		CFG_INPUT_GAIN,
		CFG_VOLUME,
		CFG_BASS,
		CFG_MIDRANGE,
		CFG_TREBLE,
		CFG_ATTEN_R,
		CFG_ATTEN_L,
		CFG_SIZE
} TDA7439_config;



#endif /* TDA_CONFIG_H_ */
