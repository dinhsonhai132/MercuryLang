all:
	g++ -shared -o init.dll init.cpp \
	-static -static-libgcc -static-libstdc++ \
	-luser32 -lgdi32 -limm32 -lole32 -loleaut32 -lversion -luuid -ldxguid \
	-lwinmm -lsetupapi -lcfgmgr32
