aprox: main.o splines.o points.o aproksymator_na_bazie.o $(solver)/libge.a
	gcc -o aprox  main.o splines.o points.o aproksymator_na_bazie.o -L $(solver) -l ge

main.o:	main.c
	gcc -c main.c -o main.o

splines.o:	splines.c
	gcc -c splines.c -o splines.o

points.o:	points.c
	gcc -c points.c -o points.o

intrp: main.o splines.o points.o interpolator.o $(solver)/libge.a
	gcc -o intrp  main.o splines.o points.o interpolator.o -L $(solver) -l ge

prosta: main.o splines.o points.o prosta.o
	gcc -o prosta  main.o splines.o points.o prosta.o	

aproksymator_na_bazie.o: makespl.h points.h $(solver)/piv_ge_solver.h
	gcc -I $(solver) -c aproksymator_na_bazie.c

interpolator.o: makespl.h points.h $(solver)/piv_ge_solver.h
	gcc -I $(solver) -c interpolator.c

.PHONY: clean

clean:
	rm *.o
	rm aprox*
