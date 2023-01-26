libge: matrix.o pivot.o piv_ge_solver.o
	ar rvs libge.a $^

matrix.o: matrix.c matrix.h
	gcc -c matrix.c -o matrix.o

pivot.o: pivot.c matrix.h
	gcc -c pivot.c -o pivot.o

piv_ge_solver.o: piv_ge_solver.c piv_ge_solver.h matrix.h
	gcc -c piv_ge_solver.c -o piv_ge_solver.o

.PHONY: clean

clean:
	-rm *.o libge.a
