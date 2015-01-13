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

#ifndef PTCE_DEFINES_H_
#define PTCE_DEFINES_H_

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>

namespace PTCE_NS {

	#define __in
	#define __in_opt
	#define __out
	#define __out_opt
	#define __inout
	#define __inout_opt
	
	#define EMPTY "(EMPTY)"
	#define ERROR "(ERROR)"
	#define UNKNOWN "(UNKNOWN)"
	#define UNKNOWN_EXCEPTION "(UNKNOWN EXCEPTION)"
	
	#define APPEND(_VALUE0_, _VALUE1_) _VALUE0_ ## _VALUE1_
	
	#define _CONCAT(_VALUE_) # _VALUE_
	#define CONCAT(_VALUE_) _CONCAT(_VALUE_)

	#define INVALID(_TYPE_) ((_TYPE_) (-1))
	
	#define _SERIALIZE_CALL(_TYPE_, _MUTEX_) \
		std::lock_guard<_TYPE_> APPEND(__LOCK_, _MUTEX_)(_MUTEX_)
	#define SERIALIZE_CALL(_MUTEX_) \
		_SERIALIZE_CALL(std::mutex, _MUTEX_)
	#define SERIALIZE_CALL_RECUR(_MUTEX_) \
		_SERIALIZE_CALL(std::recursive_mutex, _MUTEX_)
	
	#define UNREF_PARAM(_PARAM_) (void) _PARAM_
	
	#define VALUE_AS_HEX(_TYPE_, _VALUE_) \
		std::setw(sizeof(_TYPE_) * 2) << std::setfill('0') << std::hex \
		<< (uintmax_t) ((_TYPE_) (_VALUE_)) << std::dec
	
	typedef uint16_t type_t;
	
	std::string format_string(
		__in const char *format,
		...
		);
}

#endif // PTCE_DEFINES_H_
