#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "aplcore/types.h"
#include "getcodept.h"

void get_bytes_from_codepoint_str(
	const char *cp_str,
	u8 *out_bytes,
	usize *out_len)
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
		{
			*out_len = 0;
			return;
		}

		if ((*bfps++ = *pos++) == '\0')
			break;
	}

	UCP code_point = {0};
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
	{
		*out_len = 0;
		return;
	}

	switch (code_point.type) {
	case UCP_ASCII_TYPE:
		out_bytes[0] = code_point.val.b[0];
		*out_len = 1;
		return;
	case UCP_2BYTE_TYPE:
		out_bytes[0] = 0xC0 | ((code_point.val.b[1] & 0x07) << 2)
		                    | ((code_point.val.b[0] & 0xC0) >> 6);
		out_bytes[1] = 0x80 | (code_point.val.b[0] & 0x3F);
		*out_len = 2;
		return;
	case UCP_3BYTE_TYPE:
		out_bytes[0] = 0xE0 | ((code_point.val.b[1] & 0xF0) >> 4);
		out_bytes[1] = 0x80 | ((code_point.val.b[1] & 0x0F) << 2)
		                    | ((code_point.val.b[0] & 0xC0) >> 6);
		out_bytes[2] = 0x80 | (code_point.val.b[0] & 0x3F);
		*out_len = 3;
		return;
	case UCP_4BYTE_TYPE:
		out_bytes[0] = 0xF0 | ((code_point.val.b[2] & 0x1C) << 2);
		out_bytes[1] = 0x80 | ((code_point.val.b[2] & 0x03) << 4)
		                    | ((code_point.val.b[1] & 0xF0) >> 4);
		out_bytes[2] = 0x80 | ((code_point.val.b[1] & 0x0F) << 2)
		                    | ((code_point.val.b[0] & 0xC0) >> 6);
		out_bytes[3] = 0x80 | (code_point.val.b[0] & 0x3F);
		*out_len = 4;
		return;
	default:
		break;
	}

	*out_len = 0;
}
