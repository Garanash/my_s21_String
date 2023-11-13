CC = gcc
FLAG_C = -c
FLAG_O = -o
ASAN = -fsanitize=address
FLAG_COV = --coverage 
FLAG_ER = -Wall -Werror -Wextra -std=c11
s21_STRING_C = s21_*.c 
s21_STRING_O = s21_*.o
SUITE_CASES_C = ~/tests/suite_*.c
SUITE_CASES_O = ~/tests/suite_*.o

all: clean s21_string.a test gcov_report
# --- СОЗДАНИЕ БИБЛИОТЕКИ ФУНКЦИЙ ---

s21_string.a:
	$(CC) $(FLAG_C) $(FLAG_ER) $(s21_STRING_C) 
	ar rc s21_string.a $(s21_STRING_O)
	ranlib s21_string.a
# --- СОЗДАНИЕ БИБЛИОТЕКИ ТЕСТОВ И ИСПОЛНЕНИЕ ---

test: s21_string.a
	$(CC) $(FLAG_C) $(FLAG_ER) $(SUITE_CASES_C) main.c
	ar rc suite_cases.a $(SUITE_CASES_O)
	ranlib suite_cases.a
	$(CC) $(ASAN) $(FLAG_ER) $(FLAG_COV) $(FLAG_O) tests s21_string.a suite_cases.a $(s21_STRING_C) main.o -lcheck
	./tests
# --- ФОРМИРОВАНИЕ ОТЧЕТА О ПОКРЫТИИ ---

gcov_report: test
	gcov s21_*.gcda	
	gcovr -b 
	gcovr
	gcovr --html-details -o report.html

check:
	cppcheck --enable=all --force *.h *.c
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	CK_FORK=no leaks --atExit -- ./tests
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./tests
	lcov -b --checksum --derive-func-data  -f -t "report" -o report.info -c -d . 
	genhtml  --branch-coverage -o report report.info	
	open ./report/report.html

clean:
	-rm -rf *.o *.html *.gcda *.gcno *.css *.a *.gcov *.info *.out *.cfg *.txt
	-rm -f tests
	-rm -f report
	find . -type d -name 'tests.dSYM' -exec rm -r {} +
# удаление для lcov и genhtml
	-rm -f ./tests.dSYM
	-rmdir tests.dSYM  
	-rm -rf . report/*
	-rmdir . report
