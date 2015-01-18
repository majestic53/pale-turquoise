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

#include "../include/ptce_test.h"
#include "../include/ptce_test_board.h"

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		ptce_test_t 
		ptce_test_board_assignment(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_assignment exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->destroy();
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), result);
			return result;
		}

		ptce_test_t 
		ptce_test_board_constructor(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_constructor exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->destroy();
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), result);
			return result;
		}

		ptce_test_t 
		ptce_test_board_contains(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_contains exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->destroy();
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), result);
			return result;
		}

		ptce_test_t 
		ptce_test_board_equals(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_equals exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->destroy();
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), result);
			return result;
		}

		ptce_test_t 
		ptce_test_board_move(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_move exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->destroy();
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), result);
			return result;
		}

		ptce_test_t 
		ptce_test_board_not_equals(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_not_equals exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->destroy();
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), result);
			return result;
		}

		ptce_test_t 
		ptce_test_board_piece(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_piece exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->destroy();
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), result);
			return result;
		}

		ptce_test_t 
		ptce_test_board_piece_captured(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_piece_captured exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->destroy();
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), result);
			return result;
		}

		ptce_test_t 
		ptce_test_board_piece_count(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_piece_count exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->destroy();
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), result);
			return result;
		}

		ptce_test_t 
		ptce_test_board_piece_moved(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_piece_moved exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->destroy();
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), result);
			return result;
		}

		ptce_test_t 
		ptce_test_board_size(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_size exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->destroy();
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), result);
			return result;
		}

		ptce_test_t 
		ptce_test_board_state(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_state exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->destroy();
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), result);
			return result;
		}
	}
}
