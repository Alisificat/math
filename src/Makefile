CC=gcc -std=c11 -Wall -Werror -Wextra
SOURCE=s21_math.c
OBJECT=$(SOURCE:.c=.o)
GCOVFLAGS=-L. --coverage
HTML=lcov -t "test" -o rep.info -c -d .
OS := $(shell uname)

ifeq ($(OS), Darwin)
	CHECK_H=-lcheck
else
	# CHECK_H=-lcheck -pthread -lrt -lm
	CHECK_H=-lcheck -lm -lrt -lpthread -D_GNU_SOURCE
endif

all: gcov_report

s21_math.a: clean $(OBJECT)
	ar rcs s21_math.a $(OBJECT)
	ranlib s21_math.a

test: s21_math.a
	$(CC) s21_math_tests.c $(SOURCE) -o test $(CHECK_H) $(GCOVFLAGS)
	./test

gcov_report: test
	$(HTML)
	genhtml -o report rep.info

open:
	open ./report/index.html # DELETE BEFORE FINISH PROJECT

clean:
	rm -rf *.a && rm -rf *.o
	rm -rf *.info && rm -rf *.gcda && rm -rf *.gcno &&  rm -rf *.gcov
	rm -rf report/ && rm -rf *.out test
	rm -rf CPPLINT.cfg

rebuild: clean all

linter:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	# rm -rf CPPLINT.cfg

cppcheck:
	cppcheck *.h *.c

vc:
	CK_FORK=no valgrind --tool=memcheck ./test

vb:
	K_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test

valgrind:
	valgrind -q --tool=memcheck --leak-check=yes --log-file=RESULT_VALGRIND.txt ./test -e while -e void s21_math.c Makefile -f pattern.txt -s -l
	cat RESULT_VALGRIND.txt
	 
lik: 
	CK_FORK=no leaks -atExit -- ./test

check:
	@echo
	@echo ===CPPCHECK===
	@echo
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
	@echo
	@echo ===STYLE TEST===
	@echo
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	@echo
	@echo ===LEAKS TEST===
	@echo
	CK_FORK=no leaks -atExit -- ./test

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

install_valgrind:
	brew install --HEAD LouisBrunner/valgrind/valgrind

install_cpch:
	brew install cppcheck