#!/bin/bash



for n in {5..30}
do
  for m in {5..14}
  do
    for line in $(cat syms.txt)
    do
      echo 1 > "$line"inp.txt
      echo $line >> "$line"inp.txt
      echo 3 >> "$line"inp.txt
      echo $line >> "$line"inp.txt
      echo 0 >> "$line"inp.txt

      echo "$line" > ./resultsBB/"$line".txt

      ./StockProcessor.out < "$line"inp.txt | grep -s -o '[0-9]*.[0-9]*%' | grep -s -o '[0-9]*\.[0-9]*'>> ./resultsBB/"$line".txt

      rm "$line"inp.txt
    done
  done
done
