#!/bin/bash
input="data.txt"
last=10000000
result=0
while IFS= read -r current
do
  if [ $last -lt $current ]; then
    ((result=result+1))
  fi
  last=$current
done < "$input"
echo "$result"