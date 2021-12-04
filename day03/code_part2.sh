#!/bin/bash
input="data.txt"
chars=$(cat $input | head -n 1 | wc -c)
number1=""
data=$(cat $input)
for ((i = 1; i < chars; i++)); do
  echo "--- $number1 $data"
  echo "$data" | cut -c $i | sort | uniq -c | sort -k1,7nr -k8,8nr -t ' '
  char=$(echo "$data" | cut -c $i | sort | uniq -c | sort -k1,7nr -k8,8nr -t ' ' | head -n 1 | tail -c -2)
  number1="${number1}${char}"
  data=$(echo "$data" | egrep "^$number1")
  if [ $(echo "$data" | wc -l) -eq 1 ]; then
    number1=$data
    i=$chars
  fi
done

number2=""
data=$(cat $input)
for ((i = 1; i < chars; i++)); do
  char=$(echo "$data" | cut -c $i | sort | uniq -c | sort -k1,7n -k8,8n -t ' ' | head -n 1 | tail -c -2)
  number2="${number2}${char}"
  data=$(echo "$data" | egrep "^$number2")
  if [ $(echo "$data" | wc -l) -eq 1 ]; then
    number2=$data
    i=$chars
  fi
done
echo "$number1 $number2"
dec1="$((2#$number1))"
dec2="$((2#$number2))"

echo $((dec1 * dec2))
