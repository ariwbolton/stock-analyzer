#!/bin/bash

rm signalnames.txt signalnums.txt

grep -o '<tr id="dt1_[A-Z]*" class="">' signal100.txt | \
grep -o '[A-Z]\+' > signalnames.txt

grep -o '\([0-9]\+% \(Buy\|Sell\)\)\|\(>Hold<\)' signal100.txt \
> signalnums.txt

