/**
 * libptce
 * Copyright (C) 2015 David Jolly
 * ----------------------
 *
 * libptce is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libptce is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../lib/include/ptce.h"
#include "./include/ptce_test.h"
#include "./include/ptce_test_board.h"
#include "./include/ptce_test_game.h"
#include "./include/ptce_test_node.h"
#include "./include/ptce_test_piece.h"
#include "./include/ptce_test_singleton.h"
#include "./include/ptce_test_uid.h"

ptce_test_set 
create_test_set_ptce_board(void)
{
	size_t test_iter = 0;
	ptce_test_set result(PTCE_TEST_BOARD_TRACE_HEADER);

	TRACE_ENTRY();

	for(; test_iter <= PTCE_TEST_BOARD_MAX; ++test_iter) {
		result.add(PTCE_TEST_BOARD_STRING(test_iter), 
				PTCE_TEST_BOARD_CALLBACK(test_iter));
	}

	TRACE_EXIT("Return Value: 0x%x", 0);
	return result;	
}

ptce_test_set 
create_test_set_ptce_game(void)
{
	size_t test_iter = 0;
	ptce_test_set result(PTCE_TEST_GAME_TRACE_HEADER);

	TRACE_ENTRY();

	for(; test_iter <= PTCE_TEST_GAME_MAX; ++test_iter) {
		result.add(PTCE_TEST_GAME_STRING(test_iter), 
				PTCE_TEST_GAME_CALLBACK(test_iter));
	}

	TRACE_EXIT("Return Value: 0x%x", 0);
	return result;	
}

ptce_test_set 
create_test_set_ptce_node(void)
{
	size_t test_iter = 0;
	ptce_test_set result(PTCE_TEST_NODE_TRACE_HEADER);

	TRACE_ENTRY();

	for(; test_iter <= PTCE_TEST_NODE_MAX; ++test_iter) {
		result.add(PTCE_TEST_NODE_STRING(test_iter), 
				PTCE_TEST_NODE_CALLBACK(test_iter));
	}

	TRACE_EXIT("Return Value: 0x%x", 0);
	return result;	
}

ptce_test_set 
create_test_set_ptce_piece(void)
{
	size_t test_iter = 0;
	ptce_test_set result(PTCE_TEST_PIECE_TRACE_HEADER);

	TRACE_ENTRY();

	for(; test_iter <= PTCE_TEST_PIECE_MAX; ++test_iter) {
		result.add(PTCE_TEST_PIECE_STRING(test_iter), 
				PTCE_TEST_PIECE_CALLBACK(test_iter));
	}

	TRACE_EXIT("Return Value: 0x%x", 0);
	return result;	
}

ptce_test_set 
create_test_set_ptce_singleton(void)
{
	size_t test_iter = 0;
	ptce_test_set result(PTCE_TEST_SINGLETON_TRACE_HEADER);

	TRACE_ENTRY();

	for(; test_iter <= PTCE_TEST_SINGLETON_MAX; ++test_iter) {
		result.add(PTCE_TEST_SINGLETON_STRING(test_iter), 
				PTCE_TEST_SINGLETON_CALLBACK(test_iter));
	}

	TRACE_EXIT("Return Value: 0x%x", 0);
	return result;
}

ptce_test_set 
create_test_set_ptce_uid(void)
{
	size_t test_iter = 0;
	ptce_test_set result(PTCE_TEST_UID_TRACE_HEADER);

	TRACE_ENTRY();

	for(; test_iter <= PTCE_TEST_UID_MAX; ++test_iter) {
		result.add(PTCE_TEST_UID_STRING(test_iter), 
				PTCE_TEST_UID_CALLBACK(test_iter));
	}

	TRACE_EXIT("Return Value: 0x%x", 0);
	return result;
}

void 
initialize_test_suite(void) 
{
	ptce_test_ptr inst = NULL;

	TRACE_ENTRY();
	
	inst = ptce_test::acquire();
	inst->add(PTCE_TEST_SINGLETON_TRACE_HEADER, create_test_set_ptce_singleton());
	inst->add(PTCE_TEST_UID_TRACE_HEADER, create_test_set_ptce_uid());
	inst->add(PTCE_TEST_NODE_TRACE_HEADER, create_test_set_ptce_node());
	inst->add(PTCE_TEST_PIECE_TRACE_HEADER, create_test_set_ptce_piece());
	inst->add(PTCE_TEST_BOARD_TRACE_HEADER, create_test_set_ptce_board());
	inst->add(PTCE_TEST_GAME_TRACE_HEADER, create_test_set_ptce_game());

	TRACE_EXIT("Return Value: 0x%x", 0);
}

int 
main(
	__in int argc, 
	__in const char **argv
	) 
{
	int result = 0;
	ptce_test_ptr inst = NULL;
	size_t failure, inconclusive, success;

	TRACE_ENTRY();

	std::cout << BUILD_TITLE << " " << ptce::version(true) << std::endl << BUILD_COPYRIGHT
			<< std::endl;

	try {
		inst = ptce_test::acquire();
		inst->initialize();
		initialize_test_suite();
		inst->run_all(failure, inconclusive, success);
		std::cout << inst->to_string(true) << std::endl << std::endl << "RESULT (" 
			<< failure << ", " << inconclusive << ", " << success << ")"
			<< std::endl;
		inst->destroy();
	} catch(std::runtime_error &exc) {
		std::cerr << exc.what() << std::endl;
		result = 1;
	}

	TRACE_EXIT("Return Value: 0x%x", result);
	return result;
}
