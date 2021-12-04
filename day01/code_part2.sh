#!/bin/bash
input="data.txt"
last=10000000
result=0
current=0
pred_line=0

while IFS= read -r line; do
  ((current = current + line))
  if [ $pred_line -gt 0 ]; then
    ((current = current - pred_line))
    if [ $last -lt $current ]; then
      ((result = result + 1))
    fi
  fi
  echo ">> $last $current $pred_line "
  ((screen = screen - 1))
  last=$current
  pred_line=$line2
  line2=$line1
  line1=$line
done <"$input"
echo "$result"
