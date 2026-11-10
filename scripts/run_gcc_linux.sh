#!/usr/bin/env bash
mkdir -p bin
gcc src/main.c src/config.c src/context.c -o bin/main
./bin/main --cell_width=100 --iterations=100 --rule=90 --start_mode=1 --cell='#' --space='.'