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

#ifndef PTCE_PARAMETER_TYPE_H_
#define PTCE_PARAMETER_TYPE_H_

namespace PTCE_NS {

	namespace PTCE_TOOL_NS {

		#ifndef NDEBUG
		#define PTCE_PARAMETER_HEADER "(PARAMETER)"
		#else
		#define PTCE_PARAMETER_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		enum {
			PTCE_PARMAETER_EXCEPTION_EMPTY_PARAMETER = 0,
			PTCE_PARAMETER_EXCEPTION_INVALID_PARAMETER,
			PTCE_PARAMETER_EXCEPTION_MISSING_PARAMETER,
			PTCE_PARAMETER_EXCEPTION_MISSING_PARAMETER_ARGUMENT,
			PTCE_PARAMETER_EXCEPTION_UNKNOWN_PARAMETER,
		};

		#define PTCE_PARAMETER_EXCEPTION_MAX PTCE_PARAMETER_EXCEPTION_UNKNOWN_PARAMETER

		static const std::string PTCE_PARAMETER_EXCEPTION_STR[] = {
			PTCE_PARAMETER_HEADER " Empty parameter",
			PTCE_PARAMETER_HEADER " Invalid parameter",
			PTCE_PARAMETER_HEADER " Missing parameter",
			PTCE_PARAMETER_HEADER " Missing parameter argument",
			PTCE_PARAMETER_HEADER " Unknown parameter",
			};

		#define PTCE_PARAMETER_EXCEPTION_STRING(_EXCEPT_) \
			((_EXCEPT_) > PTCE_PARAMETER_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
			PTCE_PARAMETER_EXCEPTION_STR[_EXCEPT_].c_str())

		#define THROW_PTCE_PARAMETER_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(PTCE_PARAMETER_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_PTCE_PARAMETER_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(PTCE_PARAMETER_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _ptce_parameter;
		typedef _ptce_parameter ptce_parameter, *ptce_parameter_ptr;	
	}
}

#endif // PTCE_PARAMETER_TYPE_H_
