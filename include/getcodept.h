#include "../../include/aplcore/types.h"

struct UnicodeCodePoint {
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
};

struct UTF8_max4byte {
	u8 bytes[4];
	usize len;
};

struct UTF8_max4byte get_bytes_from_codepoint_str(const char *cp_str);
