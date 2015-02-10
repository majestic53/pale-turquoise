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
EXE=ptce
FLAGS=-march=native -pthread -std=gnu++11 -O3 -Wall
INC=./include/
LIB=libptce.a
LIB_TOOL=libptcetool.a
OUT_BIN=./../../bin/
OUT_BUILD=./../../build/
SRC=./src/
TOP=./

all: build archive exe

archive:
	@echo ""
	@echo "--- BUILDING PTCE TOOL LIBRARY -------------"
	ar rcs $(OUT_BUILD)$(LIB_TOOL) $(OUT_BUILD)ptce.o $(OUT_BUILD)ptce_board.o $(OUT_BUILD)ptce_game.o $(OUT_BUILD)ptce_defines.o $(OUT_BUILD)ptce_node.o $(OUT_BUILD)ptce_piece.o $(OUT_BUILD)ptce_uid.o $(OUT_BUILD)ptce_parameter.o
	@echo "--- DONE -----------------------------------"
	@echo ""

exe:
	@echo ""
	@echo "--- BUILDING PTCE TOOL ---------------------" 
	$(CC) $(FLAGS) $(TOP)main.cpp $(OUT_BUILD)$(LIB) $(OUT_BUILD)$(LIB_TOOL) -o $(OUT_BIN)$(EXE)
	@echo "--- DONE -----------------------------------"
	@echo ""

build: ptce_parameter.o

ptce_parameter.o: $(SRC)ptce_parameter.cpp $(INC)ptce_parameter.h
	$(CC) $(FLAGS) -c $(SRC)ptce_parameter.cpp -o $(OUT_BUILD)ptce_parameter.o
