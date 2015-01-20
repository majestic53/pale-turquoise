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

EXE=ptce_test
EXE_DIR=./src/test/
JOB_SLOTS=4
LIB_DIR=./src/lib/
OUT_BIN=./bin/
OUT_BUILD=./build/
OUT_LOG=./log/
SRC_DIR=./src/

MEM_LOG=val_err.log
STAT_LOG=stat_err.log
CLOC_LOG=cloc_stat.log

all: build

build: clean init lib exe

clean:
	rm -rf $(OUT_BIN)
	rm -rf $(OUT_BUILD)
	rm -rf $(OUT_LOG)

exe:
	@echo ""
	@echo "============================================"
	@echo "BUILDING EXECUTABLES"
	@echo "============================================"
	cd $(EXE_DIR) && make exe

init:
	mkdir $(OUT_BIN)
	mkdir $(OUT_BUILD)
	mkdir $(OUT_LOG)

lib: 
	@echo ""
	@echo "============================================"
	@echo "BUILDING LIBRARIES"
	@echo "============================================"
	cd $(LIB_DIR) && make build -j $(JOB_SLOTS)
	cd $(LIB_DIR) && make archive
	cd $(EXE_DIR) && make build -j $(JOB_SLOTS)
	cd $(EXE_DIR) && make archive

### TESTING ###

test: static mem

mem:
	@echo ""
	@echo "============================================"
	@echo "RUNNING MEMORY TEST"
	@echo "============================================"
	valgrind $(OUT_BIN)$(EXE) ==leak-check=full --verbose 2> $(OUT_LOG)$(MEM_LOG)

static:
	@echo ""
	@echo "============================================"
	@echo "RUNNING STATIC ANALYSIS"
	@echo "============================================"
	cppcheck --enable=all --std=c++11 $(SRC_DIR) 2> $(OUT_LOG)$(STAT_LOG)

### STATISTICS ###

stat: lines

lines:
	@echo ""
	@echo "============================================"
	@echo "CALCULATING LINE COUNT"
	@echo "============================================"
	cloc $(SRC_DIR) > $(OUT_LOG)$(CLOC_LOG)
