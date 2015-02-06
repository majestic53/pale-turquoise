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

		#define BOARD_PIECE_LEN 32
		#define BOARD_PIECE_COLOR_LEN (BOARD_PIECE_LEN / 2)

		void 
		append_test_move_set(
			__inout std::set<ptce_mv_ent_t> &set,
			__in ptce_mv_t type,
			__in_opt const ptce_pos_t &old_position = INVALID_POS,
			__in_opt const ptce_pos_t &new_position = INVALID_POS,
			__in_opt const ptce_pos_t &old_position_aux = INVALID_POS,
			__in_opt const ptce_pos_t &new_position_aux = INVALID_POS
			)
		{
			ptce_mv_ent_t entry;

			TRACE_ENTRY();

			entry.first = type;

			if((old_position.first != INVALID_POS.first)
					&&  (old_position.second != INVALID_POS.second)
					&& (new_position.first != INVALID_POS.first)
					&& (new_position.second != INVALID_POS.second)) {
				entry.second.insert(std::pair<ptce_pos_t, ptce_pos_t>(old_position, new_position));
			}

			if((old_position_aux.first != INVALID_POS.first)
					&&  (old_position_aux.second != INVALID_POS.second)
					&& (new_position_aux.first != INVALID_POS.first)
					&& (new_position_aux.second != INVALID_POS.second)) {
				entry.second.insert(std::pair<ptce_pos_t, ptce_pos_t>(old_position_aux, new_position_aux));
			}

			set.insert(entry);

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		void 
		append_test_score_move_set(
			__inout std::set<std::pair<ptce_mv_ent_t, size_t>> &set,
			__in ptce_mv_t type,
			__in size_t score,
			__in_opt const ptce_pos_t &old_position = INVALID_POS,
			__in_opt const ptce_pos_t &new_position = INVALID_POS,
			__in_opt const ptce_pos_t &old_position_aux = INVALID_POS,
			__in_opt const ptce_pos_t &new_position_aux = INVALID_POS
			)
		{
			ptce_mv_ent_t entry;

			TRACE_ENTRY();

			entry.first = type;

			if((old_position.first != INVALID_POS.first)
					&&  (old_position.second != INVALID_POS.second)
					&& (new_position.first != INVALID_POS.first)
					&& (new_position.second != INVALID_POS.second)) {
				entry.second.insert(std::pair<ptce_pos_t, ptce_pos_t>(old_position, new_position));
			}

			if((old_position_aux.first != INVALID_POS.first)
					&&  (old_position_aux.second != INVALID_POS.second)
					&& (new_position_aux.first != INVALID_POS.first)
					&& (new_position_aux.second != INVALID_POS.second)) {
				entry.second.insert(std::pair<ptce_pos_t, ptce_pos_t>(old_position_aux, new_position_aux));
			}

			set.insert(std::pair<ptce_mv_ent_t, size_t>(entry, score));

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		bool 
		compare_test_move_sets(
			__in const std::set<ptce_mv_ent_t> &left,
			__in const std::set<ptce_mv_ent_t> &right
			)
		{
			bool result;

			std::set<ptce_mv_ent_t>::const_iterator left_iter, right_iter;
			std::set<std::pair<ptce_pos_t, ptce_pos_t>>::iterator left_pos_iter, right_pos_iter;

			TRACE_ENTRY();

			result = (left.size() == right.size());
			if(result) {

				for(left_iter = left.begin(), right_iter = right.begin();
						left_iter != left.end(); ++left_iter, ++right_iter) {
					
					result = ((left_iter->first == right_iter->first)
							&& (left_iter->second.size() == right_iter->second.size()));
					if(result) {

						for(left_pos_iter = left_iter->second.begin(), right_pos_iter = right_iter->second.begin();
								left_pos_iter != left_iter->second.end(); ++left_pos_iter, ++right_pos_iter) {

							result = ((left_pos_iter->first.first == right_pos_iter->first.first)
									&& (left_pos_iter->first.second == right_pos_iter->first.second)
									&& (left_pos_iter->second.first == right_pos_iter->second.first)
									&& (left_pos_iter->second.second == right_pos_iter->second.second));

							if(!result) {
								break;
							}
						}
					}

					if(!result) {
						break;
					}
				}
			}

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool 
		compare_test_score_move_sets(
			__in const std::set<std::pair<ptce_mv_ent_t, size_t>> &left,
			__in const std::set<std::pair<ptce_mv_ent_t, size_t>> &right
			)
		{
			bool result;

			std::set<std::pair<ptce_mv_ent_t, size_t>>::const_iterator left_iter, right_iter;
			std::set<std::pair<ptce_pos_t, ptce_pos_t>>::iterator left_pos_iter, right_pos_iter;

			TRACE_ENTRY();

			result = (left.size() == right.size());
			if(result) {

				for(left_iter = left.begin(), right_iter = right.begin();
						left_iter != left.end(); ++left_iter, ++right_iter) {
					
					result = ((left_iter->first == right_iter->first)
							&& (left_iter->second == right_iter->second)
							&& (left_iter->first.second.size() == right_iter->first.second.size()));
					if(result) {

						for(left_pos_iter = left_iter->first.second.begin(), right_pos_iter = right_iter->first.second.begin();
								left_pos_iter != left_iter->first.second.end(); ++left_pos_iter, ++right_pos_iter) {

							result = ((left_pos_iter->first.first == right_pos_iter->first.first)
									&& (left_pos_iter->first.second == right_pos_iter->first.second)
									&& (left_pos_iter->second.first == right_pos_iter->second.first)
									&& (left_pos_iter->second.second == right_pos_iter->second.second));

							if(!result) {
								break;
							}
						}
					}

					if(!result) {
						break;
					}
				}
			}

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		ptce_test_t 
		ptce_test_board_assignment(void)
		{
			ptce_ptr inst = NULL;
			size_t piece_iter = 0;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board0, board1;
				board1.move(ptce_pos_t(3, 1), ptce_pos_t(3, 3));

				try {
					board0 = board1;

					if((board0.piece_captured() != board1.piece_captured())
							|| (board0.piece_moved() != board1.piece_moved())
							|| (board0.state() != board1.state())
							|| (board0.piece_list().size() != board1.piece_list().size())) {
						std::cerr << "----!ptce_test_board_assignment failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					for(; piece_iter < board1.piece_list().size(); ++piece_iter) {

						if(board0.piece_list().at(piece_iter) != board1.piece_list().at(piece_iter)) {
							std::cerr << "----!ptce_test_board_assignment failure(1)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					}
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
		ptce_test_board_clear(void)
		{
			size_t x, y = 0;
			ptce_ptr inst = NULL;
			ptce_piece board_piece;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board;

				try {
					board.clear();

					for(; y < BOARD_WID; ++y) {

						for(x = 0; x < BOARD_WID; ++x) {

							board_piece = board.piece(ptce_pos_t(x, y));
							if(board_piece.type() != PIECE_EMPTY) {
								std::cerr << "----!ptce_test_board_clear failure(0)" << std::endl;
								result = PTCE_TEST_FAILURE;
								goto exit;
							}
						}
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_clear exception(0): " 
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
			size_t x, y;
			ptce_ptr inst = NULL;
			ptce_piece board_piece;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					// default constructor
					{
						ptce_board board;

						try {
							board.piece_moved();
							std::cerr << "----!ptce_test_board_constructor failure(0)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						} catch(...) { }

						if(board.piece_captured()
								|| (board.state() != BOARD_INACTIVE)
								|| (board.piece_list().size() != BOARD_LEN)) {
							std::cerr << "----!ptce_test_board_constructor failure(1)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					}

					// constructor w/ blank flag
					{
						ptce_board board(true);

						for(y = 0; y < BOARD_WID; ++y) {

							for(x = 0; x < BOARD_WID; ++x) {

								board_piece = board.piece(ptce_pos_t(x, y));
								if((board_piece.type() != PIECE_EMPTY)
										|| (board_piece.color() != PIECE_WHITE)) {
									std::cerr << "----!ptce_test_board_constructor failure(2)" << std::endl;
									result = PTCE_TEST_FAILURE;
									goto exit;
								}								
							}
						}
					}

					// constructor w/ parameter
					{
						ptce_board board0;
						board0.move(ptce_pos_t(3, 1), ptce_pos_t(3, 3));
						ptce_board board1(board0);

						if(board1.piece_captured()
								|| (board1.state() != BOARD_ACTIVE)
								|| (board1.piece_list().size() != BOARD_LEN)) {
							std::cerr << "----!ptce_test_board_constructor failure(3)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}

						if((board1.piece_moved().type() != PIECE_PAWN)
								|| (board1.piece(ptce_pos_t(3, 1)).type() != PIECE_EMPTY) 
								|| (board1.piece(ptce_pos_t(3, 3)).type() != PIECE_PAWN)) {
							std::cerr << "----!ptce_test_board_constructor failure(4)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					}
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
				ptce_board board;

				try {

					try {
						board.contains(ptce_pos_t(8, 8));
						std::cerr << "----!ptce_test_board_contains failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;					
					} catch(...) { }

					if(board.contains(ptce_pos_t(3, 3))) {
						std::cerr << "----!ptce_test_board_contains failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(!board.contains(ptce_pos_t(3, 1))) {
						std::cerr << "----!ptce_test_board_contains failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
				ptce_board board0, board1;
				board1.move(ptce_pos_t(3, 1), ptce_pos_t(3, 3));

				try {

					if(board0 == board1) {
						std::cerr << "----!ptce_test_board_equals failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board0 = board1;
					if(!(board0 == board1)) {
						std::cerr << "----!ptce_test_board_equals failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
		ptce_test_board_factory_acquire(void)
		{
			ptce_ptr inst = NULL;
			ptce_board_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					fact_inst = ptce_board_factory::acquire();
					if(!fact_inst) {
						std::cerr << "----!ptce_test_board_factory_acquire failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(!fact_inst->is_allocated()) {
						std::cerr << "----!ptce_test_board_factory_acquire failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_factory_acquire exception(0): " 
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
		ptce_test_board_factory_contains(void)
		{
			ptce_ptr inst = NULL;
			ptce_board_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_board_factory();
				ptce_board board;

				try {

					if(fact_inst->contains(board)) {
						std::cerr << "----!ptce_test_board_factory_contains failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board = fact_inst->generate();

					if(!fact_inst->contains(board)) {
						std::cerr << "----!ptce_test_board_factory_contains failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->decrement_reference(board);

					if(fact_inst->contains(board)) {
						std::cerr << "----!ptce_test_board_factory_contains failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_factory_contains exception(0): " 
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
		ptce_test_board_factory_decrement_reference(void)
		{
			ptce_ptr inst = NULL;
			ptce_board_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_board_factory();
				ptce_board board = fact_inst->generate();
				fact_inst->increment_reference(board);

				try {
					fact_inst->decrement_reference(board);

					if(fact_inst->reference_count(board) != PTCE_INIT_REF_DEF) {
						std::cerr << "----!ptce_test_board_factory_decrement_reference failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->decrement_reference(board);

					if(fact_inst->contains(board)) {
						std::cerr << "----!ptce_test_board_factory_decrement_reference failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_factory_decrement_reference exception(0): " 
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
		ptce_test_board_factory_destroy(void)
		{
			ptce_ptr inst = NULL;
			ptce_board_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_board_factory();

				try {

					if(fact_inst->is_initialized()) {
						fact_inst->destroy();
					}

					if(fact_inst->is_initialized()) {
						std::cerr << "----!ptce_test_board_factory_destroy failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_factory_destroy exception(0): " 
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
		ptce_test_board_factory_generate(void)
		{
			ptce_ptr inst = NULL;
			ptce_board_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_board_factory();
				ptce_board board;

				try {
					board = fact_inst->generate();

					if(fact_inst->size() != 1) {
						std::cerr << "----!ptce_test_board_factory_generate failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(!fact_inst->contains(board)
							|| (fact_inst->reference_count(board) != PTCE_INIT_REF_DEF)) {
						std::cerr << "----!ptce_test_board_factory_generate failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_factory_generate exception(0): " 
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
		ptce_test_board_factory_increment_reference(void)
		{
			ptce_ptr inst = NULL;
			ptce_board_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_board_factory();
				ptce_board board = fact_inst->generate();

				try {
					fact_inst->increment_reference(board);

					if(fact_inst->reference_count(board) != (PTCE_INIT_REF_DEF + 1)) {
						std::cerr << "----!ptce_test_board_factory_increment_reference failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_factory_increment_reference exception(0): " 
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
		ptce_test_board_factory_initialize(void)
		{
			ptce_ptr inst = NULL;
			ptce_board_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_board_factory();

				try {

					if(fact_inst->is_initialized()) {
						fact_inst->destroy();
					}

					fact_inst->initialize();

					if(!fact_inst->is_initialized()
							|| fact_inst->size()) {
						std::cerr << "----!ptce_test_board_factory_initialize failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_factory_initialize exception(0): " 
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
		ptce_test_board_factory_is_allocated(void)
		{
			ptce_board_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				try {

					inst = ptce_board_factory::acquire();
					if(!inst) {
						result = PTCE_TEST_INCONCLUSIVE;
						goto exit;
					}

					try {

						if(!ptce_board_factory::is_allocated()) {
							std::cerr << "----!ptce_test_board_factory_is_allocated failure(0)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					} catch(std::runtime_error &exc) {
						std::cerr << "----!ptce_test_board_factory_is_allocated exception(0): " 
								<< exc.what() << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					ptce::release_board_factory();

					try {

						if(ptce_board_factory::is_allocated()) {
							std::cerr << "----!ptce_test_board_factory_is_allocated failure(1)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					} catch(std::runtime_error &exc) {
						std::cerr << "----!ptce_test_board_factory_is_allocated exception(1): " 
								<< exc.what() << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_factory_is_allocated exception(0): " 
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
		ptce_test_board_factory_is_initialized(void)
		{
			ptce_ptr inst = NULL;
			ptce_board_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_board_factory();

				try {

					if(fact_inst->is_initialized()) {
						fact_inst->destroy();
					}

					if(fact_inst->is_initialized()) {
						std::cerr << "----!ptce_test_board_factory_is_initialized failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->initialize();

					if(!fact_inst->is_initialized()) {
						std::cerr << "----!ptce_test_board_factory_is_initialized failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_factory_is_initialized exception(0): " 
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
		ptce_test_board_factory_reference_count(void)
		{
			ptce_ptr inst = NULL;
			ptce_board_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_board_factory();
				ptce_board board;

				try {
					board = fact_inst->generate();

					if(fact_inst->reference_count(board) != PTCE_INIT_REF_DEF) {
						std::cerr << "----!ptce_test_board_factory_reference_count failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->increment_reference(board);

					if(fact_inst->reference_count(board) != (PTCE_INIT_REF_DEF + 1)) {
						std::cerr << "----!ptce_test_board_factory_reference_count failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->decrement_reference(board);

					if(fact_inst->reference_count(board) != PTCE_INIT_REF_DEF) {
						std::cerr << "----!ptce_test_board_factory_reference_count failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->decrement_reference(board);

					try {
						fact_inst->reference_count(board);
						std::cerr << "----!ptce_test_board_factory_reference_count failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					} catch(...) { }
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_factory_reference_count exception(0): " 
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
		ptce_test_board_factory_size(void)
		{
			ptce_ptr inst = NULL;
			ptce_board_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_board_factory();
				ptce_board board;

				try {

					if(fact_inst->size()) {
						std::cerr << "----!ptce_test_board_factory_size failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board = fact_inst->generate();

					if(fact_inst->size() != 1) {
						std::cerr << "----!ptce_test_board_factory_size failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->decrement_reference(board);

					if(fact_inst->size()) {
						std::cerr << "----!ptce_test_board_factory_size failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_factory_size exception(0): " 
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
		ptce_test_board_generate_moves_bishop(void)
		{
			ptce_ptr inst = NULL;
			std::set<ptce_mv_ent_t> move_set;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(2, 1));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_bishop failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(4, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(5, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(6, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(7, 6));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_bishop failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 4), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(4, 3));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(5, 4));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_bishop failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 4), PIECE_PAWN, PIECE_BLACK);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(4, 3));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(1, 0), ptce_pos_t(5, 4));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_bishop failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_BISHOP, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(0, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(7, 7));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(0, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 0));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_bishop failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 5), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 5), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(5, 1));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_bishop failure(5)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(1, 5), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(5, 5), PIECE_PAWN, PIECE_BLACK);
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(5, 1));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_bishop failure(6)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 5), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 7), PIECE_KING, PIECE_BLACK);
					append_test_move_set(move_set, MOVE_CHECK, ptce_pos_t(3, 5), ptce_pos_t(5, 7));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 5), ptce_pos_t(0, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 5), ptce_pos_t(1, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 5), ptce_pos_t(1, 7));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 5), ptce_pos_t(2, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 5), ptce_pos_t(2, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 5), ptce_pos_t(4, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 5), ptce_pos_t(4, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 5), ptce_pos_t(5, 3));					
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 5), ptce_pos_t(6, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 5), ptce_pos_t(7, 1));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 5), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_bishop failure(7)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_generate_moves_bishop exception(0): " 
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
		ptce_test_board_generate_moves_king(void)
		{
			ptce_ptr inst = NULL;
			std::set<ptce_mv_ent_t> move_set;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_KING, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 0), ptce_pos_t(2, 0));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 0), ptce_pos_t(2, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 0), ptce_pos_t(3, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 0), ptce_pos_t(4, 0));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 0), ptce_pos_t(4, 1));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_king failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_KING, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(4, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 0), ptce_pos_t(2, 1));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 0), ptce_pos_t(3, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 0), ptce_pos_t(4, 1));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_king failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_KING, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 4));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_king failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_ROOK, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 0), PIECE_KING, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(7, 0), PIECE_ROOK, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_CASTLE, ptce_pos_t(4, 0), ptce_pos_t(2, 0), 
							ptce_pos_t(0, 0), ptce_pos_t(3, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(4, 0), ptce_pos_t(3, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(4, 0), ptce_pos_t(3, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(4, 0), ptce_pos_t(4, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(4, 0), ptce_pos_t(5, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(4, 0), ptce_pos_t(5, 1));
					append_test_move_set(move_set, MOVE_CASTLE, ptce_pos_t(4, 0), ptce_pos_t(6, 0), 
							ptce_pos_t(7, 0), ptce_pos_t(5, 0));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(4, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_king failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_ROOK, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 7), PIECE_ROOK, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(4, 0), PIECE_KING, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(6, 7), PIECE_ROOK, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(7, 0), PIECE_ROOK, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(4, 0), ptce_pos_t(3, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(4, 0), ptce_pos_t(3, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(4, 0), ptce_pos_t(4, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(4, 0), ptce_pos_t(5, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(4, 0), ptce_pos_t(5, 1));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(4, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_king failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 0), PIECE_KING, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_BLACK, true);
					board.generate_piece(ptce_pos_t(5, 2), PIECE_PAWN, PIECE_BLACK, true);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(2, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(2, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(3, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(4, 0));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_king failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_generate_moves_king exception(0): " 
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
		ptce_test_board_generate_moves_knight(void)
		{
			ptce_ptr inst = NULL;
			std::set<ptce_mv_ent_t> move_set;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_KNIGHT, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(0, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(3, 1));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_knight failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 2), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_KNIGHT, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 2), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(1, 0), ptce_pos_t(0, 2));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(1, 0), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(3, 1));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_knight failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 2), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_KNIGHT, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 2), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(0, 2));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(3, 1));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_knight failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_KNIGHT, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 4));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_knight failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(1, 2), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(1, 4), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(2, 5), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_KNIGHT, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(4, 5), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(5, 2), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(5, 4), PIECE_PAWN, PIECE_BLACK);
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(1, 2));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(1, 4));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(2, 1));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(2, 5));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(4, 1));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(4, 5));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(5, 2));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(5, 4));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_knight failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(1, 2), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 4), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 5), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_KNIGHT, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 5), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 2), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 4), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(1, 2));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(1, 4));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(2, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(2, 5));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(4, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(4, 5));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(5, 2));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(5, 4));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_knight failure(5)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(5, 5), PIECE_KNIGHT, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(6, 7), PIECE_KING, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(7, 6), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(5, 5), ptce_pos_t(3, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(5, 5), ptce_pos_t(3, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(5, 5), ptce_pos_t(4, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(5, 5), ptce_pos_t(4, 7));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(5, 5), ptce_pos_t(6, 3));
					append_test_move_set(move_set, MOVE_CHECK, ptce_pos_t(5, 5), ptce_pos_t(6, 7));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(5, 5), ptce_pos_t(7, 4));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(5, 5), ptce_pos_t(7, 6));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(5, 5), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_knight failure(6)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_generate_moves_knight exception(0): " 
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
		ptce_test_board_generate_moves_pawn(void)
		{
			ptce_ptr inst = NULL;
			std::set<ptce_mv_ent_t> move_set;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 1), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 1), ptce_pos_t(3, 3));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 1), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 1), ptce_pos_t(4, 2));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 1), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 2), PIECE_PAWN, PIECE_BLACK, true);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 1), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 1), ptce_pos_t(4, 2));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 1), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_PAWN, PIECE_BLACK, true);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 1), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 1), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 1), ptce_pos_t(4, 2));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 1), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 2), PIECE_PAWN, PIECE_WHITE, true);
					board.generate_piece(ptce_pos_t(2, 2), PIECE_PAWN, PIECE_BLACK, true);
					board.generate_piece(ptce_pos_t(4, 2), PIECE_PAWN, PIECE_BLACK, true);
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 1), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 1), ptce_pos_t(4, 2));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 1), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 2), PIECE_PAWN, PIECE_WHITE, true);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 2), ptce_pos_t(3, 3));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 2), ptce_pos_t(2, 3));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 2), ptce_pos_t(4, 3));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 2), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 2), PIECE_PAWN, PIECE_WHITE, true);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_PAWN, PIECE_BLACK, true);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 2), ptce_pos_t(2, 3));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 2), ptce_pos_t(4, 3));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 2), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(5)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 2), PIECE_PAWN, PIECE_WHITE, true);
					board.generate_piece(ptce_pos_t(2, 3), PIECE_PAWN, PIECE_BLACK, true);
					board.generate_piece(ptce_pos_t(4, 3), PIECE_PAWN, PIECE_BLACK, true);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 2), ptce_pos_t(3, 3));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 2), ptce_pos_t(2, 3));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 2), ptce_pos_t(4, 3));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 2), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(6)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(2, 6), PIECE_PAWN, PIECE_WHITE, true);
					board.generate_piece(ptce_pos_t(3, 7), PIECE_KING, PIECE_BLACK, true);
					append_test_move_set(move_set, MOVE_CHECK, ptce_pos_t(2, 6), ptce_pos_t(3, 7));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(2, 6), ptce_pos_t(2, 7));
					append_test_move_set(move_set, MOVE_PROMOTE, ptce_pos_t(2, 6), ptce_pos_t(2, 7));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(2, 6), ptce_pos_t(1, 7));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(2, 6), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(7)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(2, 7), PIECE_PAWN, PIECE_WHITE, true);					

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(2, 7), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(8)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_generate_moves_pawn exception(0): " 
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
		ptce_test_board_generate_moves_queen(void)
		{
			ptce_ptr inst = NULL;
			std::set<ptce_mv_ent_t> move_set;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(0, 0));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(1, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(2, 0));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(2, 1));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(0, 0));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(1, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(2, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(4, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(5, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(6, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(7, 6));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 3), PIECE_PAWN, PIECE_BLACK);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(0, 0));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(1, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(2, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(1, 0), ptce_pos_t(4, 3));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 3), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(0, 0));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(1, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(2, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(1, 0), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(1, 0), ptce_pos_t(4, 3));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_QUEEN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(0, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(0, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(0, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 7));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(7, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(7, 7));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(0, 3), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(0, 6), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 7), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(6, 0), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(7, 3), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(7, 7), PIECE_PAWN, PIECE_BLACK);
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(0, 0));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(0, 3));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(0, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(3, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 6));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(3, 7));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(6, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 6));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(7, 3));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(3, 3), ptce_pos_t(7, 7));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 3), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 6), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 7), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(6, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(7, 3), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(7, 7), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(0, 0));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(0, 3));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(0, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(3, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 6));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(3, 7));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(6, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 6));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(7, 3));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(3, 3), ptce_pos_t(7, 7));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(5)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 7), PIECE_KING, PIECE_BLACK);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(0, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(0, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(0, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 6));
					append_test_move_set(move_set, MOVE_CHECK, ptce_pos_t(3, 3), ptce_pos_t(3, 7));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(7, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(7, 7));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(6)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(7, 7), PIECE_KING, PIECE_BLACK);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(0, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(0, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(0, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(3, 7));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(6, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 3), ptce_pos_t(7, 3));
					append_test_move_set(move_set, MOVE_CHECK, ptce_pos_t(3, 3), ptce_pos_t(7, 7));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(7)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_generate_moves_queen exception(0): " 
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
		ptce_test_board_generate_moves_rook(void)
		{
			ptce_ptr inst = NULL;
			std::set<ptce_mv_ent_t> move_set;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(0, 0), PIECE_ROOK, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(0, 0), ptce_pos_t(0, 1));
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(0, 0), ptce_pos_t(1, 0));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(0, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_rook failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_ROOK, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_PAWN, PIECE_BLACK);
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(0, 0), ptce_pos_t(0, 1));
					append_test_move_set(move_set, MOVE_CAPTURE, ptce_pos_t(0, 0), ptce_pos_t(1, 0));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(0, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_rook failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_ROOK, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_PROTECT, ptce_pos_t(0, 0), ptce_pos_t(0, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(1, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(2, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(3, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(4, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(5, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(6, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(7, 0));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(0, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_rook failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_ROOK, PIECE_WHITE);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(0, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(0, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(0, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(0, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(0, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(0, 6));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(0, 7));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(1, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(2, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(3, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(4, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(5, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(6, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(0, 0), ptce_pos_t(7, 0));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(0, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_rook failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					board.generate_piece(ptce_pos_t(3, 0), PIECE_ROOK, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 7), PIECE_KING, PIECE_BLACK);
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(0, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(1, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(2, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(3, 1));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(3, 2));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(3, 3));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(3, 4));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(3, 5));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(3, 6));
					append_test_move_set(move_set, MOVE_CHECK, ptce_pos_t(3, 0), ptce_pos_t(3, 7));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(4, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(5, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(6, 0));
					append_test_move_set(move_set, MOVE_NORMAL, ptce_pos_t(3, 0), ptce_pos_t(7, 0));

					if(!compare_test_move_sets(board.generate_move_set(ptce_pos_t(3, 0), PIECE_BLACK), 
							move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_rook failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_generate_moves_rook exception(0): " 
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
		ptce_test_board_generate_piece(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece board_piece;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(3, 3), PIECE_BISHOP, PIECE_BLACK, true);

					if(!board.contains(ptce_pos_t(3, 3))) {
						std::cerr << "----!ptce_test_board_generate_piece failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board_piece = board.piece(ptce_pos_t(3, 3));
					if((board_piece.type() != PIECE_BISHOP)
							|| (board_piece.color() != PIECE_BLACK)
							|| !board_piece.moved()) {
						std::cerr << "----!ptce_test_board_generate_piece failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					try {
						board.generate_piece(ptce_pos_t(3, 3), PIECE_KING, PIECE_WHITE);
						std::cerr << "----!ptce_test_board_generate_piece failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					} catch(...) { }
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_generate_piece exception(0): " 
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
		ptce_test_board_is_checkmated(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(3, 3), PIECE_KING, PIECE_WHITE, true);

					if(board.is_checkmated(PIECE_WHITE)) {
						std::cerr << "----!ptce_test_board_is_checkmated failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					board.generate_piece(ptce_pos_t(3, 0), PIECE_KING, PIECE_WHITE, true);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_WHITE);

					if(board.is_checkmated(PIECE_WHITE)) {
						std::cerr << "----!ptce_test_board_is_checkmated failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					board.generate_piece(ptce_pos_t(3, 0), PIECE_KING, PIECE_WHITE, true);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(4, 0), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_BLACK);

					if(board.is_checkmated(PIECE_WHITE)) {
						std::cerr << "----!ptce_test_board_is_checkmated failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					board.generate_piece(ptce_pos_t(3, 0), PIECE_KING, PIECE_WHITE, true);
					board.generate_piece(ptce_pos_t(1, 2), PIECE_BISHOP, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_QUEEN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(4, 0), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(5, 2), PIECE_BISHOP, PIECE_BLACK);

					if(!board.is_checkmated(PIECE_WHITE)) {
						std::cerr << "----!ptce_test_board_is_checkmated failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					board.generate_piece(ptce_pos_t(3, 0), PIECE_KING, PIECE_WHITE, true);
					board.generate_piece(ptce_pos_t(1, 2), PIECE_BISHOP, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_QUEEN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(4, 0), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(5, 2), PIECE_BISHOP, PIECE_BLACK);

					if(!board.is_checkmated(PIECE_WHITE)) {
						std::cerr << "----!ptce_test_board_is_checkmated failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_is_checkmated exception(0): " 
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
			size_t black, white;
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board;

				try {

					try {
						board.move(ptce_pos_t(8, 8), ptce_pos_t(8, 8));
						std::cerr << "----!ptce_test_board_move failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					board.move(ptce_pos_t(3, 1), ptce_pos_t(3, 3));

					if(board.piece_captured()
							|| (board.state() != BOARD_ACTIVE)
							|| (board.piece_moved().type() != PIECE_PAWN)
							|| (board.piece_count(white, black) != BOARD_PIECE_LEN)
							|| (white != BOARD_PIECE_COLOR_LEN)
							|| (black != BOARD_PIECE_COLOR_LEN)) {
						std::cerr << "----!ptce_test_board_move failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.move(ptce_pos_t(2, 1), ptce_pos_t(3, 3));

					if(!board.piece_captured()
							|| (board.state() != BOARD_ACTIVE)
							|| (board.piece_moved().type() != PIECE_PAWN)
							|| (board.piece_count(white, black) != (BOARD_PIECE_LEN - 1))
							|| (white != (BOARD_PIECE_COLOR_LEN - 1))
							|| (black != BOARD_PIECE_COLOR_LEN)) {
						std::cerr << "----!ptce_test_board_move failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
				ptce_board board0, board1;
				board1.move(ptce_pos_t(3, 1), ptce_pos_t(3, 3));

				try {

					if(!(board0 != board1)) {
						std::cerr << "----!ptce_test_board_not_equals failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board0 = board1;
					if(board0 != board1) {
						std::cerr << "----!ptce_test_board_not_equals failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
			ptce_piece piece;
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board;

				try {

					piece = board.piece(ptce_pos_t(3, 1));
					if((piece.type() != PIECE_PAWN)
							|| (piece.color() != PIECE_WHITE)) {
						std::cerr << "----!ptce_test_board_piece failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					piece = board.piece(ptce_pos_t(3, 3));
					if((piece.type() != PIECE_EMPTY)
							|| (piece.color() != PIECE_WHITE)) {
						std::cerr << "----!ptce_test_board_piece failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
				ptce_board board;

				try {

					if(board.piece_captured()) {
						std::cerr << "----!ptce_test_board_piece_captured failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.move(ptce_pos_t(3, 1), ptce_pos_t(3, 3));
					board.move(ptce_pos_t(2, 1), ptce_pos_t(3, 3));

					if(!board.piece_captured()) {
						std::cerr << "----!ptce_test_board_piece_captured failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
			size_t black, total, white;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board;

				try {

					total = board.piece_count(white, black);
					if((total != BOARD_PIECE_LEN)
							|| (white != BOARD_PIECE_COLOR_LEN)
							|| (black != BOARD_PIECE_COLOR_LEN)) {
						std::cerr << "----!ptce_test_board_piece_count failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.move(ptce_pos_t(3, 1), ptce_pos_t(3, 3));
					board.move(ptce_pos_t(2, 1), ptce_pos_t(3, 3));

					total = board.piece_count(white, black);
					if((total != (BOARD_PIECE_LEN - 1))
							|| (white != (BOARD_PIECE_COLOR_LEN - 1))
							|| (black != BOARD_PIECE_COLOR_LEN)) {
						std::cerr << "----!ptce_test_board_piece_count failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
		ptce_test_board_piece_list(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board;

				try {

					if(board.piece_list().size() != BOARD_LEN) {
						std::cerr << "----!ptce_test_board_piece_list failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_piece_list exception(0): " 
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
			ptce_uid uid;
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board;
				uid = board.piece(ptce_pos_t(3, 1)).id();
				board.move(ptce_pos_t(3, 1), ptce_pos_t(3, 3));

				try {

					if(board.piece_moved().id() != uid) {
						std::cerr << "----!ptce_test_board_piece_moved failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
		ptce_test_board_piece_moved_coordinate(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board;
				board.move(ptce_pos_t(3, 1), ptce_pos_t(3, 3));

				try {

					if(board.piece_moved_coordinate() != ptce_pos_t(3, 3)) {
						std::cerr << "----!ptce_test_board_piece_moved_coordinate failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_piece_moved_coordinate exception(0): " 
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
		ptce_test_board_remove(void)
		{
			ptce_ptr inst = NULL;
			ptce_piece board_piece;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board;

				try {

					try {
						board.remove(ptce_pos_t(3, 3));
						std::cerr << "----!ptce_test_board_remove failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;	
					} catch(...) { }

					board.remove(ptce_pos_t(3, 1));

					board_piece = board.piece(ptce_pos_t(3, 1));
					if((board_piece.type() != PIECE_EMPTY)
							|| (board_piece.color() != PIECE_WHITE)) {
						std::cerr << "----!ptce_test_board_remove failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_remove exception(0): " 
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
		ptce_test_board_score_moves_bishop(void)
		{
			size_t result_score;
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;
			std::set<std::pair<ptce_mv_ent_t, size_t>> move_set, result_move_set;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN), 
							ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN), 
							ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					result_score = ptce_board::score_move_set(board, PIECE_BISHOP, 
							board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_bishop failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN), 
							ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL), 
							ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL), 
							ptce_pos_t(1, 0), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL), 
							ptce_pos_t(1, 0), ptce_pos_t(4, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL), 
							ptce_pos_t(1, 0), ptce_pos_t(5, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL), 
							ptce_pos_t(1, 0), ptce_pos_t(6, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL), 
							ptce_pos_t(1, 0), ptce_pos_t(7, 6));
					result_score = ptce_board::score_move_set(board, PIECE_BISHOP, 
							board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_bishop failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 4), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN), 
							ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL), 
							ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(4, 3));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(5, 4));
					result_score = ptce_board::score_move_set(board, PIECE_BISHOP, 
							board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_bishop failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 4), PIECE_PAWN, PIECE_BLACK);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(4, 3));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_CAPTURE),
							ptce_pos_t(1, 0), ptce_pos_t(5, 4));
					result_score = ptce_board::score_move_set(board, PIECE_BISHOP, 
							board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_CAPTURE))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_bishop failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_BISHOP, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(0, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(7, 7));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(0, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 0));
					result_score = ptce_board::score_move_set(board, PIECE_BISHOP, 
							board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_bishop failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 5), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 5), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					result_score = ptce_board::score_move_set(board, PIECE_BISHOP, 
							board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_bishop failure(5)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(1, 5), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(5, 5), PIECE_PAWN, PIECE_BLACK);
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					result_score = ptce_board::score_move_set(board, PIECE_BISHOP, 
							board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_CAPTURE))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_bishop failure(6)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 5), PIECE_BISHOP, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 7), PIECE_KING, PIECE_BLACK);
					append_test_score_move_set(move_set, MOVE_CHECK, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_CHECK),
							ptce_pos_t(3, 5), ptce_pos_t(5, 7));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 5), ptce_pos_t(0, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 5), ptce_pos_t(1, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 5), ptce_pos_t(1, 7));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 5), ptce_pos_t(2, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 5), ptce_pos_t(2, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 5), ptce_pos_t(4, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 5), ptce_pos_t(4, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 5), ptce_pos_t(5, 3));					
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 5), ptce_pos_t(6, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_NORMAL),
							ptce_pos_t(3, 5), ptce_pos_t(7, 1));
					result_score = ptce_board::score_move_set(board, PIECE_BISHOP, 
							board.generate_move_set(ptce_pos_t(3, 5), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_BISHOP, MOVE_CHECK))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_bishop failure(7)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_score_moves_bishop exception(0): " 
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
		ptce_test_board_score_moves_king(void)
		{
			size_t result_score;
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;
			std::set<std::pair<ptce_mv_ent_t, size_t>> move_set, result_move_set;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_KING, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 0), ptce_pos_t(2, 0));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 0), ptce_pos_t(2, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 0), ptce_pos_t(3, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 0), ptce_pos_t(4, 0));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 0), ptce_pos_t(4, 1));
					result_score = ptce_board::score_move_set(board, PIECE_KING, 
							board.generate_move_set(ptce_pos_t(3, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_king failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_KING, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(4, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							 ptce_pos_t(3, 0), ptce_pos_t(2, 1));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_CAPTURE),
							ptce_pos_t(3, 0), ptce_pos_t(3, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 0), ptce_pos_t(4, 1));
					result_score = ptce_board::score_move_set(board, PIECE_KING, 
							board.generate_move_set(ptce_pos_t(3, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_CAPTURE))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_king failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_KING, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					result_score = ptce_board::score_move_set(board, PIECE_KING, 
							board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_king failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_ROOK, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 0), PIECE_KING, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(7, 0), PIECE_ROOK, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_CASTLE, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_CASTLE),
							ptce_pos_t(4, 0), ptce_pos_t(2, 0), ptce_pos_t(0, 0), ptce_pos_t(3, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(4, 0), ptce_pos_t(3, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(4, 0), ptce_pos_t(3, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(4, 0), ptce_pos_t(4, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(4, 0), ptce_pos_t(5, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(4, 0), ptce_pos_t(5, 1));
					append_test_score_move_set(move_set, MOVE_CASTLE, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_CASTLE),
							ptce_pos_t(4, 0), ptce_pos_t(6, 0), ptce_pos_t(7, 0), ptce_pos_t(5, 0));
					result_score = ptce_board::score_move_set(board, PIECE_KING, 
							board.generate_move_set(ptce_pos_t(4, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_CASTLE))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_king failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_ROOK, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 7), PIECE_ROOK, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(4, 0), PIECE_KING, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(6, 7), PIECE_ROOK, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(7, 0), PIECE_ROOK, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(4, 0), ptce_pos_t(3, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(4, 0), ptce_pos_t(3, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(4, 0), ptce_pos_t(4, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(4, 0), ptce_pos_t(5, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(4, 0), ptce_pos_t(5, 1));
					result_score = ptce_board::score_move_set(board, PIECE_KING, 
							board.generate_move_set(ptce_pos_t(4, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_king failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 0), PIECE_KING, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_BLACK, true);
					board.generate_piece(ptce_pos_t(5, 2), PIECE_PAWN, PIECE_BLACK, true);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(2, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(2, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(3, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(4, 0));
					result_score = ptce_board::score_move_set(board, PIECE_KING, 
							board.generate_move_set(ptce_pos_t(3, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_KING, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_king failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_score_moves_king exception(0): " 
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
		ptce_test_board_score_moves_knight(void)
		{
			size_t result_score;
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;
			std::set<std::pair<ptce_mv_ent_t, size_t>> move_set, result_move_set;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_KNIGHT, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(0, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(3, 1));
					result_score = ptce_board::score_move_set(board, PIECE_KNIGHT, 
							board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_knight failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 2), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_KNIGHT, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 2), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CAPTURE),
							ptce_pos_t(1, 0), ptce_pos_t(0, 2));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CAPTURE),
							ptce_pos_t(1, 0), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(3, 1));
					result_score = ptce_board::score_move_set(board, PIECE_KNIGHT, 
							board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CAPTURE))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_knight failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 2), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_KNIGHT, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 2), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(0, 2));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(3, 1));
					result_score = ptce_board::score_move_set(board, PIECE_KNIGHT, 
							board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_knight failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_KNIGHT, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 4));
					result_score = ptce_board::score_move_set(board, PIECE_KNIGHT, 
							board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_knight failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(1, 2), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(1, 4), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(2, 5), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_KNIGHT, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(4, 5), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(5, 2), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(5, 4), PIECE_PAWN, PIECE_BLACK);
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(1, 2));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(1, 4));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(2, 1));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(2, 5));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(4, 1));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(4, 5));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(5, 2));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(5, 4));
					result_score = ptce_board::score_move_set(board, PIECE_KNIGHT, 
							board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CAPTURE))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_knight failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(1, 2), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 4), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 5), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_KNIGHT, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 5), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 2), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(5, 4), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(1, 2));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(1, 4));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(2, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(2, 5));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(4, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(4, 5));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(5, 2));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(5, 4));
					result_score = ptce_board::score_move_set(board, PIECE_KNIGHT, 
							board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_knight failure(5)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(5, 5), PIECE_KNIGHT, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(6, 7), PIECE_KING, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(7, 6), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(5, 5), ptce_pos_t(3, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(5, 5), ptce_pos_t(3, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(5, 5), ptce_pos_t(4, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(5, 5), ptce_pos_t(4, 7));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(5, 5), ptce_pos_t(6, 3));
					append_test_score_move_set(move_set, MOVE_CHECK, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CHECK),
							ptce_pos_t(5, 5), ptce_pos_t(6, 7));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_NORMAL),
							ptce_pos_t(5, 5), ptce_pos_t(7, 4));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(5, 5), ptce_pos_t(7, 6));
					result_score = ptce_board::score_move_set(board, PIECE_KNIGHT, 
							board.generate_move_set(ptce_pos_t(5, 5), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_KNIGHT, MOVE_CHECK))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_score_moves_knight failure(6)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_score_moves_knight exception(0): " 
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
		ptce_test_board_score_moves_pawn(void)
		{
			size_t result_score;
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;
			std::set<std::pair<ptce_mv_ent_t, size_t>> move_set, result_move_set;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_NORMAL),
							ptce_pos_t(3, 1), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_NORMAL),
							ptce_pos_t(3, 1), ptce_pos_t(3, 3));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_EMPTY),
							ptce_pos_t(3, 1), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_EMPTY),
							ptce_pos_t(3, 1), ptce_pos_t(4, 2));
					result_score = ptce_board::score_move_set(board, PIECE_PAWN, 
							board.generate_move_set(ptce_pos_t(3, 1), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 2), PIECE_PAWN, PIECE_BLACK, true);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_EMPTY),
							ptce_pos_t(3, 1), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_EMPTY),
							ptce_pos_t(3, 1), ptce_pos_t(4, 2));
					result_score = ptce_board::score_move_set(board, PIECE_PAWN, 
							board.generate_move_set(ptce_pos_t(3, 1), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_EMPTY))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_PAWN, PIECE_BLACK, true);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_NORMAL),
							ptce_pos_t(3, 1), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_EMPTY),
							ptce_pos_t(3, 1), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_EMPTY),
							ptce_pos_t(3, 1), ptce_pos_t(4, 2));
					result_score = ptce_board::score_move_set(board, PIECE_PAWN, 
							board.generate_move_set(ptce_pos_t(3, 1), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 2), PIECE_PAWN, PIECE_WHITE, true);
					board.generate_piece(ptce_pos_t(2, 2), PIECE_PAWN, PIECE_BLACK, true);
					board.generate_piece(ptce_pos_t(4, 2), PIECE_PAWN, PIECE_BLACK, true);
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_CAPTURE),
							ptce_pos_t(3, 1), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_CAPTURE),
							ptce_pos_t(3, 1), ptce_pos_t(4, 2));
					result_score = ptce_board::score_move_set(board, PIECE_PAWN, 
							board.generate_move_set(ptce_pos_t(3, 1), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_CAPTURE))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 2), PIECE_PAWN, PIECE_WHITE, true);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_NORMAL),
							ptce_pos_t(3, 2), ptce_pos_t(3, 3));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_EMPTY),
							ptce_pos_t(3, 2), ptce_pos_t(2, 3));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_EMPTY),
							ptce_pos_t(3, 2), ptce_pos_t(4, 3));
					result_score = ptce_board::score_move_set(board, PIECE_PAWN, 
							board.generate_move_set(ptce_pos_t(3, 2), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 2), PIECE_PAWN, PIECE_WHITE, true);
					board.generate_piece(ptce_pos_t(3, 3), PIECE_PAWN, PIECE_BLACK, true);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_EMPTY),
							ptce_pos_t(3, 2), ptce_pos_t(2, 3));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_EMPTY),
							ptce_pos_t(3, 2), ptce_pos_t(4, 3));
					result_score = ptce_board::score_move_set(board, PIECE_PAWN, 
							board.generate_move_set(ptce_pos_t(3, 2), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_EMPTY))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(5)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 2), PIECE_PAWN, PIECE_WHITE, true);
					board.generate_piece(ptce_pos_t(2, 3), PIECE_PAWN, PIECE_BLACK, true);
					board.generate_piece(ptce_pos_t(4, 3), PIECE_PAWN, PIECE_BLACK, true);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_NORMAL),
							ptce_pos_t(3, 2), ptce_pos_t(3, 3));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_CAPTURE),
							ptce_pos_t(3, 2), ptce_pos_t(2, 3));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_CAPTURE),
							ptce_pos_t(3, 2), ptce_pos_t(4, 3));
					result_score = ptce_board::score_move_set(board, PIECE_PAWN, 
							board.generate_move_set(ptce_pos_t(3, 2), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_CAPTURE))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(6)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(2, 6), PIECE_PAWN, PIECE_WHITE, true);
					board.generate_piece(ptce_pos_t(3, 7), PIECE_KING, PIECE_BLACK, true);
					append_test_score_move_set(move_set, MOVE_CHECK, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_CHECK),
							ptce_pos_t(2, 6), ptce_pos_t(3, 7));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_NORMAL),
							ptce_pos_t(2, 6), ptce_pos_t(2, 7));
					append_test_score_move_set(move_set, MOVE_PROMOTE, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROMOTE),
							ptce_pos_t(2, 6), ptce_pos_t(2, 7));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_EMPTY),
							ptce_pos_t(2, 6), ptce_pos_t(1, 7));
					result_score = ptce_board::score_move_set(board, PIECE_PAWN, 
							board.generate_move_set(ptce_pos_t(2, 6), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_PAWN, MOVE_CHECK))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(7)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(2, 7), PIECE_PAWN, PIECE_WHITE, true);					
					result_score = ptce_board::score_move_set(board, PIECE_PAWN, 
							board.generate_move_set(ptce_pos_t(2, 7), PIECE_BLACK), result_move_set);

					if(result_score 
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_pawn failure(8)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_score_moves_pawn exception(0): " 
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
		ptce_test_board_score_moves_queen(void)
		{
			size_t result_score;
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;
			std::set<std::pair<ptce_mv_ent_t, size_t>> move_set, result_move_set;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(0, 0));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(1, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(2, 0));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					result_score = ptce_board::score_move_set(board, PIECE_QUEEN, 
							board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(0, 0));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(1, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(2, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(4, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(5, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(6, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(7, 6));
					result_score = ptce_board::score_move_set(board, PIECE_QUEEN, 
							board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 3), PIECE_PAWN, PIECE_BLACK);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(0, 0));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(1, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(2, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CAPTURE),
							ptce_pos_t(1, 0), ptce_pos_t(4, 3));
					result_score = ptce_board::score_move_set(board, PIECE_QUEEN, 
							board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CAPTURE))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(2, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(4, 3), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(0, 0));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(0, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(1, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(2, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(2, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(1, 0), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(1, 0), ptce_pos_t(4, 3));
					result_score = ptce_board::score_move_set(board, PIECE_QUEEN, 
							board.generate_move_set(ptce_pos_t(1, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_QUEEN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(0, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(0, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(0, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 7));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(7, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(7, 7));
					result_score = ptce_board::score_move_set(board, PIECE_QUEEN, 
							board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(0, 3), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(0, 6), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(3, 7), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(6, 0), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(7, 3), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(7, 7), PIECE_PAWN, PIECE_BLACK);
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(0, 0));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(0, 3));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(0, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(3, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 6));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(3, 7));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(6, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 6));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(7, 3));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CAPTURE),
							ptce_pos_t(3, 3), ptce_pos_t(7, 7));
					result_score = ptce_board::score_move_set(board, PIECE_QUEEN, 
							board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CAPTURE))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 3), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 6), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 7), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(6, 0), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(7, 3), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(7, 7), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(0, 0));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(0, 3));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(0, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(3, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 6));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(3, 7));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(6, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 6));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(7, 3));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(3, 3), ptce_pos_t(7, 7));
					result_score = ptce_board::score_move_set(board, PIECE_QUEEN, 
							board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(5)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 7), PIECE_KING, PIECE_BLACK);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(0, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(0, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(0, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 6));
					append_test_score_move_set(move_set, MOVE_CHECK, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CHECK),
							ptce_pos_t(3, 3), ptce_pos_t(3, 7));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(7, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(7, 7));
					result_score = ptce_board::score_move_set(board, PIECE_QUEEN, 
							board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CHECK))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(6)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 3), PIECE_QUEEN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(7, 7), PIECE_KING, PIECE_BLACK);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(0, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(0, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(0, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(1, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(2, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(3, 7));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(4, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(5, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(6, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_NORMAL),
							ptce_pos_t(3, 3), ptce_pos_t(7, 3));
					append_test_score_move_set(move_set, MOVE_CHECK, MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CHECK),
							ptce_pos_t(3, 3), ptce_pos_t(7, 7));
					result_score = ptce_board::score_move_set(board, PIECE_QUEEN, 
							board.generate_move_set(ptce_pos_t(3, 3), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_QUEEN, MOVE_CHECK))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_queen failure(7)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_score_moves_queen exception(0): " 
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
		ptce_test_board_score_moves_rook(void)
		{
			size_t result_score;
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;
			std::set<std::pair<ptce_mv_ent_t, size_t>> move_set, result_move_set;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board(true);

				try {
					board.generate_piece(ptce_pos_t(0, 0), PIECE_ROOK, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(0, 0), ptce_pos_t(0, 1));
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(0, 0), ptce_pos_t(1, 0));
					result_score = ptce_board::score_move_set(board, PIECE_ROOK, 
							board.generate_move_set(ptce_pos_t(0, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_rook failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_ROOK, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_BLACK);
					board.generate_piece(ptce_pos_t(1, 0), PIECE_PAWN, PIECE_BLACK);
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_CAPTURE),
							ptce_pos_t(0, 0), ptce_pos_t(0, 1));
					append_test_score_move_set(move_set, MOVE_CAPTURE, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_CAPTURE),
							ptce_pos_t(0, 0), ptce_pos_t(1, 0));
					result_score = ptce_board::score_move_set(board, PIECE_ROOK, 
							board.generate_move_set(ptce_pos_t(0, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_CAPTURE))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_rook failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_ROOK, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(0, 1), PIECE_PAWN, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_PROTECT, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_PROTECT) 
							* MOVE_HEURISTIC_PROTECT_MULTIPLE_VALUE(PIECE_PAWN),
							ptce_pos_t(0, 0), ptce_pos_t(0, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(1, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(2, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(3, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(4, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(5, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(6, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(7, 0));
					result_score = ptce_board::score_move_set(board, PIECE_ROOK, 
							board.generate_move_set(ptce_pos_t(0, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_rook failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(0, 0), PIECE_ROOK, PIECE_WHITE);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(0, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(0, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(0, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(0, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(0, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(0, 6));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(0, 7));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(1, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(2, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(3, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(4, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(5, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(6, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(0, 0), ptce_pos_t(7, 0));
					result_score = ptce_board::score_move_set(board, PIECE_ROOK, 
							board.generate_move_set(ptce_pos_t(0, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_rook failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.clear();
					move_set.clear();
					result_move_set.clear();
					board.generate_piece(ptce_pos_t(3, 0), PIECE_ROOK, PIECE_WHITE);
					board.generate_piece(ptce_pos_t(3, 7), PIECE_KING, PIECE_BLACK);
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(0, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(1, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(2, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(3, 1));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(3, 2));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(3, 3));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(3, 4));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(3, 5));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(3, 6));
					append_test_score_move_set(move_set, MOVE_CHECK, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_CHECK),
							ptce_pos_t(3, 0), ptce_pos_t(3, 7));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(4, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(5, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(6, 0));
					append_test_score_move_set(move_set, MOVE_NORMAL, MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_NORMAL),
							ptce_pos_t(3, 0), ptce_pos_t(7, 0));
					result_score = ptce_board::score_move_set(board, PIECE_ROOK, 
							board.generate_move_set(ptce_pos_t(3, 0), PIECE_BLACK), result_move_set);

					if((result_score != MOVE_HEURISTIC_VALUE(PIECE_ROOK, MOVE_CHECK))
							|| !compare_test_score_move_sets(move_set, result_move_set)) {
						std::cerr << "----!ptce_test_board_generate_moves_rook failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_score_moves_rook exception(0): " 
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
		ptce_test_board_serialize(void)
		{
			ptce_piece_t type;
			ptce_ptr inst = NULL;
			ptce_piece_col_t color;
			std::string serial, token;
			size_t x = 0, y, ch_iter = 0, cmd_iter = 0;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_board board;

				try {

					serial = board.serialize(BOARD_CONTINUE);
					if(serial.empty()) {
						std::cerr << "----!ptce_test_board_serialize failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					for(; ch_iter < serial.size(); ++ch_iter) {

						if(serial.at(ch_iter) == COMMAND_TOKEN_DELIM) {
							break;
						}

						token += serial.at(ch_iter);
					}

					std::transform(token.begin(), token.end(), token.begin(), ::tolower);

					for(; cmd_iter <= BOARD_MOVE_MAX; ++cmd_iter) {

						if(token == BOARD_MOVE_STRING(cmd_iter)) {
							break;
						}
					}

					if(cmd_iter > BOARD_MOVE_MAX) {
						std::cerr << "----!ptce_test_board_serialize failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if((ch_iter++ == serial.size()) || (ch_iter == serial.size())) {
						std::cerr << "----!ptce_test_board_serialize failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					for(; x < BOARD_WID; ++x) {

						for(y = 0; y < BOARD_WID; ++y) {

							if((ch_iter + PIECE_TOKEN_LEN_MIN) >= serial.size()) {
								std::cerr << "----!ptce_test_board_serialize failure(3)" << std::endl;
								result = PTCE_TEST_FAILURE;
								goto exit;
							}

							token = std::string(1, serial.at(ch_iter++));
							if(std::atoi(token.c_str()) != x) {
								std::cerr << "----!ptce_test_board_serialize failure(4)" << std::endl;
								result = PTCE_TEST_FAILURE;
								goto exit;
							}

							token = std::string(1, serial.at(ch_iter++));
							if(std::atoi(token.c_str()) != y) {
								std::cerr << "----!ptce_test_board_serialize failure(5)" << std::endl;
								result = PTCE_TEST_FAILURE;
								goto exit;
							}

							token = std::string(1, serial.at(ch_iter++));
							type = (ptce_piece_t) std::atoi(token.c_str());

							if(type > PIECE_TYPE_MAX) {
								std::cerr << "----!ptce_test_board_serialize failure(6)" << std::endl;
								result = PTCE_TEST_FAILURE;
								goto exit;
							}

							token = std::string(1, serial.at(ch_iter++));
							color = (ptce_piece_col_t) std::atoi(token.c_str());

							if(color > PIECE_COLOR_MAX) {
								std::cerr << "----!ptce_test_board_serialize failure(7)" << std::endl;
								result = PTCE_TEST_FAILURE;
								goto exit;
							}

							if((type == PIECE_KING)
									|| (type == PIECE_ROOK)
									|| (type == PIECE_PAWN)) {

								if((ch_iter + PIECE_TOKEN_FLAG_LEN) >= serial.size()) {
									std::cerr << "----!ptce_test_board_serialize failure(8)" << std::endl;
									result = PTCE_TEST_FAILURE;
									goto exit;
								}

								++ch_iter;
							}

							if(serial.at(ch_iter) != PIECE_TOKEN_SEP) {
								std::cerr << "----!ptce_test_board_serialize failure(9)" << std::endl;
								result = PTCE_TEST_FAILURE;
								goto exit;
							}

							++ch_iter;
						}
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_serialize exception(0): " 
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
				ptce_board board;

				try {

					if(board.size() != BOARD_LEN) {
						std::cerr << "----!ptce_test_board_size failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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
				ptce_board board;

				try {

					if(board.state() != BOARD_INACTIVE) {
						std::cerr << "----!ptce_test_board_state failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					board.move(ptce_pos_t(3, 1), ptce_pos_t(3, 3));

					if(board.state() != BOARD_ACTIVE) {
						std::cerr << "----!ptce_test_board_state failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
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

		ptce_test_t 
		ptce_test_board_unserialize(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_piece piece;
				ptce_board board0, board1;

				try {
					board0.move(ptce_pos_t(3, 1), ptce_pos_t(3, 3));
					board1.unserialize(board0.serialize());

					if(!board1.contains(ptce_pos_t(3, 3))) {
						std::cerr << "----!ptce_test_board_unserialize failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					piece = board1.piece(ptce_pos_t(3, 3));
					if((piece.type() != PIECE_PAWN) || (piece.color() != PIECE_WHITE)) {
						std::cerr << "----!ptce_test_board_unserialize failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_board_unserialize exception(0): " 
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
