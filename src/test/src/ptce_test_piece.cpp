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
#include "../include/ptce_test_piece.h"

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		ptce_test_t 
		ptce_test_piece_assignment(void)
		{
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_assignment exception(0): " 
							<< exc.what() << std::endl;
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
		ptce_test_piece_color(void)
		{
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_color exception(0): " 
							<< exc.what() << std::endl;
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
		ptce_test_piece_constructor(void)
		{
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_constructor exception(0): " 
							<< exc.what() << std::endl;
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
		ptce_test_piece_equals(void)
		{
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_equals exception(0): " 
							<< exc.what() << std::endl;
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
		ptce_test_piece_factory_acquire(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_piece_factory();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_factory_acquire exception(0): " 
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
		ptce_test_piece_factory_contains(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_piece_factory();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_factory_contains exception(0): " 
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
		ptce_test_piece_factory_decrement_reference(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_piece_factory();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_factory_decrement_reference exception(0): " 
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
		ptce_test_piece_factory_destroy(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_piece_factory();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_factory_destroy exception(0): " 
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
		ptce_test_piece_factory_generate(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_piece_factory();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_factory_generate exception(0): " 
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
		ptce_test_piece_factory_increment_reference(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_piece_factory();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_factory_increment_reference exception(0): " 
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
		ptce_test_piece_factory_initialize(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_piece_factory();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_factory_initialize exception(0): " 
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
		ptce_test_piece_factory_is_allocated(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_piece_factory();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_factory_is_allocated exception(0): " 
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
		ptce_test_piece_factory_is_initialized(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_piece_factory();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_factory_is_initialized exception(0): " 
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
		ptce_test_piece_factory_reference_count(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_piece_factory();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_factory_reference_count exception(0): " 
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
		ptce_test_piece_factory_size(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_piece_factory();

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_factory_size exception(0): " 
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
		ptce_test_piece_not_equals(void)
		{
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_not_equals exception(0): " 
							<< exc.what() << std::endl;
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
		ptce_test_piece_type(void)
		{
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				try {

					// TODO

				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_type exception(0): " 
							<< exc.what() << std::endl;
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
