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
#include "../include/ptce_node_type.h"

namespace PTCE_NS {

	namespace PTCE_COMP_NS {

		_ptce_node::_ptce_node(void) :
			m_entry(UID_NULL),
			m_parent(UID_NULL)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_node::_ptce_node(
			__in const ptce_uid &uid,
			__in_opt const ptce_uid &entry,
			__in_opt const ptce_uid &parent,
			__in_opt const std::vector<ptce_uid> &children
			) :
				ptce_uid_base(uid),
				m_children(children),
				m_entry(entry),
				m_parent(parent)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_node::_ptce_node(
			__in const _ptce_node &other
			) :
				ptce_uid_base(other),
				m_children(other.m_children),
				m_entry(other.m_entry),
				m_parent(other.m_parent)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_node::~_ptce_node(void)
		{
			TRACE_ENTRY();

			decrement_reference();

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_node &
		_ptce_node::operator=(
			__in const _ptce_node &other
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				ptce_uid_base::operator=(other);
				m_children = other.m_children;
				m_entry = other.m_entry;
				m_parent = other.m_parent;
			}

			TRACE_EXIT("Return Value: 0x%p", this);
			return *this;
		}

		bool 
		_ptce_node::operator==(
			__in const _ptce_node &other
			)
		{
			bool result = true;
			size_t child_iter = 0;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				result = ((id() == other.m_uid)
						&& (m_entry == other.m_entry)
						&& (m_parent == other.m_parent)
						&& (m_children.size() == other.m_children.size()));

				if(result) {

					for(; child_iter < m_children.size(); ++child_iter) {

						if(m_children.at(child_iter) != other.m_children.at(child_iter)) {
							result = false;
							break;
						}
					}
				}
			}

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool 
		_ptce_node::operator!=(
			__in const _ptce_node &other
			)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result = !(*this == other);

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		std::vector<ptce_uid> &
		_ptce_node::children(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return m_children;
		}

		ptce_uid &
		_ptce_node::entry(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return m_entry;
		}

