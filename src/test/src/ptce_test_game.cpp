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
#include "../include/ptce_test_game.h"

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		ptce_test_t 
		ptce_test_game_manager_acquire(void)
		{
			ptce_game_manager_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				try {

					inst = ptce_game_manager::acquire();
					if(!inst) {
						std::cerr << "----!ptce_test_game_manager_acquire failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(!inst->is_allocated()) {
						std::cerr << "----!ptce_test_game_manager_acquire failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_game_manager_acquire exception(0): " << exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
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
		ptce_test_game_manager_connections(void)
		{
			ptce_game_manager_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_game_manager::acquire();

				try {

					try {
						inst->connections();
						std::cerr << "----!ptce_test_game_manager_connections failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					} catch(...) { }
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_game_manager_connections exception(0): " << exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
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
		ptce_test_game_manager_is_allocated(void)
		{
			ptce_game_manager_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_game_manager::acquire();

				try {
					
					if(!inst) {
						result = PTCE_TEST_INCONCLUSIVE;
						goto exit;
					}

					try {

						if(!ptce_game_manager::is_allocated()) {
							std::cerr << "----!ptce_test_game_manager_is_allocated failure(0)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					} catch(std::runtime_error &exc) {
						std::cerr << "----!ptce_test_game_manager_is_allocated exception(0): " 
								<< exc.what() << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					ptce::release_game_manager();

					try {

						if(ptce_game_manager::is_allocated()) {
							std::cerr << "----!ptce_test_game_manager_is_allocated failure(1)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					} catch(std::runtime_error &exc) {
						std::cerr << "----!ptce_test_game_manager_is_allocated exception(1): " 
								<< exc.what() << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_game_manager_is_allocated exception(0): " << exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
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
		ptce_test_game_manager_is_started(void)
		{
			ptce_game_manager_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_game_manager::acquire();

				try {

					if(inst->is_started()) {
						std::cerr << "----!ptce_test_game_manager_is_started failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_game_manager_is_started exception(0): " << exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
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
		ptce_test_game_manager_port(void)
		{
			ptce_game_manager_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_game_manager::acquire();

				try {

					try {
						inst->port();
						std::cerr << "----!ptce_test_game_manager_port failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					} catch(...) { }
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_game_manager_port exception(0): " << exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
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
		ptce_test_game_manager_size(void)
		{
			ptce_game_manager_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_game_manager::acquire();

				try {

					try {
						inst->size();
						std::cerr << "----!ptce_test_game_manager_size failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					} catch(...) { }
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_game_manager_size exception(0): " << exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
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
