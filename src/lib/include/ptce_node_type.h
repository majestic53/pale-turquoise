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

#ifndef PTCE_NODE_TYPE_H_
#define PTCE_NODE_TYPE_H_

namespace PTCE_NS {

	namespace PTCE_COMP_NS {

		#ifndef NDEBUG
		#define PTCE_NODE_HEADER "(NODE)"
		#else
		#define PTCE_NODE_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		#define PTCE_NODE_TRACE_HEADER "(NODE)"

		enum {
			PTCE_NODE_EXCEPTION_ACQUIRE_FAILED = 0,
			PTCE_NODE_EXCEPTION_ALREADY_EXISTS,
			PTCE_NODE_EXCEPTION_INITIALIZED,
			PTCE_NODE_EXCEPTION_UNINITIAILIZED,
			PTCE_NODE_EXCEPTION_UNKNOWN_NODE,
		};

		#define PTCE_NODE_EXCEPTION_MAX PTCE_NODE_EXCEPTION_UNKNOWN_NODE

		static const std::string PTCE_NODE_EXCEPTION_STR[] = {
			PTCE_NODE_HEADER " Failed to acquire node factory",
			PTCE_NODE_HEADER " Node already exists",
			PTCE_NODE_HEADER " Node factory is already initialized",
			PTCE_NODE_HEADER " Node factory is uninitialized",
			PTCE_NODE_HEADER " Node does not exist",
			};

		#define PTCE_NODE_EXCEPTION_STRING(_EXCEPT_) \
			((_EXCEPT_) > PTCE_NODE_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
			PTCE_NODE_EXCEPTION_STR[_EXCEPT_].c_str())

		#define THROW_PTCE_NODE_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(PTCE_NODE_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_PTCE_NODE_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(PTCE_NODE_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _ptce_node;
		typedef _ptce_node ptce_node, *ptce_node_ptr;

		class _ptce_node_factory;
		typedef _ptce_node_factory ptce_node_factory, *ptce_node_factory_ptr;
	}
}

#endif // PTCE_NODE_TYPE_H_
