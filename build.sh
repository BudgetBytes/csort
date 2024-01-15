#!/bin/sh
set -xe

cc -Wall -Wextra -pedantic -std=c11 -ggdb -o main main.c  
cc -Wall -Wextra -pedantic -std=c11 -ggdb -o visualizer visualizer.c -L/usr/local/lib -lraylib -lm 
