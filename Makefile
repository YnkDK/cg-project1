main:
	g++ -O3 -Wall -lrt -std=c++0x INC_CH.cpp DC_CH.cpp MbC_CH.cpp MbC2_CH.cpp main.cpp -o main
perf:
	g++ -O3 -Wall -lrt -std=c++0x INC_CH.cpp DC_CH.cpp MbC_CH.cpp MbC2_CH.cpp Performance.cpp -o perf
tests:
	$(MAKE) -C generators all
	
clean:
	rm main
	rm perf
	rm output/*
