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
#include "../include/ptce_test_uid.h"

namespace PTCE_NS {

	namespace PTCE_TEST_NS {

		#define TEST_UID 0x234355faab6673

		ptce_test_t 
		ptce_test_uid_assignment(void)
		{
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				ptce_uid uid0, uid1(TEST_UID);

				try {
					uid0 = uid1;

					if(uid0.id() != uid1.id()) {
						std::cerr << "----!ptce_test_uid_assignment failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_assignment exception(0): " << exc.what() << std::endl;
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
		ptce_test_uid_base_assignment(void)
		{
			ptce_ptr inst = NULL;
			ptce_uid_factory_ptr fact_inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();				

				ptce_uid_base base0;

				try {

					{
						ptce_uid_base base1;

						fact_inst = inst->acquire_uid_factory();
						if(fact_inst->size() != 2) {
							std::cerr << "----!ptce_test_uid_base_assignment failure(0)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}

						base0 = base1;

						if(base0.id() != base1.id()) {
							std::cerr << "----!ptce_test_uid_base_assignment failure(1)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}

						if((fact_inst->size() != 1)
								|| (fact_inst->reference_count(base0.id()) != 2)) {
							std::cerr << "----!ptce_test_uid_base_assignment failure(2)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					}

					if((fact_inst->size() != 1)
							|| (fact_inst->reference_count(base0.id()) != 1)) {
						std::cerr << "----!ptce_test_uid_base_assignment failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_base_assignment exception(0): " << exc.what() << std::endl;
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
		ptce_test_uid_base_constructor(void)
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
					ptce_uid_base base0;

					if((fact_inst->size() != 1)
							|| (fact_inst->reference_count(base0.id()) != 1)) {
						std::cerr << "----!ptce_test_uid_base_constructor failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					ptce_uid_base base1(base0);

					if((fact_inst->size() != 1)
							|| (fact_inst->reference_count(base0.id()) != 2)) {
						std::cerr << "----!ptce_test_uid_base_constructor failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					ptce_uid_base base2(base0.id());

					if((fact_inst->size() != 1)
							|| (fact_inst->reference_count(base0.id()) != 3)) {
						std::cerr << "----!ptce_test_uid_base_constructor failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_base_constructor exception(0): " << exc.what() << std::endl;
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
		ptce_test_uid_base_id(void)
		{
			ptce_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce::acquire();
				inst->initialize();
				ptce_uid_base base(TEST_UID);

				try {

					if(base.id() != TEST_UID) {
						std::cerr << "----!ptce_test_uid_base_id failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_base_id exception(0): " << exc.what() << std::endl;
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
		ptce_test_uid_constructor(void)
		{
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				try {
					// default constructor
					{
						ptce_uid uid;

						if(uid.id()) {
							std::cerr << "----!ptce_test_uid_constructor failure(0)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					}

					// constructor /w input
					{
						ptce_uid uid(TEST_UID);

						if(uid.id() != TEST_UID) {
							std::cerr << "----!ptce_test_uid_constructor failure(1)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					}

					// constructor /w assignment
					{
						ptce_uid uid1(TEST_UID), uid0(uid1);

						if(uid0.id() != uid1.id()) {
							std::cerr << "----!ptce_test_uid_constructor failure(2)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_constructor exception(0): " << exc.what() << std::endl;
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
		ptce_test_uid_equals(void)
		{
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				ptce_uid uid0, uid1;

				try {

					if(!(uid0 == uid1)) {
						std::cerr << "----!ptce_test_uid_equals failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					uid1.id() = TEST_UID;

					if(uid0 == uid1) {
						std::cerr << "----!ptce_test_uid_equals failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					uid0.id() = TEST_UID;

					if(!(uid0 == uid1)) {
						std::cerr << "----!ptce_test_uid_equals failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_equals exception(0): " << exc.what() << std::endl;
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
		ptce_test_uid_factory_acquire(void)
		{
			ptce_uid_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				try {

					inst = ptce_uid_factory::acquire();
					if(!inst) {
						std::cerr << "----!ptce_test_uid_factory_acquire failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(!ptce_uid_factory::is_allocated()) {
						std::cerr << "----!ptce_test_uid_factory_acquire failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_factory_acquire exception(0): " << exc.what() << std::endl;
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
		ptce_test_uid_factory_add(void)
		{
			ptce_uid uid(TEST_UID);
			ptce_uid_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_uid_factory::acquire();
				inst->initialize();

				try {
					inst->add(uid);
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_factory_add exception(0): " << exc.what() << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				if(!inst->contains(uid)
						|| (inst->reference_count(uid) != 1)) {
					std::cerr << "----!ptce_test_uid_factory_add failure(0)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->increment_reference(uid);

				if(!inst->contains(uid)
						|| (inst->reference_count(uid) != 2)) {
					std::cerr << "----!ptce_test_uid_factory_add failure(1)" << std::endl;
					result = PTCE_TEST_FAILURE;
					goto exit;
				}

				inst->decrement_reference(uid);
				inst->decrement_reference(uid);

				if(inst->contains(uid)) {
					std::cerr << "----!ptce_test_uid_factory_add failure(2)" << std::endl;
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
		ptce_test_uid_factory_contains(void)
		{
			ptce_uid uid;
			ptce_uid_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_uid_factory::acquire();
				inst->initialize();
				uid = inst->generate(true);

				try {

					if(!inst->contains(uid)) {
						std::cerr << "----!ptce_test_uid_factory_contains failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					inst->decrement_reference(uid);

					if(inst->contains(uid)) {
						std::cerr << "----!ptce_test_uid_factory_contains failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_factory_contains exception(0): " << exc.what() << std::endl;
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
		ptce_test_uid_factory_decrement_reference(void)
		{
			ptce_uid uid;
			ptce_uid_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_uid_factory::acquire();
				inst->initialize();
				uid = inst->generate(true);
				inst->increment_reference(uid);

				try {
					inst->decrement_reference(uid);

					if(inst->reference_count(uid) != 1) {
						std::cerr << "----!ptce_test_uid_factory_decrement_reference failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					inst->decrement_reference(uid);

					if(inst->contains(uid)) {
						std::cerr << "----!ptce_test_uid_factory_decrement_reference failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_factory_decrement_reference exception(0): " 
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
		ptce_test_uid_factory_destroy(void)
		{
			ptce_uid_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_uid_factory::acquire();

				try {

					if(inst->is_initialized()) {
						inst->destroy();
					}

					try {
						inst->destroy();
						std::cerr << "----!ptce_test_uid_factory_destroy failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					} catch(...) { }

					inst->initialize();
					inst->generate(true);
					inst->destroy();

					if(inst->is_initialized()) {
						inst->destroy();
						std::cerr << "----!ptce_test_uid_factory_destroy failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_factory_destroy exception(0): " << exc.what() << std::endl;
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
		ptce_test_uid_factory_generate(void)
		{
			ptce_uid uid;
			ptce_uid_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_uid_factory::acquire();
				inst->initialize();

				try {
					uid = inst->generate(true);

					if(!inst->contains(uid) || (inst->reference_count(uid) != 1)) {
						std::cerr << "----!ptce_test_uid_factory_generate failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_factory_generate exception(0): " << exc.what() << std::endl;
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
		ptce_test_uid_factory_increment_reference(void)
		{
			ptce_uid uid;
			ptce_uid_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_uid_factory::acquire();
				inst->initialize();
				uid = inst->generate(true);

				try {
					inst->increment_reference(uid);

					if(inst->reference_count(uid) != 2) {
						std::cerr << "----!ptce_test_uid_factory_increment_reference failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					inst->decrement_reference(uid);
					inst->increment_reference(uid);

					if(!inst->contains(uid) 
							|| (inst->reference_count(uid) != 2)) {
						std::cerr << "----!ptce_test_uid_factory_increment_reference failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_factory_increment_reference exception(0): " 
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
		ptce_test_uid_factory_initialize(void)
		{
			ptce_uid_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_uid_factory::acquire();

				try {
					inst->initialize();

					if(!inst->is_initialized() || inst->size()) {
						std::cerr << "----!ptce_test_uid_factory_initializ failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_factory_initialize exception(0): " << exc.what() << std::endl;
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
		ptce_test_uid_factory_is_allocated(void)
		{
			ptce_uid_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				try {

					inst = ptce_uid_factory::acquire();
					if(!inst) {
						result = PTCE_TEST_INCONCLUSIVE;
						goto exit;
					}

					try {

						if(!ptce_uid_factory::is_allocated()) {
							std::cerr << "----!ptce_test_uid_factory_is_allocated failure(0)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					} catch(std::runtime_error &exc) {
						std::cerr << "----!ptce_test_uid_factory_is_allocated exception(0): " 
								<< exc.what() << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					ptce::release_uid_factory();

					try {

						if(ptce_uid_factory::is_allocated()) {
							std::cerr << "----!ptce_test_uid_factory_is_allocated failure(1)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					} catch(std::runtime_error &exc) {
						std::cerr << "----!ptce_test_uid_factory_is_allocated exception(1): " 
								<< exc.what() << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_factory_is_allocated exception(0): " 
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
		ptce_test_uid_factory_is_initialized(void)
		{
			ptce_uid_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {

				inst = ptce_uid_factory::acquire();
				if(!inst) {
					result = PTCE_TEST_INCONCLUSIVE;
					goto exit;
				}

				try {

					try {

						if(inst->is_initialized()) {
							std::cerr << "----!ptce_test_uid_factory_is_initialized failure(0)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					} catch(std::runtime_error &exc) {
						std::cerr << "----!ptce_test_uid_factory_is_initialized exception(0): " << exc.what() << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					inst->initialize();

					try {

						if(!inst->is_initialized()) {
							std::cerr << "----!ptce_test_uid_factory_is_initialized failure(1)" << std::endl;
							result = PTCE_TEST_FAILURE;
							goto exit;
						}
					} catch(std::runtime_error &exc) {
						std::cerr << "----!ptce_test_uid_factory_is_initialized exception(1): " << exc.what() << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_factory_is_initialized exception(0): " 
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
		ptce_test_uid_factory_reference_count(void)
		{
			ptce_uid uid;
			ptce_uid_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_uid_factory::acquire();
				inst->initialize();
				uid = inst->generate(true);

				try {

					if(inst->reference_count(uid) != 1) {
						std::cerr << "----!ptce_test_uid_factory_reference_count failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(inst->increment_reference(uid) != 2) {
						std::cerr << "----!ptce_test_uid_factory_reference_count failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					if(inst->decrement_reference(uid) != 1) {
						std::cerr << "----!ptce_test_uid_factory_reference_count failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_factory_reference_count exception(0): " 
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
		ptce_test_uid_factory_size(void)
		{
			ptce_uid uid0, uid1;
			ptce_uid_factory_ptr inst = NULL;
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				inst = ptce_uid_factory::acquire();
				inst->initialize();

				try {

					if(inst->size()) {
						std::cerr << "----!ptce_test_uid_factory_size failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					uid0 = inst->generate(true);

					if(inst->size() != 1) {
						std::cerr << "----!ptce_test_uid_factory_size failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					uid1 = inst->generate(true);

					if(inst->size() != 2) {
						std::cerr << "----!ptce_test_uid_factory_size failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					inst->decrement_reference(uid0);
					inst->decrement_reference(uid1);

					if(inst->size()) {
						std::cerr << "----!ptce_test_uid_factory_size failure(3)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_factory_size exception(0): " << exc.what() << std::endl;
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
		ptce_test_uid_id(void)
		{
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				ptce_uid uid;

				try {
					
					if(uid.id()) {
						std::cerr << "----!ptce_test_uid_id failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					uid.id() = TEST_UID;

					if(uid.id() != TEST_UID) {
						std::cerr << "----!ptce_test_uid_id failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_id exception(0): " << exc.what() << std::endl;
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
		ptce_test_uid_not_equals(void)
		{
			ptce_test_t result = PTCE_TEST_INCONCLUSIVE;

			TRACE_ENTRY();

			try {
				ptce_uid uid0, uid1;

				try {

					if(uid0 != uid1) {
						std::cerr << "----!ptce_test_uid_not_equals failure(0)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					uid1.id() = TEST_UID;

					if(!(uid0 != uid1)) {
						std::cerr << "----!ptce_test_uid_not_equals failure(1)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}

					uid0.id() = TEST_UID;

					if(uid0 != uid1) {
						std::cerr << "----!ptce_test_uid_not_equals failure(2)" << std::endl;
						result = PTCE_TEST_FAILURE;
						goto exit;
					}
				} catch(std::runtime_error &exc) {
					std::cerr << "----!ptce_test_uid_not_not_equals exception(0): " << exc.what() << std::endl;
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
