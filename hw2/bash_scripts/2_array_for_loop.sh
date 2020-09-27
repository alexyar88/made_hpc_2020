#!/bin/zsh

array=(one two three a b c d e f g)

for element in "${array[@]}"
do
  echo $element
done