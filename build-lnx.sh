#! /bin/sh
g++ -O2 -DLINUX -I"$ADLSDKROOT/include" -ldl overdrive5.cpp -o overdrive5
