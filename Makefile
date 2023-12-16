a.out: evm1.o matrix_reader.o matrix_solver.o
	g++ evm1.o matrix_reader.o matrix_solver.o -std=c++11
evm1.o: evm1.cpp matrix_reader.h matrix_solver.h
	g++ -c evm1.cpp -std=c++11
matrix_reader.o: matrix_reader.cpp matrix_reader.h
	g++ -c matrix_reader.cpp -std=c++11
matrix_solver.o: matrix_solver.cpp matrix_solver.h
	g++ -c matrix_solver.cpp -std=c++11
clear:
	rm matrix_reader.o matrix_solver.o evm1.o a.out
