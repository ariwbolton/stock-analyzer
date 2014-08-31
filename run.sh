#!/bin/bash

make clean
make
./StockProcessor.out < MSFTtest.txt
