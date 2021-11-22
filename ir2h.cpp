// Copyright (C) 2014-2021 Theo Niessink <theo@taletn.com>
// This work is free. You can redistribute it and/or modify it under the
// terms of the Do What The Fuck You Want To Public License, Version 2,
// as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.

#include <math.h>
#include <stdio.h>

#include "WDL/wavread.h"

int error(const char* str, int err)
{
	fputs(str, stderr);
	return err;
}

int main(int argc, char* argv[])
{
	if (argc < 3 || argc > 4)
	{
		printf("Usage: %s <input WAV file> <mono/left channel output C header file>\n"
		       "       [<right channel output C header file>]\n", argv[0]);
		return 1;
	}

	WaveReader wav;
	unsigned int len;
	if (!(wav.Open(argv[1]) && (len = wav.GetLength())))
	{
		return error("Error: Can't open WAV file\n", 2);
	}

	int nch = argc > 3 ? 2 : 1;
	if (nch != wav.get_nch())
	{
		fputs("Warning: Mono/stereo mismatch\n", stderr);
		if (nch > wav.get_nch()) nch = wav.get_nch();
	}

	FILE* out[2];
	for (int i = 0; i < nch; ++i)
	{
		char* fn = argv[i + 2];
		printf("%s (%u samples)\n", fn, len);

		out[i] = fopen(fn, "wb");
		if (!out[i]) return error("Error: Can't create C header file\n", 3);
	}

	float buf[2][64], * const pp[2] = { buf[0], buf[1] };
	while (len > 0)
	{
		unsigned int n = len;
		if (n > 64) n = 64;

		if (wav.ReadFloatsNI((float**)pp, 0, n, nch) < n)
		{
			return error("Error: Can't read WAV file\n", 4);
		}

		for (int i = 0; i < nch; ++i)
		{
			for (unsigned int j = 0; j < n;)
			{
				const double x = (double)buf[i][j], a = fabs(x);
				if (a > 0.0)
				{
					const double e = floor(log10(a));
					fprintf(out[i], "%.8f", x / pow(10.0, e));
					if (e != 0.0) fprintf(out[i], "e%+.f", e);
					putc('f', out[i]);
				}
				else
				{
					fputs("0", out[i]);
				}

				if (++j < len) putc(',', out[i]);
				if (!(j & 3) || j >= len) putc('\n', out[i]);
			}
		}

		len -= n;
	}	

	for (int i = 0; i < nch; ++i) fclose(out[i]);
	return 0;
}
