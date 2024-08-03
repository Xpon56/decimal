CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
LFLAGS=-lcheck -lpthread -lsubunit -lm
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -fPIC
CFILES=s21_decimal.a
CEXE=s21_test

#============= FLAGS FOR OS ======================================================== 
UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LDFLAGS=-lcheck -lsubunit -lm -lrt -lpthread
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lcheck -lm
	OPEN_CM=open
endif

#============= ALL ==================================================================
all: clean ${CFILES}

#============= LIBRIRY & TEST LIBRARY================================================

s21_decimal.a:
	${CC} ${CFLAGS} -c s21_*.c
	ar rc ${CFILES} *.o
	ranlib ${CFILES}
	rm -f *.o

gcov_s21_decimal.a: clean
	${CC} ${CFLAGS} -c *.c ${GCOV_FLAGS}
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a
	rm -f *.o

#============= TEST ==============================================================

test: clean s21_decimal.a
	$(CC) ${CFLAGS} tests/*.c  ${CFILES} -o ${CEXE} ${LDFLAGS}
	./${CEXE}

gcov_report: clean gcov_s21_decimal.a
	$(CC) ${CFLAGS} tests/*.c s21_decimal.a -o ${CEXE} ${LDFLAGS} ${GCOV_FLAGS}
	./${CEXE}
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	open report/index.html
	rm -rf *.gcda *.gcno *.info


#=========== STYLE ====================================================================
style:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n tests/*.c tests/*.h *.c *.h
	rm -f .clang-format

style_fmt:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i tests/*.c tests/*.h *.c *.h
	rm -f .clang-format

#=========== VALGRIND ==================================================================
val: clean s21_decimal.a
	$(CC) ${CFLAGS} tests/*.c  ${CFILES} -o ${CEXE} ${LDFLAGS}
	valgrind --tool=memcheck --leak-check=yes --log-file=val_log.log ./${CEXE}

#=========== LEAKS =====================================================================
leaks: clean s21_decimal.a
	$(CC) ${CFLAGS} tests/*.c  ${CFILES} -o ${CEXE} ${LDFLAGS}
	leaks -atExit -- ./${CEXE} >> leak_log.log

#========== CLEAN ======================================================================
clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf *.a
	rm -rf s21_test
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.gcov
	rm -rf *.log
	rm -rf *.html
	rm -rf *.css
	rm -rf report
	rm -rf *.dSYM
	rm -rf *.info