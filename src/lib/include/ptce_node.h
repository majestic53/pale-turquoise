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

#ifndef PTCE_NODE_H_
#define PTCE_NODE_H_

#include <map>
#include <vector>

namespace PTCE_NS {

	namespace PTCE_COMP_NS {

		typedef class _ptce_node :
				public ptce_uid_base {

			public:

				_ptce_node(void);

				_ptce_node(
					__in const ptce_uid &uid,
					__in_opt const ptce_uid &entry = ptce_uid(),
					__in_opt const ptce_uid &parent = ptce_uid(),
					__in_opt const std::vector<ptce_uid> &children = std::vector<ptce_uid>()
					);

				_ptce_node(
					__in const _ptce_node &other
					);

				virtual ~_ptce_node(void);

				_ptce_node &operator=(
					__in const _ptce_node &other
					);

				bool operator==(
					__in const _ptce_node &other
					);

				bool operator!=(
					__in const _ptce_node &other
					);

				std::vector<ptce_uid> &children(void);

				ptce_uid &entry(void);

				static std::string node_as_string(
					__in const _ptce_node &node,
					__in_opt bool verbose = false
					);

				ptce_uid &parent(void);

				size_t size(void);

				virtual std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				friend class _ptce_node_factory;

				std::vector<ptce_uid> m_children;

				ptce_uid m_entry;

				ptce_uid m_parent;

			private:

				std::recursive_mutex m_lock;

		} ptce_node, *ptce_node_ptr;

		void ptce_node_factory_destroy(void);

		typedef class _ptce_node_factory {

			public:

				~_ptce_node_factory(void);

				static _ptce_node_factory *acquire(void);

				bool contains(
					__in const ptce_node &node
					);

				size_t decrement_reference(
					__in const ptce_node &node
					);

				void destroy(void);

				ptce_node &generate(
					__in const ptce_uid &entry,
					__in_opt const ptce_uid &parent = ptce_uid(),
					__in_opt const std::vector<ptce_uid> &children = std::vector<ptce_uid>()
					);

				size_t increment_reference(
					__in const ptce_node &node
					);

				void initialize(void);

				static bool is_allocated(void);

				bool is_initialized(void);

				size_t reference_count(
					__in const ptce_node &node
					);

				size_t size(void);

				std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				friend void ptce_node_factory_destroy(void);

				_ptce_node_factory(void);

				_ptce_node_factory(
					__in const _ptce_node_factory &other
					);

				_ptce_node_factory &operator=(
					__in const _ptce_node_factory &other
					);

				std::map<ptce_uid, std::pair<ptce_node, size_t>>::iterator find_node(
					__in const ptce_uid &uid
					);

				bool m_initialized;

				static _ptce_node_factory *m_instance;

				std::map<ptce_uid, std::pair<ptce_node, size_t>> m_node_map;

			private:

				std::recursive_mutex m_lock;

		} ptce_node_factory, *ptce_node_factory_ptr;
	}
}

#endif // PTCE_NODE_H_
