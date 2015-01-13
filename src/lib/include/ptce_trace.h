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

#ifndef PTCE_TRACE_H_
#define PTCE_TRACE_H_

namespace PTCE_NS {

	#ifndef NDEBUG
	#define TRACE_ENTRY() \
		std::cout << format_string("+%s: (%s:%lu)", __FUNCTION__, __FILE__, __LINE__) << std::endl
	#define TRACE_EXIT(_FORMAT_, ...) \
		std::cout << format_string("-%s: " _FORMAT_ ": (%s:%lu)", __FUNCTION__, __VA_ARGS__, \
		__FILE__, __LINE__) << std::endl
	#define TRACE_MESSAGE(_FORMAT_, ...) \
		std::cout << format_string("%s%s: " _FORMAT_ ": (%s:%lu)", _PREFIX_, __FUNCTION__, \
		__VA_ARGS__, __FILE__, __LINE__) << std::endl
	#else
	#define TRACE_ENTRY()
	#define TRACE_EXIT(_FORMAT_, ...)
	#define TRACE_MESSAGE(_FORMAT_, ...)
	#endif // NDEBUG
}

#endif // PTCE_TRACE_H_
