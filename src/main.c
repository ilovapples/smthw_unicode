#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#define APLCORE__INCLUDE_WIDE_FUNCS
#include "aplcore/types.h"
#include "aplcore/util/misc.h"
#include "aplcore/util/log.h"
#include "aplcore/wide_compat.h"
#include "getcodept.h"

s32 main(s32 argc, char **argv)
{
	setlocale(LC_ALL, "");
	if (argc < 2)
		wc_eerror(1, L("usage: %s <code_point+>\n"), argv[0]);

	struct UTF8_max4byte *bytes __defer_free = calloc(argc-1, sizeof(struct UTF8_max4byte));
	wchar_t *widestr __defer_free = calloc(argc, sizeof(wchar_t));
	for (s32 i = 0; i < argc - 1; ++i)
	{
		bytes[i] = get_bytes_from_codepoint_str(argv[i+1]);
		if (bytes[i].len == 0)
			wc_eerror(2, L("an error occurred attempting to decode the code")
					L(" point '%s'\n"), argv[i+1]);

		mbtowc(&widestr[i], (char *)bytes[i].bytes, 4);
	}

	wprintf(L"%ls", widestr);

	return 0;
}
