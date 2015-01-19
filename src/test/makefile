# libptce
# Copyright (C) 2015 David Jolly
# ----------------------
#
# libptce is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# libptce is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CC=clang++
EXE=ptce_test
FLAGS=-march=native -std=gnu++11 -O3 -Wall
INC=./include/
LIB=libptce.a
LIB_TEST=libptcetest.a
OUT_BIN=./../../bin/
OUT_BUILD=./../../build/
SRC=./src/
TOP=./

all: build archive exe

archive:
	@echo ""
	@echo "--- BUILDING PTCE TEST LIBRARY -------------"
	ar rcs $(OUT_BUILD)$(LIB_TEST) $(OUT_BUILD)ptce.o $(OUT_BUILD)ptce_board.o $(OUT_BUILD)ptce_defines.o $(OUT_BUILD)ptce_node.o $(OUT_BUILD)ptce_piece.o $(OUT_BUILD)ptce_uid.o $(OUT_BUILD)ptce_test_set.o $(OUT_BUILD)ptce_test.o $(OUT_BUILD)ptce_test_board.o $(OUT_BUILD)ptce_test_node.o $(OUT_BUILD)ptce_test_piece.o $(OUT_BUILD)ptce_test_singleton.o $(OUT_BUILD)ptce_test_uid.o
	@echo "--- DONE -----------------------------------"
	@echo ""

exe:
	@echo ""
	@echo "--- BUILDING PTCE --------------------------" 
	$(CC) $(FLAGS) $(TOP)main.cpp $(OUT_BUILD)$(LIB) $(OUT_BUILD)$(LIB_TEST) -o $(OUT_BIN)$(EXE)
	@echo "--- DONE -----------------------------------"
	@echo ""

build: ptce_test_set.o ptce_test.o ptce_test_board.o ptce_test_node.o ptce_test_piece.o ptce_test_singleton.o ptce_test_uid.o

ptce_test.o: $(SRC)ptce_test.cpp $(INC)ptce_test.h
	$(CC) $(FLAGS) -c $(SRC)ptce_test.cpp -o $(OUT_BUILD)ptce_test.o

ptce_test_set.o: $(SRC)ptce_test_set.cpp $(INC)ptce_test_set.h
	$(CC) $(FLAGS) -c $(SRC)ptce_test_set.cpp -o $(OUT_BUILD)ptce_test_set.o

### UNIT TESTS ###

ptce_test_board.o: $(SRC)ptce_test_board.cpp $(INC)ptce_test_board.h
	$(CC) $(FLAGS) -c $(SRC)ptce_test_board.cpp -o $(OUT_BUILD)ptce_test_board.o

ptce_test_node.o: $(SRC)ptce_test_node.cpp $(INC)ptce_test_node.h
	$(CC) $(FLAGS) -c $(SRC)ptce_test_node.cpp -o $(OUT_BUILD)ptce_test_node.o

ptce_test_piece.o: $(SRC)ptce_test_piece.cpp $(INC)ptce_test_piece.h
	$(CC) $(FLAGS) -c $(SRC)ptce_test_piece.cpp -o $(OUT_BUILD)ptce_test_piece.o

ptce_test_singleton.o: $(SRC)ptce_test_singleton.cpp $(INC)ptce_test_singleton.h
	$(CC) $(FLAGS) -c $(SRC)ptce_test_singleton.cpp -o $(OUT_BUILD)ptce_test_singleton.o

ptce_test_uid.o: $(SRC)ptce_test_uid.cpp $(INC)ptce_test_uid.h
	$(CC) $(FLAGS) -c $(SRC)ptce_test_uid.cpp -o $(OUT_BUILD)ptce_test_uid.o
