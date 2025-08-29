#include "aplcore/types.h"

typedef struct {
	union {
		u32 i;
		u8 b[4];
	} val;
	enum {
		UCP_ASCII_TYPE,
		UCP_2BYTE_TYPE,
		UCP_3BYTE_TYPE,
		UCP_4BYTE_TYPE
	} type;
} UCP;

void get_bytes_from_codepoint_str(
	const char *cp_str,
	u8 *out_bytes,
	usize *out_len);
