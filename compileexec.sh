#!/bin/bash
[ -f main ] && rm main
gcc main.c -o main -lm
./main
