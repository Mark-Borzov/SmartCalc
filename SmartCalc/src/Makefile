CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
FLAGS_COV = -lcheck -lgcov -fprofile-arcs --coverage
OS_NAME=$(shell uname)

ifeq (${OS_NAME}, Linux)
FLAGS_L = -lcheck -lm -lpthread -lrt -lsubunit
else 
FLAGS_L = -lcheck
endif

all: test gcov_report install dist

stack.a:
	$(CC) $(CFLAGS) -c stack.c stack.h
	ar rcs stack.a stack.o
	ranlib stack.a
	rm -rf stack.o
	rm -rf stack.h.gch

notation.a: 
	$(CC) $(CFLAGS) -c notation.c notation.h
	ar rcs notation.a notation.o
	ranlib notation.a
	rm -rf notation.o
	rm -rf notation.h.gch

clean:
	rm -rf stack.a
	rm -rf notation.a
	rm -rf test
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf report
	rm -rf gcov_report.info
	rm -rf build-Front-Desktop-Debug

test: clean stack.a notation.a
	$(CC) tests_smart_calc.c notation.a stack.a $(FLAGS_L) -o test
	./test

gcov_report: clean
	$(CC) tests_smart_calc.c notation.c stack.c $(FLAGS_L) -o test $(FLAGS_COV)
	./test
	lcov -t "gcov_report" -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open report/index.html
	rm -rf *.gcda
	rm -rf *.gcno

install:
	mkdir -p ./build
	cd ./Front/ && qmake . && $(MAKE) all
	mv ./Front/main.o ./build
	mv ./Front/mainwindow.o ./build
	mv ./Front/Makefile ./build
	mv ./Front/moc_mainwindow.cpp ./build
	mv ./Front/moc_mainwindow.o ./build
	mv ./Front/moc_predefs.h ./build
	mv ./Front/moc_qcustomplot.cpp ./build
	mv ./Front/moc_qcustomplot.o ./build
	mv ./Front/notation.o ./build
	mv ./Front/qcustomplot.o ./build
	mv ./Front/stack.o ./build
	mv ./Front/ui_mainwindow.h ./build
	mv ./Front/Front ./build

uninstall:
	rm -rf build
	rm -rf dist

dvi:
	open documentation.md

dist: 
	mkdir -p ./dist
	tar -cvzf smart_calc.tar build documentation.md
	mv smart_calc.tar ./dist