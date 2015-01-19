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
#include "../include/ptce_test_singleton.h"

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		ptce_test_t 
		ptce_test_singleton_acquire(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				inst = ptce::acquire();
				if(!inst) {
					std::cerr << "----!ptce_test_singleton_acquire failure(0)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				if(!inst->is_allocated()) {
					std::cerr << "----!ptce_test_singleton_acquire failure(1)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
			} catch(std::runtime_error &exc) {
				std::cerr << "----!ptce_test_singleton_acquire exception(0): " << exc.what() << std::endl;
				result = PTCE_TEST_FAILURE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}

		ptce_test_t 
		ptce_test_singleton_acquire_board_factory(void)
		{
			ptce_ptr parent = NULL;
			ptce_board_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				parent = ptce::acquire();
				parent->initialize();

				inst = parent->acquire_board_factory();
				if(!inst) {
					std::cerr << "----!ptce_test_singleton_acquire_board_factory failure(0)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				if(!inst->is_initialized()) {
					std::cerr << "----!ptce_test_singleton_acquire_board_factory failure(1)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				parent->destroy();

				if(inst->is_initialized()) {
					std::cerr << "----!ptce_test_singleton_acquire_board_factory failure(2)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
			} catch(std::runtime_error &exc) {
				std::cerr << "----!ptce_test_singleton_acquire_board_factory exception(0): " << exc.what() << std::endl;
				result = PTCE_TEST_FAILURE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}

		ptce_test_t 
		ptce_test_singleton_acquire_node_factory(void)
		{
			ptce_ptr parent = NULL;
			ptce_node_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				parent = ptce::acquire();
				parent->initialize();

				inst = parent->acquire_node_factory();
				if(!inst) {
					std::cerr << "----!ptce_test_singleton_acquire_node_factory failure(0)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				if(!inst->is_initialized()) {
					std::cerr << "----!ptce_test_singleton_acquire_node_factory failure(1)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				parent->destroy();

				if(inst->is_initialized()) {
					std::cerr << "----!ptce_test_singleton_acquire_node_factory failure(2)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
			} catch(std::runtime_error &exc) {
				std::cerr << "----!ptce_test_singleton_acquire_node_factory exception(0): " << exc.what() << std::endl;
				result = PTCE_TEST_FAILURE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}

		ptce_test_t 
		ptce_test_singleton_acquire_piece_factory(void)
		{
			ptce_ptr parent = NULL;
			ptce_piece_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				parent = ptce::acquire();
				parent->initialize();

				inst = parent->acquire_piece_factory();
				if(!inst) {
					std::cerr << "----!ptce_test_singleton_acquire_piece_factory failure(0)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				if(!inst->is_initialized()) {
					std::cerr << "----!ptce_test_singleton_acquire_piece_factory failure(1)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				parent->destroy();

				if(inst->is_initialized()) {
					std::cerr << "----!ptce_test_singleton_acquire_piece_factory failure(2)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
			} catch(std::runtime_error &exc) {
				std::cerr << "----!ptce_test_singleton_acquire_piece_factory exception(0): " << exc.what() << std::endl;
				result = PTCE_TEST_FAILURE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}

		ptce_test_t 
		ptce_test_singleton_acquire_uid_factory(void)
		{
			ptce_ptr parent = NULL;
			ptce_uid_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				parent = ptce::acquire();
				parent->initialize();

				inst = parent->acquire_uid_factory();
				if(!inst) {
					std::cerr << "----!ptce_test_singleton_acquire_uid_factory failure(0)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				if(!inst->is_initialized()) {
					std::cerr << "----!ptce_test_singleton_acquire_uid_factory failure(1)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				parent->destroy();

				if(inst->is_initialized()) {
					std::cerr << "----!ptce_test_singleton_acquire_uid_factory failure(2)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
			} catch(std::runtime_error &exc) {
				std::cerr << "----!ptce_test_singleton_acquire_uid_factory exception(0): " << exc.what() << std::endl;
				result = PTCE_TEST_FAILURE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}

		ptce_test_t 
		ptce_test_singleton_destroy(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				inst = ptce::acquire();
				if(!inst) {
					result = PTCE_TEST_INCONCLUSIVE;
					goto exit;
				}

				inst->initialize();

				try {
					inst->destroy();

					if(inst->is_initialized()) {
						std::cerr << "----!ptce_test_singleton_destroy failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_singleton_destroy exception(0): " << exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}

		ptce_test_t 
		ptce_test_singleton_initialize(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				inst = ptce::acquire();
				if(!inst) {
					result = PTCE_TEST_INCONCLUSIVE;
					goto exit;
				}

				try {
					inst->initialize();

					if(!inst->is_initialized()) {
						std::cerr << "----!ptce_test_singleton_initialize failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_singleton_initialize exception(0): " << exc.what() << std::endl;
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
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}

		ptce_test_t 
		ptce_test_singleton_is_allocated(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				inst = ptce::acquire();
				if(!inst) {
					result = PTCE_TEST_INCONCLUSIVE;
					goto exit;
				}

				try {

					if(!ptce::is_allocated()) {
						std::cerr << "----!ptce_test_singleton_is_allocated failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_singleton_is_allocated exception(0): " << exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				ptce_destroy();

				try {

					if(ptce::is_allocated()) {
						std::cerr << "----!ptce_test_singleton_is_allocated failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_singleton_is_allocated exception(1): " << exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}

		ptce_test_t 
		ptce_test_singleton_is_initialized(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				inst = ptce::acquire();
				if(!inst) {
					result = PTCE_TEST_INCONCLUSIVE;
					goto exit;
				}

				try {

					if(inst->is_initialized()) {
						std::cerr << "----!ptce_test_singleton_is_initialized failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_singleton_is_initialized exception(0): " << exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->initialize();

				try {

					if(!inst->is_initialized()) {
						std::cerr << "----!ptce_test_singleton_is_initialized failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_singleton_is_initialized exception(1): " << exc.what() << std::endl;
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
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}

		ptce_test_t 
		ptce_test_singleton_release_board_factory(void)
		{
			ptce_ptr parent = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				parent = ptce::acquire();
				parent->initialize();

				try {
					ptce::release_board_factory();

					if(ptce_board_factory::is_allocated()) {
						std::cerr << "----!ptce_test_singleton_release_board_factory failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					parent->acquire_board_factory();
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_singleton_release_board_factory exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				parent->destroy();
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
		ptce_test_singleton_release_node_factory(void)
		{
			ptce_ptr parent = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				parent = ptce::acquire();
				parent->initialize();

				try {
					ptce::release_node_factory();

					if(ptce_node_factory::is_allocated()) {
						std::cerr << "----!ptce_test_singleton_release_node_factory failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					parent->acquire_node_factory();
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_singleton_release_node_factory exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				parent->destroy();
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
		ptce_test_singleton_release_piece_factory(void)
		{
			ptce_ptr parent = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				parent = ptce::acquire();
				parent->initialize();

				try {
					ptce::release_piece_factory();

					if(ptce_piece_factory::is_allocated()) {
						std::cerr << "----!ptce_test_singleton_release_piece_factory failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					parent->acquire_piece_factory();
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_singleton_release_piece_factory exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				parent->destroy();
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
		ptce_test_singleton_release_uid_factory(void)
		{
			ptce_ptr parent = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				parent = ptce::acquire();
				parent->initialize();

				try {
					ptce::release_uid_factory();

					if(ptce_uid_factory::is_allocated()) {
						std::cerr << "----!ptce_test_singleton_release_uid_factory failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					parent->acquire_uid_factory();
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_singleton_release_uid_factory exception(0): " 
							<< exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				parent->destroy();
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
		ptce_test_singleton_version(void)
		{
			std::stringstream ver_test;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				ver_test << VERSION_MAJ << "." << VERSION_MIN << "." << VERSION_WEEK
						<< "-" << VERSION_REV;

				if(ptce::version() != ver_test.str()) {
					std::cerr << "----!ptce_test_singleton_version failure(0)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}
			} catch(...) {
				result = PTCE_TEST_INCONCLUSIVE;
				goto exit;
			}

			result = PTCE_TEST_SUCCESS;

exit:
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}
	}
}
