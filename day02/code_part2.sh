#!/bin/bash
input="data.txt"
result=0
depth=0
aim=0
while IFS= read -r current; do
  cmd=${current/ */}
  num=${current/* /}
  case $cmd in
  "up")
    ((aim = aim - num))
    ;;
  "down")
    ((aim = aim + num))
    ;;
  "forward")
    ((result = result + num))
    ((depth = depth + aim * num))
    ;;
  esac
  echo "$aim $result >$cmd<"
done <"$input"
echo $((result * depth))
