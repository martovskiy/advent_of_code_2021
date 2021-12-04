#!/bin/bash
input="test.txt"
chars=$(cat $input | head -n 1 | wc -c)
number1=""
for ((i = 1; i < $chars; i++)); do
  char=$(cut -c $i $input | sort | uniq -c | sort -nr | head -n 1 | tail -c -2)
  number1="${number1}${char}"
done
number2=$(echo "$number1" | tr 01 10)
dec1="$((2#$number1))"
dec2="$((2#$number2))"

echo $(( dec1 * dec2 ))