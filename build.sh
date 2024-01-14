#!/bin/sh
set -xe

cc -Wall -Wextra -pedantic -std=c11 -ggdb -o main main.c -L/usr/local/lib -lraylib -lm 

