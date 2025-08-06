all:
	g++ -shared -o init.dll init.cpp \
	-I "C:\SDL3-main\x86_64-w64-mingw32\include" \
	-L "C:\SDL3-main\x86_64-w64-mingw32\lib" \
	-lSDL3 \
	-static-libgcc -static-libstdc++ \
	-luser32 -lgdi32 -limm32 -lole32 -loleaut32 -lversion -luuid -ldxguid \
	-lwinmm -lsetupapi -lcfgmgr32
