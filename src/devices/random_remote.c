#include "decoder.h"

static int brandless_remote_callback(r_device *decoder, bitbuffer_t *bitbuffer) {
	if (bitbuffer->bits_per_row[0] < 24 || bitbuffer->bits_per_row[0] > 30) {
		return DECODE_ABORT_LENGTH;
	}
  uint8_t data[3]={0};
	bitbuffer_extract_bytes(bitbuffer, 0, 0, data, 24);
	char hexstr[7] = {0};

	const char HEX [16] = "0123456789ABCDEF";
	for(size_t i=0; i<3; i++) {
    hexstr[i*2] =  HEX[ (data[i] & 0xF0) >> 4 ];
    hexstr[i*2+1] =  HEX[ (data[i] & 0x0F) ];
  }

  /* clang-format off */
  data_t *output = data_make(
          "model",        "",             DATA_STRING, "Brandless remote",
          "id",           "Id",           DATA_STRING, hexstr,
          NULL);
  /* clang-format on */

  decoder_output_data(decoder, output);
  return 1;
}

static char const *const brandless_remote_output_fields[] = {
		"model",
    "id",
    NULL,
};

r_device const brandless_remote = {
        .name        = "Brandless remote",
        .modulation  = OOK_PULSE_PWM,
        .sync_width  = 0,
        .short_width = 277,
        .long_width  = 946,
        .gap_limit   = 0,
        .reset_limit = 2000,
        .tolerance   = 68,
        .decode_fn   = &brandless_remote_callback,
        .fields      = brandless_remote_output_fields,
};
