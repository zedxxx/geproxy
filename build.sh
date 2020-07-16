#!/usr/bin/bash -ex

if [ $MSYSTEM = 'MINGW64' ]; then
  arch=64
else
  arch=32
fi 

dll=geproxy.dll
ini=geproxy.ini

rm -rf $dll

cmake . '-GMSYS Makefiles' \
        "-DBUILD_SHARED_LIBS=1" \
        "-DCMAKE_BUILD_TYPE=Release" \
        "-DCMAKE_C_FLAGS=-static-libgcc -s"
        
mingw32-make

echo -en "[Proxy]\r\nUse=1\r\nAddress=127.0.0.1:8081\r\n" > $ini

7z a -tzip geproxy-win$arch-mingw.zip $dll $ini

mingw32-make clean

rm CMakeCache.txt
rm -rf CMakeFiles
rm $ini
rm Makefile
rm cmake_install.cmake
