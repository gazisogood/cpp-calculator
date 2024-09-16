CC=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17

all: clean style tests gcov_report install

cmake:
	mkdir -p build && cd build && cmake ..

install: cmake
	cd build && make
	cd build && open SmartCalc.app

uninstall: clean
	rm -rf build

dvi:
	open ./README.md

dist: clean
	mkdir SmartCalc_v2.0
	mkdir SmartCalc_v2.0/src
	cp -R controller Smartcalc_v2.0/src
	cp -R model Smartcalc_v2.0/src
	cp -R view Smartcalc_v2.0/src
	cp -R graph Smartcalc_v2.0/src
	cp -R makefile Smartcalc_v2.0/src
	cp -R README.md Smartcalc_v2.0/src
	tar cvzf SmartCalc_v2.0.tgz SmartCalc_v2.0/
	rm -rf SmartCalc_v2.0

tests: clean
	$(CC) $(CFLAGS) --coverage tests/*.cc model/model.cc -lgtest -lgtest_main -pthread -o test
	./test

gcov_report: clean tests
	@lcov -t "SmartCalc" -o SmartCalc.info -c -d . --ignore-errors mismatch,inconsistent
	@lcov -e SmartCalc.info '*/src/*/*.cc' -o SmartCalc_filtered.info --ignore-errors mismatch,inconsistent
	@genhtml -o gcov_report SmartCalc_filtered.info --ignore-errors mismatch,inconsistent
	@open ./gcov_report/index.html

clean:
	rm -rf test *.gcda *.gcno *.o *.info *.a tests/*.gcno gcov_report test.dSYM SmartCalc_v2.0 SmartCalc_v2.0.tgz

style:
	clang-format -style=Google -n view/*.cc view/*.h
	clang-format -style=Google -n controller/*.cc controller/*.h
	clang-format -style=Google -n model/*.cc model/*.h
	clang-format -style=Google -n graph/*.cc graph/*.h
	clang-format -style=Google -n tests/*.cc
	clang-format -style=Google -n main.cc

clang:
	clang-format -style=Google -i view/*.cc view/*.h
	clang-format -style=Google -i controller/*.cc controller/*.h
	clang-format -style=Google -i model/*.cc model/*.h
	clang-format -style=Google -i graph/*.cc graph/*.h
	clang-format -style=Google -i tests/*.cc
	clang-format -style=Google -i main.cc

valgrind:
	CK_FORK=no valgrind --vgdb=no --leak-check=full --tool=memcheck --leak-check=yes make test

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

lcov_install:
	brew install lcov

rebuild: clean tests
