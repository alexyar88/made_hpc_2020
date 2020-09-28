#!/bin/zsh

for flag in '-O3' '-g'
do
  make FLAG=$flag
  for n in 512 1024 2048 4096
  do
    ./matmul $n
    ./matmul $n strassen
  done
done
