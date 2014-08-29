StockProcessor.out: main.cpp Day.o Stock.o
	g++ -Wall -o StockProcessor.out main.cpp Day.o Stock.o 

Day.o: Day.cpp Day.h
	g++ -Wall -c Day.cpp

Stock.o: Stock.cpp Stock.h
	g++ -Wall -c Stock.cpp

clean:
	rm -f *.o StockProcessor.out
