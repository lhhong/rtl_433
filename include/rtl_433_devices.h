/** @file
    Declaration of all available decoders.
*/

#ifndef INCLUDE_RTL_433_DEVICES_H_
#define INCLUDE_RTL_433_DEVICES_H_

#include "r_device.h"

#define DEVICES \
	DECL(brandless_kinetic_switch) \
	DECL(brandless_remote) \

    /* Add new decoders here. */

#define DECL(name) extern r_device name;
DEVICES
#undef DECL

#endif /* INCLUDE_RTL_433_DEVICES_H_ */
