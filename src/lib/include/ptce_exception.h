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

#ifndef PTCE_EXCEPTION_H_
#define PTCE_EXCEPTION_H_

namespace PTCE_NS {
		
	#define EXCEPTION_HEADER "(Exception)"
		
	#define THROW_EXCEPTION(_EXCEPT_) \
		throw std::runtime_error(format_string(_EXCEPT_).c_str())
	#define THROW_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
		throw std::runtime_error(format_string("%s: " _FORMAT_, \
		_EXCEPT_, __VA_ARGS__).c_str())
}

#endif // PTCE_EXCEPTION_H_
