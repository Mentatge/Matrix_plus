GCC=gcc
SRC=s21_matrix_oop.cc
OBJ=s21_matrix_oop.o
CFLAGS=--std=c++17 -lstdc++ -lm
TESTFLAGS=-lgtest -lgcov -lm
GCOVFLAGS=--coverage
HTML=lcov -t test -o rep.info -c -d ./
OS = $(shell uname)

all: clean gcov_report

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt *.dSYM

test: s21_matrix_oop.a
	$(GCC) -g unit_tests.cc s21_matrix_oop.a $(CFLAGS) $(TESTFLAGS) -o test
	./test

s21_matrix_oop.a: clean
	$(GCC) $(GCOVFLAGS) -c $(SRC)
	ar rcs s21_matrix_oop.a $(OBJ)
	ranlib s21_matrix_oop.a


gcov_report: test
	$(HTML)
	genhtml -o report rep.info
	open report/index.html

check: test
	clang-format -style="{BasedOnStyle: Google}" -i *.cc *.h
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SRC) *.h
