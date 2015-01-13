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

#include "../include/ptce.h"
#include "../include/ptce_type.h"

namespace PTCE_NS {

	ptce_ptr ptce::m_instance = NULL;

	void 
	ptce_destroy(void)
	{
		TRACE_ENTRY();
		
		if(ptce::m_instance) {
			delete ptce::m_instance;
			ptce::m_instance = NULL;
		}

		TRACE_EXIT("Return Value: 0x%x", 0);
	}
	
	_ptce::_ptce(void) :
		m_initialized(false),
		m_factory_node(ptce_node_factory::acquire()),
		m_factory_uid(ptce_uid_factory::acquire())
	{
		TRACE_ENTRY();
		
		std::atexit(ptce_destroy);
		
		TRACE_EXIT("Return Value: 0x%x", 0);
	}
	
	_ptce::~_ptce(void)
	{
		TRACE_ENTRY();
		
		if(m_initialized) {
			destroy();
		}
		
		TRACE_EXIT("Return Value: 0x%x", 0);
	}

	ptce_ptr 
	_ptce::acquire(void)
	{
		ptce_ptr result = NULL;
	
		TRACE_ENTRY();
		
		if(!m_instance) {
		
			m_instance = new ptce();
			if(!m_instance) {
				THROW_PTCE_EXCEPTION(PTCE_EXCEPTION_ACQUIRE_FAILED);
			}
		}
		
		result = m_instance;
		
		TRACE_EXIT("Return Value: 0x%p", result);
		return result;
	}
	
	ptce_node_factory_ptr 
	_ptce::acquire_node_factory(void)
	{
		TRACE_ENTRY();
		SERIALIZE_CALL_RECUR(m_lock);

		if(!m_initialized) {
			THROW_PTCE_EXCEPTION(PTCE_EXCEPTION_UNINITIALIZED);
		}

		TRACE_EXIT("Return Value: 0x%p", m_factory_node);
		return m_factory_node;
	}

	ptce_uid_factory_ptr 
	_ptce::acquire_uid_factory(void)
	{
		TRACE_ENTRY();
		SERIALIZE_CALL_RECUR(m_lock);

		if(!m_initialized) {
			THROW_PTCE_EXCEPTION(PTCE_EXCEPTION_UNINITIALIZED);
		}

		TRACE_EXIT("Return Value: 0x%p", m_factory_uid);
		return m_factory_uid;
	}

	void 
	_ptce::destroy(void)
	{
		TRACE_ENTRY();
		SERIALIZE_CALL_RECUR(m_lock);
		
		if(!m_initialized) {
			THROW_PTCE_EXCEPTION(PTCE_EXCEPTION_UNINITIALIZED);
		}
		
		m_factory_node->destroy();
		m_factory_uid->destroy();

		// TODO: destroy factories, etc.
		
		m_initialized = false;
		
		TRACE_EXIT("Return Value: 0x%x", 0);
	}
	
	void 
	_ptce::initialize(void)
	{
		TRACE_ENTRY();
		SERIALIZE_CALL_RECUR(m_lock);
		
		if(m_initialized) {
			THROW_PTCE_EXCEPTION(PTCE_EXCEPTION_INITIALIZED);
		}

		m_factory_uid->initialize();
		m_factory_node->initialize();

		// TODO: initialize factories, etc.
		
		m_initialized = true;
		
		TRACE_EXIT("Return Value: 0x%x", 0);
	}

	bool 
	_ptce::is_allocated(void)
	{
		bool result;
	
		TRACE_ENTRY();
		
		result = (m_instance != NULL);
		
		TRACE_EXIT("Return Value: 0x%x", result);
		return result;
	}

	bool 
	_ptce::is_initialized(void)
	{
		TRACE_ENTRY();
		SERIALIZE_CALL_RECUR(m_lock);
		TRACE_EXIT("Return Value: 0x%x", m_initialized);
		return m_initialized;
	}

	std::string 
	_ptce::to_string(
		__in_opt bool verbose
		)
	{
		std::stringstream result;
	
		TRACE_ENTRY();
		SERIALIZE_CALL_RECUR(m_lock);
		
		if(verbose) {
			result << PTCE_TRACE_HEADER << " Instance=0x" << VALUE_AS_HEX(uintptr_t, m_instance)
					<< ", Initialized=" << m_initialized;
		}

		result << std::endl << m_factory_uid->to_string(verbose)
			<< std::endl << m_factory_node->to_string(verbose);

		// TODO: retreive factory strings, etc. (pass verbose)
		
		TRACE_EXIT("Return Value: 0x%x", 0);
		return result.str();
	}

	std::string 
	_ptce::version(
		__in_opt bool verbose
		)
	{
		TRACE_ENTRY();
		TRACE_EXIT("Return Value: 0x%x", 0);
		return verbose ? VERSION_STR_VERB : VERSION_STR;
	}
}