		std::string 
		_ptce_node::node_as_string(
			__in const _ptce_node &node,
			__in_opt bool verbose
			)
		{
			std::stringstream result;
			std::vector<ptce_uid>::const_iterator child_iter;

			TRACE_ENTRY();

			result << ptce_uid::id_as_string(node.m_uid) << ": " << "Entry: " << ptce_uid::id_as_string(node.m_entry) 
					<< ", Parent: " << ptce_uid::id_as_string(node.m_parent) << ", Children: " 
					<< node.m_children.size();

			if(verbose) {

				for(child_iter = node.m_children.begin(); child_iter != node.m_children.end(); ++child_iter) {
					result << std::endl << " --- " << ptce_uid::id_as_string(*child_iter);
				}
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}

		ptce_uid &
		_ptce_node::parent(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return m_parent;
		}

		size_t 
		_ptce_node::size(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result = m_children.size();

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		std::string 
		_ptce_node::to_string(
			__in_opt bool verbose
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", 0);
			return node_as_string(*this);
		}

		ptce_node_factory_ptr ptce_node_factory::m_instance = NULL;

		void 
		ptce_node_factory_destroy(void)
		{
			TRACE_ENTRY();

			if(ptce_node_factory::m_instance) {
				delete ptce_node_factory::m_instance;
				ptce_node_factory::m_instance = NULL;
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_node_factory::_ptce_node_factory(void) :
			m_initialized(false)
		{
			TRACE_ENTRY();

			std::atexit(ptce_node_factory_destroy);

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_node_factory::~_ptce_node_factory(void)
		{
			TRACE_ENTRY();

			if(m_initialized) {
				destroy();
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		ptce_node_factory_ptr 
		_ptce_node_factory::acquire(void)
		{
			ptce_node_factory_ptr result = NULL;

			TRACE_ENTRY();

			if(!m_instance) {

				m_instance = new ptce_node_factory;
				if(!m_instance) {
					THROW_PTCE_NODE_EXCEPTION(PTCE_NODE_EXCEPTION_ACQUIRE_FAILED);
				}
			}

			result = m_instance;

			TRACE_EXIT("Return Value: 0x%p", result);
			return result;
		}

		bool 
		_ptce_node_factory::contains(
			__in const ptce_uid &uid
			)
		{
			bool result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_NODE_EXCEPTION(PTCE_NODE_EXCEPTION_UNINITIAILIZED);
			}

			result = (m_node_map.find(uid) != m_node_map.end());

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool 
		_ptce_node_factory::contains(
			__in const ptce_node &node
			)
		{
			return contains(node.m_uid);
		}

		size_t 
		_ptce_node_factory::decrement_reference(
			__in const ptce_uid &uid
			)
		{
			size_t result = 0;
			std::map<ptce_uid, std::pair<ptce_node, size_t>>::iterator node_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_NODE_EXCEPTION(PTCE_NODE_EXCEPTION_UNINITIAILIZED);
			}

			node_iter = find_node(uid);

			if(node_iter->second.second == PTCE_INIT_REF_DEF) {
				m_node_map.erase(node_iter);
			} else {
				result = --node_iter->second.second;
			}

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_node_factory::decrement_reference(
			__in const ptce_node &node
			)
		{
			return decrement_reference(node.m_uid);
		}

		void 
		_ptce_node_factory::destroy(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_NODE_EXCEPTION(PTCE_NODE_EXCEPTION_UNINITIAILIZED);
			}

			m_node_map.clear();
			m_initialized = false;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		std::map<ptce_uid, std::pair<ptce_node, size_t>>::iterator 
		_ptce_node_factory::find_node(
			__in const ptce_uid &uid
			)
		{
			std::map<ptce_uid, std::pair<ptce_node, size_t>>::iterator result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_NODE_EXCEPTION(PTCE_NODE_EXCEPTION_UNINITIAILIZED);
			}

			result = m_node_map.find(uid);
			if(result == m_node_map.end()) {
				THROW_PTCE_NODE_EXCEPTION_MESSAGE(PTCE_NODE_EXCEPTION_UNKNOWN_NODE,
					"%s", ptce_uid::id_as_string(uid).c_str());
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result;
		}

		ptce_node &
		_ptce_node_factory::generate(
			__in const ptce_uid &entry,
			__in_opt const ptce_uid &parent,
			__in_opt const std::vector<ptce_uid> &children
			)
		{
			ptce_node node;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_NODE_EXCEPTION(PTCE_NODE_EXCEPTION_UNINITIAILIZED);
			}

			if(contains(node.id())) {
				THROW_PTCE_NODE_EXCEPTION_MESSAGE(PTCE_NODE_EXCEPTION_ALREADY_EXISTS,
					"%s", node.id().to_string().c_str());
			}

			m_node_map.insert(std::pair<ptce_uid, std::pair<ptce_node, size_t>>(node.id(), 
					std::pair<ptce_node, size_t>(ptce_node(node.id(), entry, parent, children), 
					PTCE_INIT_REF_DEF)));

			TRACE_EXIT("Return Value: 0x%x", 0);
			return find_node(node.id())->second.first;
		}

		size_t 
		_ptce_node_factory::increment_reference(
			__in const ptce_uid &uid
			)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_NODE_EXCEPTION(PTCE_NODE_EXCEPTION_UNINITIAILIZED);
			}

			result = ++find_node(uid)->second.second;

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_node_factory::increment_reference(
			__in const ptce_node &node
			)
		{
			return increment_reference(node.m_uid);
		}

		void 
		_ptce_node_factory::initialize(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(m_initialized) {
				THROW_PTCE_NODE_EXCEPTION(PTCE_NODE_EXCEPTION_INITIALIZED);
			}

			m_node_map.clear();
			m_initialized = true;

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		bool 
		_ptce_node_factory::is_allocated(void)
		{
			bool result;

			TRACE_ENTRY();

			result = (m_instance != NULL);

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		bool 
		_ptce_node_factory::is_initialized(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_initialized);
			return m_initialized;
		}

		size_t 
		_ptce_node_factory::reference_count(
			__in const ptce_uid &uid
			)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_NODE_EXCEPTION(PTCE_NODE_EXCEPTION_UNINITIAILIZED);
			}

			result = find_node(uid)->second.second;

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		size_t 
		_ptce_node_factory::reference_count(
			__in const ptce_node &node
			)
		{
			return reference_count(node.m_uid);
		}

		size_t 
		_ptce_node_factory::size(void)
		{
			size_t result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(!m_initialized) {
				THROW_PTCE_NODE_EXCEPTION(PTCE_NODE_EXCEPTION_UNINITIAILIZED);
			}

			result = m_node_map.size();

			TRACE_EXIT("Return Value: %lu", result);
			return result;
		}

		std::string 
		_ptce_node_factory::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;
			std::map<ptce_uid, std::pair<ptce_node, size_t>>::iterator node_iter;
	
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result << PTCE_NODE_TRACE_HEADER << " Instance=0x" << VALUE_AS_HEX(uintptr_t, m_instance) 
					<< ", Initialized=" << m_initialized << ", Count=" << m_node_map.size();

			if(verbose) {

				for(node_iter = m_node_map.begin(); node_iter != m_node_map.end(); ++node_iter) {
					result << std::endl << " --- " << ptce_node::node_as_string(node_iter->second.first)
						<< " (" << node_iter->second.second << ")";
				}
			}
		
			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}
	}
}
