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

#ifndef PTCE_DEFINES_TYPE_H_
#define PTCE_DEFINES_TYPE_H_

namespace PTCE_NS {

	#ifndef NDEBUG
	#define PTCE_TRACE_HEADER "(TRACE)"
	#else
	#define PTCE_TRACE_HEADER EXCEPTION_HEADER
	#endif // NDEBUG

	enum {
		PTCE_DEFINES_EXCEPTION_INVALID_FORMAT = 0,
	};
	
	#define PTCE_DEFINES_EXCEPTION_MAX PTCE_DEFINES_EXCEPTION_INVALID_FORMAT
	
	static const std::string PTCE_DEFINES_EXCEPTION_STR[] = {
		PTCE_TRACE_HEADER " Formatting string failed",
		};
		
	#define PTCE_DEFINES_EXCEPTION_STRING(_EXCEPT_) \
		((_EXCEPT_) > PTCE_DEFINES_EXCEPTION_MAX ? UNKNOWN_EXCEPTION : \
		PTCE_DEFINES_EXCEPTION_STR[_EXCEPT_].c_str())
}

#endif // PTCE_DEFINES_TYPE_H_
