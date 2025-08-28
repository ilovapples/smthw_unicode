#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "aplcore/types.h"
#include "getcodept.h"

struct UTF8_max4byte get_bytes_from_codepoint_str(const char *cp_str)
{
	const char *pos = cp_str;
	const size_t cp_strlen = strlen(cp_str);
	if (cp_strlen > 2 && strncmp(pos, "U+", 2) == 0)
		pos += 2;
	char buf[6+1] = {0};
	char *bfps = buf;
	for (u8 i = 0; i < 6; ++i)
	{
		if (*pos && !isxdigit(*pos))
			return (struct UTF8_max4byte) {{0}, 0};

		if ((*bfps++ = *pos++) == '\0')
			break;
	}

	struct UnicodeCodePoint code_point = {0};
 	code_point.val.i = strtoul(buf, NULL, 16);
	if (code_point.val.i < 0x0080)
		code_point.type = UCP_ASCII_TYPE;
	else if (code_point.val.i < 0x0800)
		code_point.type = UCP_2BYTE_TYPE;
	else if (code_point.val.i < 0x010000)
		code_point.type = UCP_3BYTE_TYPE;
	else if (code_point.val.i < 0x110000)
		code_point.type = UCP_3BYTE_TYPE;
	else
		return (struct UTF8_max4byte) {{0}, 0};

	struct UTF8_max4byte ret = {0};

	switch (code_point.type) {
	case UCP_ASCII_TYPE:
		ret.bytes[0] = code_point.val.b[0];
		ret.len = 1;
		return ret;
	case UCP_2BYTE_TYPE:
		ret.bytes[0] = 0xC0 | ((code_point.val.b[1] & 0x07) << 2)
		                    | ((code_point.val.b[0] & 0xC0) >> 6);
		ret.bytes[1] = 0x80 | (code_point.val.b[0] & 0x3F);
		ret.len = 2;
		return ret;
	case UCP_3BYTE_TYPE:
		ret.bytes[0] = 0xE0 | ((code_point.val.b[1] & 0xF0) >> 4);
		ret.bytes[1] = 0x80 | ((code_point.val.b[1] & 0x0F) << 2)
		                    | ((code_point.val.b[0] & 0xC0) >> 6);
		ret.bytes[2] = 0x80 | (code_point.val.b[0] & 0x3F);
		ret.len = 3;
		return ret;
	case UCP_4BYTE_TYPE:
		ret.bytes[0] = 0xF0 | ((code_point.val.b[2] & 0x1C) << 2);
		ret.bytes[1] = 0x80 | ((code_point.val.b[2] & 0x03) << 4)
		                    | ((code_point.val.b[1] & 0xF0) >> 4);
		ret.bytes[2] = 0x80 | ((code_point.val.b[1] & 0x0F) << 2)
		                    | ((code_point.val.b[0] & 0xC0) >> 6);
		ret.bytes[3] = 0x80 | (code_point.val.b[0] & 0x3F);
		ret.len = 4;
		return ret;
	default:
		break;
	}

	return (struct UTF8_max4byte) {{0}, 0};
}
