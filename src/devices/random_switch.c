#include "decoder.h"

static int brandless_switch_callback(r_device *decoder, bitbuffer_t *bitbuffer) {
	if (bitbuffer->num_rows < 3) {
		return DECODE_ABORT_LENGTH;
	}
	int row = bitbuffer_find_repeated_row(bitbuffer, 3, 24);
	if (row < 0) {
		return DECODE_ABORT_EARLY;
	}
    uint8_t data[3]={0};
	bitbuffer_extract_bytes(bitbuffer, row, 0, data, 24);
	char hexstr[7] = {0};

	const char HEX [16] = "0123456789ABCDEF";
	for(size_t i=0; i<3; i++) {
    	hexstr[i*2] =  HEX[ (data[i] & 0xF0) >> 4 ];
    	hexstr[i*2+1] =  HEX[ (data[i] & 0x0F) ];
    }

    /* clang-format off */
    data_t *output = data_make(
            "model",        "",             DATA_STRING, "Brandless kinetic switch",
            "id",           "Id",           DATA_STRING, hexstr,
            NULL);
    /* clang-format on */

    decoder_output_data(decoder, output);
    return 1;
}

static char const *const brandless_switch_output_fields[] = {
		"model",
        "id",
        NULL,
};

r_device const brandless_kinetic_switch = {
        .name        = "Brandless kinetic switch",
        .modulation  = OOK_PULSE_PWM,
		.sync_width  = 33,
        .short_width = 33,
        .long_width  = 100,
		.gap_limit   = 500,
        .reset_limit = 2000,
		.tolerance   = 20,
        .decode_fn   = &brandless_switch_callback,
        .fields      = brandless_switch_output_fields,
};
