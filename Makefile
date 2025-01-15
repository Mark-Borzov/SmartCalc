CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
FLAGS_COV = -lcheck -lgcov -fprofile-arcs --coverage
FLAGS_L = -lcheck -lm -lpthread -lrt -lsubunit

all: test gcov_report install dist

stack.a:
	$(CC) $(CFLAGS) -c Back/stack.c Back/stack.h
	ar rcs Back/stack.a stack.o
	ranlib Back/stack.a
	rm -rf stack.o
	rm -rf Back/stack.h.gch

notation.a: 
	$(CC) $(CFLAGS) -c Back/notation.c Back/notation.h
	ar rcs Back/notation.a notation.o
	ranlib Back/notation.a
	rm -rf notation.o
	rm -rf Back/notation.h.gch

clean:
	rm -rf Back/stack.a
	rm -rf Back/notation.a
	rm -rf test
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf report
	rm -rf gcov_report.info
	rm -rf build-Front-Desktop-Debug

test: clean stack.a notation.a
	$(CC) Back/tests_smart_calc.c Back/notation.a Back/stack.a $(FLAGS_L) -o test
	./test
	rm -rf test

gcov_report: clean
	$(CC) Back/tests_smart_calc.c Back/notation.c Back/stack.c $(FLAGS_L) -o test $(FLAGS_COV)
	./test
	lcov -t "gcov_report" -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info;
	open report/index.html
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf gcov_report.info
	rm -rf test

# /usr/lib/qt6/bin/qmake -- Заменить на фактическое расположение файла: qmake !!!
install:
	mkdir -p ./Install
	cd ./Front/ && /usr/lib/qt6/bin/qmake . && $(MAKE) all
	mv ./Front/main.o ./Install
	mv ./Front/mainwindow.o ./Install
	mv ./Front/Makefile ./Install
	mv ./Front/moc_mainwindow.cpp ./Install
	mv ./Front/moc_mainwindow.o ./Install
	mv ./Front/moc_predefs.h ./Install
	mv ./Front/moc_qcustomplot.cpp ./Install
	mv ./Front/moc_qcustomplot.o ./Install
	mv ./Front/notation.o ./Install
	mv ./Front/qcustomplot.o ./Install
	mv ./Front/stack.o ./Install
	mv ./Front/ui_mainwindow.h ./Install
	mv ./Front/SmartCalc ./Install

uninstall: clean
	rm -rf Install
	rm -rf ./Front/build
	rm -rf SmartCalc.zip

launch:
	./Install/./SmartCalc

dist: uninstall
	zip -r SmartCalc.zip Back Front Makefile README.md

clang-check:
	clang-format -n Back/*.c Back/*.h

clang-done:
	clang-format -i Back/*.c Back/*.h