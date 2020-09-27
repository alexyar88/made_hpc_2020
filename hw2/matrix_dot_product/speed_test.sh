#!/bin/zsh

for flag in 'flag_O3' 'flag_g'
do
  make $flag
  for n in 4096
  do
    ./matmul $n
    ./matmul $n strassen
  done
done
