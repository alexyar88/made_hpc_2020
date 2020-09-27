#!/bin/zsh

# 2 варианта
echo "100 + 0.5" | bc
echo 100 0.5 | awk '{print $1 + $2}'