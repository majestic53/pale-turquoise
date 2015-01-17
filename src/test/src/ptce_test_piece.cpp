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
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_piece piece0, piece1(PIECE_KING, PIECE_BLACK);

				try {
					piece0 = piece1;

					if((piece0.id() != piece1.id())
							|| (piece0.color() != piece1.color())
							|| (piece0.type() != piece1.type())) {
						std::cerr << "----!ptce_test_piece_assignment failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_assignment exception(0): " 
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
		ptce_test_piece_color(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_piece piece;

				try {

					if(piece.color() != PIECE_WHITE) {
						std::cerr << "----!ptce_test_piece_color failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					piece.color() = PIECE_BLACK;

					if(piece.color() != PIECE_BLACK) {
						std::cerr << "----!ptce_test_piece_color failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_color exception(0): " 
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
		ptce_test_piece_constructor(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// default constructor
					{
						ptce_piece piece;

						if((piece.color() != PIECE_WHITE) 
								|| (piece.type() != PIECE_EMPTY)) {
							std::cerr << "----!ptce_test_piece_constructor failure(0)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					}

					// constructor w/ parameters
					{
						ptce_piece piece(PIECE_KING, PIECE_BLACK);

						if((piece.color() != PIECE_BLACK) 
								|| (piece.type() != PIECE_KING)) {
							std::cerr << "----!ptce_test_piece_constructor failure(1)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					}

					// constructor w/ assignment
					{
						ptce_piece piece(ptce_piece(PIECE_KING, PIECE_BLACK));

						if((piece.color() != PIECE_BLACK) 
								|| (piece.type() != PIECE_KING)) {
							std::cerr << "----!ptce_test_piece_constructor failure(2)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_constructor exception(0): " 
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
		ptce_test_piece_equals(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_piece piece0, piece1(PIECE_KING, PIECE_BLACK);

				try {

					if(piece0 == piece1) {
						std::cerr << "----!ptce_test_piece_equals failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					piece0.color() = PIECE_BLACK;
					piece0.type() = PIECE_KING;

					if(piece0 == piece1) {
						std::cerr << "----!ptce_test_piece_equals failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					piece0 = piece1;

					if(!(piece0 == piece1)) {
						std::cerr << "----!ptce_test_piece_equals failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_equals exception(0): " 
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
		ptce_test_piece_factory_acquire(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					fact_inst = ptce_piece_factory::acquire();
					if(!fact_inst) {
						std::cerr << "----!ptce_test_piece_factory_acquire failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(!fact_inst->is_allocated()) {
						std::cerr << "----!ptce_test_piece_factory_acquire failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
				ptce_piece piece;

				try {
					piece = fact_inst->generate(PIECE_KING, PIECE_BLACK);

					if(!fact_inst->contains(piece)) {
						std::cerr << "----!ptce_test_piece_factory_contains failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->decrement_reference(piece);

					if(fact_inst->contains(piece)) {
						std::cerr << "----!ptce_test_piece_factory_contains failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
				ptce_piece piece = fact_inst->generate(PIECE_KING, PIECE_BLACK);
				fact_inst->increment_reference(piece);

				try {
					
					if((fact_inst->decrement_reference(piece) != 1)
							|| (fact_inst->reference_count(piece) != 1)) {
						std::cerr << "----!ptce_test_piece_factory_decrement_reference failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(fact_inst->decrement_reference(piece)
							|| fact_inst->contains(piece)) {
						std::cerr << "----!ptce_test_piece_factory_decrement_reference failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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

					if(fact_inst->is_initialized()) {
						fact_inst->destroy();
					}

					try {
						fact_inst->destroy();
						std::cerr << "----!ptce_test_piece_factory_destroy failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					if(fact_inst->is_initialized()) {
						std::cerr << "----!ptce_test_piece_factory_destroy failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
				ptce_piece piece;

				try {
					piece = fact_inst->generate(PIECE_KING, PIECE_BLACK);

					if((piece.type() != PIECE_KING)
							|| (piece.color() != PIECE_BLACK)) {
						std::cerr << "----!ptce_test_piece_factory_generate failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(!fact_inst->contains(piece)) {
						std::cerr << "----!ptce_test_piece_factory_generate failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(fact_inst->reference_count(piece) != PTCE_INIT_REF_DEF) {
						std::cerr << "----!ptce_test_piece_factory_generate failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
				ptce_piece piece = fact_inst->generate(PIECE_KING, PIECE_BLACK);

				try {

					if((fact_inst->increment_reference(piece) != 2)
							|| (fact_inst->reference_count(piece) != 2)) {
						std::cerr << "----!ptce_test_piece_factory_increment_reference failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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

				if(fact_inst->is_initialized()) {
					fact_inst->destroy();
				}

				try {
					fact_inst->initialize();

					if(!fact_inst->is_initialized()) {
						std::cerr << "----!ptce_test_piece_factory_initialize failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					try {
						fact_inst->initialize();
						std::cerr << "----!ptce_test_piece_factory_initialize failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					} catch(...) { }
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
			ptce_piece_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				try {

					inst = ptce_piece_factory::acquire();
					if(!inst) {
						result = PTCE_TEST_INCONCLUSIVE;
						goto exit;
					}

					try {

						if(!ptce_piece_factory::is_allocated()) {
							std::cerr << "----!ptce_test_piece_factory_is_allocated failure(0)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					} catch(std::runtime_error &exc) {
						std::cerr << "----!ptce_test_piece_factory_is_allocated exception(0): " 
								<< exc.what() << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					ptce::release_piece_factory();

					try {

						if(ptce_piece_factory::is_allocated()) {
							std::cerr << "----!ptce_test_piece_factory_is_allocated failure(1)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					} catch(std::runtime_error &exc) {
						std::cerr << "----!ptce_test_piece_factory_is_allocated exception(1): " 
								<< exc.what() << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_factory_is_allocated exception(0): " 
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
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
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
				fact_inst->initialize();

				try {

					if(!fact_inst->is_initialized()) {
						std::cerr << "----!ptce_test_piece_factory_is_initialized failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->destroy();

					if(fact_inst->is_initialized()) {
						std::cerr << "----!ptce_test_piece_factory_is_initialized failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
			ptce_piece piece;
			ptce_ptr inst = NULL;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_piece_factory();
				piece = fact_inst->generate(PIECE_KING, PIECE_BLACK);

				try {

					if(fact_inst->reference_count(piece) != PTCE_INIT_REF_DEF) {
						std::cerr << "----!ptce_test_piece_factory_reference_count failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->increment_reference(piece);

					if(fact_inst->reference_count(piece) != PTCE_INIT_REF_DEF + 1) {
						std::cerr << "----!ptce_test_piece_factory_reference_count failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->decrement_reference(piece);

					if(fact_inst->reference_count(piece) != PTCE_INIT_REF_DEF) {
						std::cerr << "----!ptce_test_piece_factory_reference_count failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}		
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
			ptce_piece piece0, piece1;
			ptce_piece_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_piece_factory();

				try {

					if(fact_inst->size()) {
						std::cerr << "----!ptce_test_piece_factory_size failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					piece0 = fact_inst->generate(PIECE_KING, PIECE_BLACK);

					if(fact_inst->size() != 1) {
						std::cerr << "----!ptce_test_piece_factory_size failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					piece1 = fact_inst->generate(PIECE_KING, PIECE_BLACK);

					if(fact_inst->size() != 2) {
						std::cerr << "----!ptce_test_piece_factory_size failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->decrement_reference(piece0);
					fact_inst->decrement_reference(piece1);

					if(fact_inst->size()) {
						std::cerr << "----!ptce_test_piece_factory_size failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_piece piece0, piece1(PIECE_KING, PIECE_BLACK);

				try {
					
					if(!(piece0 != piece1)) {
						std::cerr << "----!ptce_test_piece_not_equals failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					piece0.color() = PIECE_BLACK;
					piece1.type() = PIECE_KING;

					if(!(piece0 != piece1)) {
						std::cerr << "----!ptce_test_piece_not_equals failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					piece0 = piece1;

					if(piece0 != piece1) {
						std::cerr << "----!ptce_test_piece_not_equals failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_not_equals exception(0): " 
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
		ptce_test_piece_type(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_piece piece;

				try {

					if(piece.type() != PIECE_EMPTY) {
						std::cerr << "----!ptce_test_piece_type failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					piece.type() = PIECE_KING;

					if(piece.type() != PIECE_KING) {
						std::cerr << "----!ptce_test_piece_type failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_piece_type exception(0): " 
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
