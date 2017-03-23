%o:%c
	g++ -c $<

hw1: hw1.o Connection.o
	g++ -o hw1 $^
