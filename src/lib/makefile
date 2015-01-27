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
FLAGS=-march=native -std=gnu++11 -O3 -Wall
INC=./include/
LIB=libptce.a
OUT_BIN=./../../bin/
OUT_BUILD=./../../build/
SRC=./src/

all: build archive

archive:
	@echo ""
	@echo "--- BUILDING PTCE LIBRARY ------------------"
	ar rcs $(OUT_BUILD)$(LIB) $(OUT_BUILD)ptce.o $(OUT_BUILD)ptce_board.o $(OUT_BUILD)ptce_defines.o $(OUT_BUILD)ptce_game.o $(OUT_BUILD)ptce_node.o $(OUT_BUILD)ptce_piece.o $(OUT_BUILD)ptce_uid.o
	@echo "--- DONE -----------------------------------"
	@echo ""

build: ptce.o ptce_board.o ptce_defines.o ptce_game.o ptce_node.o ptce_piece.o ptce_uid.o

ptce.o: $(SRC)ptce.cpp $(INC)ptce.h
	$(CC) $(FLAGS) -c $(SRC)ptce.cpp -o $(OUT_BUILD)ptce.o

ptce_board.o: $(SRC)ptce_board.cpp $(INC)ptce_board.h
	$(CC) $(FLAGS) -c $(SRC)ptce_board.cpp -o $(OUT_BUILD)ptce_board.o

ptce_defines.o: $(SRC)ptce_defines.cpp $(INC)ptce_defines.h
	$(CC) $(FLAGS) -c $(SRC)ptce_defines.cpp -o $(OUT_BUILD)ptce_defines.o

ptce_game.o: $(SRC)ptce_game.cpp $(INC)ptce_game.h
	$(CC) $(FLAGS) -c $(SRC)ptce_game.cpp -o $(OUT_BUILD)ptce_game.o

ptce_node.o: $(SRC)ptce_node.cpp $(INC)ptce_node.h
	$(CC) $(FLAGS) -c $(SRC)ptce_node.cpp -o $(OUT_BUILD)ptce_node.o

ptce_piece.o: $(SRC)ptce_piece.cpp $(INC)ptce_piece.h
	$(CC) $(FLAGS) -c $(SRC)ptce_piece.cpp -o $(OUT_BUILD)ptce_piece.o

ptce_uid.o: $(SRC)ptce_uid.cpp $(INC)ptce_uid.h
	$(CC) $(FLAGS) -c $(SRC)ptce_uid.cpp -o $(OUT_BUILD)ptce_uid.o
