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

#ifndef PTCE_TYPE_H_
#define PTCE_TYPE_H_

namespace PTCE_NS {

	#ifndef NDEBUG
	#define PTCE_HEADER "(PTCE)"
	#else
	#define PTCE_HEADER EXCEPTION_HEADER
	#endif // NDEBUG

	#define PTCE_TRACE_HEADER "(PTCE)"
	
	enum {
		PTCE_EXCEPTION_ACQUIRE_FAILED = 0,
		PTCE_EXCEPTION_INITIALIZED,
		PTCE_EXCEPTION_UNINITIALIZED,
	};
	
	#define PTCE_EXCEPTION_MAX PTCE_EXCEPTION_UNINITIALIZED
	
	static const std::string PTCE_EXCEPTION_STR[] = {
		PTCE_HEADER " Failed to acquire instance",
		PTCE_HEADER " Library is already initialized",
		PTCE_HEADER " Library is uninitialized",
		};
		
	#define PTCE_EXCEPTION_STRING(_EXCEPT_) \
		((_EXCEPT_) > PTCE_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
		PTCE_EXCEPTION_STR[_EXCEPT_].c_str())
		
	#define THROW_PTCE_EXCEPTION(_EXCEPT_) \
		THROW_EXCEPTION(PTCE_EXCEPTION_STRING(_EXCEPT_))
	#define THROW_PTCE_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
		THROW_EXCEPTION_MESSAGE(PTCE_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, \
		__VA_ARGS__)
	
	class _ptce;
	typedef _ptce ptce, *ptce_ptr;
}

#endif // PTCE_TYPE_H_
