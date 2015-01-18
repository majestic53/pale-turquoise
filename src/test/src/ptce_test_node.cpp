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
#include "../include/ptce_test_node.h"

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		#define TEST_UID 0x234355faab6673

		ptce_test_t 
		ptce_test_node_assignment(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_node node0, node1;
				node1.children().push_back(ptce_uid(TEST_UID));
				node1.entry() = ptce_uid(TEST_UID);
				node1.parent() = ptce_uid(TEST_UID);

				try {

					node0 = node1;
					if((node0.id() != node1.id())
							|| (node0.children().size() != node1.children().size())
							|| (node0.children().front() != node1.children().front())
							|| (node0.entry() != node1.entry())
							|| (node0.parent() != node1.parent())) {
						std::cerr << "----!ptce_test_node_assignment failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_assignment exception(0): " << exc.what() << std::endl;
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
		ptce_test_node_constructor(void)
		{
			ptce_ptr inst = NULL;
			ptce_uid_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_uid_factory();

				try {

					ptce_node node0;

					if((node0.entry() != UID_NULL)
							|| (node0.parent() != UID_NULL)
							|| node0.size()) {
						std::cerr << "----!ptce_test_node_constructor failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(!fact_inst->contains(node0.id())) {
						std::cerr << "----!ptce_test_node_constructor failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					ptce_node node1(ptce_uid(TEST_UID));

					if((node1.entry() != UID_NULL)
							|| (node1.parent() != UID_NULL)
							|| node1.size()) {
						std::cerr << "----!ptce_test_node_constructor failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(!fact_inst->contains(node1.id())) {
						std::cerr << "----!ptce_test_node_constructor failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					ptce_node node2(node0);

					if((node2.entry() != UID_NULL)
							|| (node2.parent() != UID_NULL)
							|| node2.size()) {
						std::cerr << "----!ptce_test_node_constructor failure(4)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(!fact_inst->contains(node2.id())) {
						std::cerr << "----!ptce_test_node_constructor failure(5)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_constructor exception(0): " << exc.what() << std::endl;
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
		ptce_test_node_children(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_node node;

				try {

					if(node.children().size()) {
						std::cerr << "----!ptce_test_node_children failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					node.children().push_back(ptce_uid(TEST_UID));

					if((node.children().size() != 1)
							|| (node.children().front() != ptce_uid(TEST_UID))) {
						std::cerr << "----!ptce_test_node_children failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					node.children().clear();

					if(node.children().size()) {
						std::cerr << "----!ptce_test_node_children failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_children exception(0): " << exc.what() << std::endl;
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
		ptce_test_node_entry(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_node node;

				try {

					if(node.entry() != UID_NULL) {
						std::cerr << "----!ptce_test_node_entry failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				
					node.entry() = ptce_uid(TEST_UID);

					if(node.entry() != ptce_uid(TEST_UID)) {
						std::cerr << "----!ptce_test_node_entry failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_entry exception(0): " << exc.what() << std::endl;
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
		ptce_test_node_equals(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_node node0(ptce_uid(0)), node1(ptce_uid(0));

				try {

					if(!(node0 == node1)) {
						std::cerr << "----!ptce_test_node_equals failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					node0 = ptce_node(ptce_uid(TEST_UID));

					if(node0 == node1) {
						std::cerr << "----!ptce_test_node_equals failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_equals exception(0): " << exc.what() << std::endl;
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
		ptce_test_node_factory_acquire(void)
		{
			ptce_ptr inst = NULL;
			ptce_node_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();

				try {

					fact_inst = inst->acquire_node_factory();
					if(!fact_inst) {
						std::cerr << "----!ptce_test_node_factory_acquire failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(!fact_inst->is_allocated()) {
						std::cerr << "----!ptce_test_node_factory_acquire failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_factory_acquire exception(0): " << exc.what() << std::endl;
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
		ptce_test_node_factory_contains(void)
		{
			ptce_ptr inst = NULL;
			ptce_node_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_node_factory();
				ptce_node node = fact_inst->generate(ptce_uid(TEST_UID));

				try {

					if(!fact_inst->contains(node)) {
						std::cerr << "----!ptce_test_node_factory_contains failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->decrement_reference(node);

					if(fact_inst->contains(node)) {
						std::cerr << "----!ptce_test_node_factory_contains failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_factory_contains exception(0): " << exc.what() << std::endl;
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
		ptce_test_node_factory_decrement_reference(void)
		{
			ptce_ptr inst = NULL;
			ptce_node_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_node_factory();
				ptce_node node = fact_inst->generate(ptce_uid(TEST_UID));
				fact_inst->increment_reference(node);

				try {

					if((fact_inst->decrement_reference(node) != 1) 
							|| (fact_inst->reference_count(node) != 1)) {
						std::cerr << "----!ptce_test_node_factory_decrement_reference failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(fact_inst->decrement_reference(node) 
							|| fact_inst->contains(node)) {
						std::cerr << "----!ptce_test_node_factory_decrement_reference failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_factory_decrement_reference exception(0): " 
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
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}

		ptce_test_t 
		ptce_test_node_factory_destroy(void)
		{
			ptce_ptr inst = NULL;
			ptce_node_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_node_factory();

				try {

					if(fact_inst->is_initialized()) {
						fact_inst->destroy();
					}

					try {
						fact_inst->destroy();
						std::cerr << "----!ptce_test_node_factory_destroy failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					if(fact_inst->is_initialized()) {
						std::cerr << "----!ptce_test_node_factory_destroy failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_factory_destroy exception(0): " << exc.what() << std::endl;
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
		ptce_test_node_factory_generate(void)
		{
			ptce_ptr inst = NULL;
			std::vector<ptce_uid> children;
			ptce_node_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_node_factory();

				try {
					children.push_back(ptce_uid(TEST_UID));
					ptce_node node = fact_inst->generate(ptce_uid(TEST_UID), ptce_uid(TEST_UID), children);

					if(!fact_inst->contains(node)
							|| (fact_inst->reference_count(node) != 1)) {
						std::cerr << "----!ptce_test_node_factory_generate failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if((node.entry() != ptce_uid(TEST_UID)) 
							|| (node.parent() != ptce_uid(TEST_UID))
							|| (node.children().size() != 1)
							|| (node.children().front() != ptce_uid(TEST_UID))) {
						std::cerr << "----!ptce_test_node_factory_generate failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}		
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_factory_generate exception(0): " << exc.what() << std::endl;
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
		ptce_test_node_factory_increment_reference(void)
		{
			ptce_ptr inst = NULL;
			ptce_node_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_node_factory();
				ptce_node node = fact_inst->generate(ptce_uid(TEST_UID));

				try {

					if((fact_inst->increment_reference(node) != 2) 
							|| (fact_inst->reference_count(node) != 2)) {
						std::cerr << "----!ptce_test_node_factory_increment_reference failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_factory_decrement_reference exception(0): " 
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
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}

		ptce_test_t 
		ptce_test_node_factory_initialize(void)
		{
			ptce_ptr inst = NULL;
			ptce_node_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_node_factory();

				if(fact_inst->is_initialized()) {
					fact_inst->destroy();
				}

				try {
					fact_inst->initialize();

					if(!fact_inst->is_initialized()
							|| fact_inst->size()) {
						std::cerr << "----!ptce_test_node_factory_initialize failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_factory_initialize exception(0): " << exc.what() << std::endl;
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
		ptce_test_node_factory_is_allocated(void)
		{
			ptce_node_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				try {

					inst = ptce_node_factory::acquire();
					if(!inst) {
						result = PTCE_TEST_INCONCLUSIVE;
						goto exit;
					}

					try {

						if(!ptce_node_factory::is_allocated()) {
							std::cerr << "----!ptce_test_node_factory_is_allocated failure(0)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					} catch(std::runtime_error &exc) {
						std::cerr << "----!ptce_test_node_factory_is_allocated exception(0): " 
								<< exc.what() << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					ptce::release_node_factory();

					try {

						if(ptce_node_factory::is_allocated()) {
							std::cerr << "----!ptce_test_node_factory_is_allocated failure(1)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					} catch(std::runtime_error &exc) {
						std::cerr << "----!ptce_test_node_factory_is_allocated exception(1): " 
								<< exc.what() << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_factory_is_allocated exception(0): " 
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
		ptce_test_node_factory_is_initialized(void)
		{
			ptce_ptr inst = NULL;
			ptce_node_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_node_factory();
				fact_inst->initialize();

				try {

					if(!fact_inst->is_initialized()) {
						std::cerr << "----!ptce_test_node_factory_is_initialized failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->destroy();

					if(fact_inst->is_initialized()) {
						std::cerr << "----!ptce_test_node_factory_is_initialized failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_factory_is_initialized exception(0): " 
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
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}

		ptce_test_t 
		ptce_test_node_factory_reference_count(void)
		{
			ptce_ptr inst = NULL;
			ptce_node_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_node_factory();
				ptce_node node = fact_inst->generate(ptce_uid(TEST_UID));

				try {

					if(fact_inst->reference_count(node) != 1) {
						std::cerr << "----!ptce_test_node_factory_reference_count failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->increment_reference(node);

					if(fact_inst->reference_count(node) != 2) {
						std::cerr << "----!ptce_test_node_factory_reference_count failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->decrement_reference(node);

					if(fact_inst->reference_count(node) != 1) {
						std::cerr << "----!ptce_test_node_factory_reference_count failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_factory_reference_count exception(0): " 
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
			TRACE_EXIT("Return Value: %s (0x%x)", PTCE_TEST_STRING(result), 
					result);
			return result;
		}

		ptce_test_t 
		ptce_test_node_factory_size(void)
		{
			ptce_ptr inst = NULL;
			ptce_node_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				fact_inst = inst->acquire_node_factory();

				try {

					if(fact_inst->size()) {
						std::cerr << "----!ptce_test_node_factory_size failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					ptce_node node = fact_inst->generate(ptce_uid(TEST_UID));

					if(fact_inst->size() != 1) {
						std::cerr << "----!ptce_test_node_factory_size failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					fact_inst->decrement_reference(node);

					if(fact_inst->size()) {
						std::cerr << "----!ptce_test_node_factory_size failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_factory_size exception(0): " << exc.what() << std::endl;
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
		ptce_test_node_not_equals(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_node node0(ptce_uid(0)), node1(ptce_uid(0));

				try {

					if(node0 != node1) {
						std::cerr << "----!ptce_test_node_not_equals failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					node0 = ptce_node(ptce_uid(TEST_UID));

					if(!(node0 != node1)) {
						std::cerr << "----!ptce_test_node_not_equals failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_not_equal exception(0): " << exc.what() << std::endl;
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
		ptce_test_node_parent(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_node node;

				try {

					if(node.parent() != UID_NULL) {
						std::cerr << "----!ptce_test_node_parent failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				
					node.parent() = ptce_uid(TEST_UID);

					if(node.parent() != ptce_uid(TEST_UID)) {
						std::cerr << "----!ptce_test_node_parent failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_parent exception(0): " << exc.what() << std::endl;
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
		ptce_test_node_size(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_node node;

				try {

					if(node.size()) {
						std::cerr << "----!ptce_test_node_size failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					node.children().push_back(ptce_uid(TEST_UID));

					if(node.size() != 1) {
						std::cerr << "----!ptce_test_node_size failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_node_size exception(0): " << exc.what() << std::endl;
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
	}
}
