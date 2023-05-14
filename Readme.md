# IR to C header

Converts mono/stereo impulse response (WAV file) to C header file(s).

## Requires WDL "Tale" Edition

Get WDL "Tale" Edition from:

https://www.taletn.com/WDL.git

Or from:

https://github.com/TaleTN/WDL

Extract it so you have:

```
ir2h.cpp
Makefile.*
```

and

```
WDL/heapbuf.h
WDL/pcmfmtcvt.h
WDL/wavread.h
WDL/wdlendian.h
WDL/wdlstring.h
WDL/wdltypes.h
WDL/win32_utf8.h
```

## How to build & run

Windows:

```
nmake /f Makefile.msvc
ir2h.exe /?
```

macOS/Linux:

```
make -f Makefile.gcc
./ir2h -h
```

## License

Copyright &copy; 2014-2021 Theo Niessink &lt;theo@taletn.com&gt;  
This work is free. You can redistribute it and/or modify it under the
terms of the Do What The Fuck You Want To Public License, Version 2,
as published by Sam Hocevar. See http://www.wtfpl.net/ for more details.
