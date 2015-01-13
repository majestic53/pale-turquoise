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

#include <cerrno>
#include <cstdarg>
#include <cstdio>
#include "../include/ptce.h"
#include "../include/ptce_defines_type.h"

namespace PTCE_NS {

	#define FORMATTED_LEN_MAX 1024

	std::string 
	format_string(
		__in const char *format,
		...
		)
	{
		int length;
		va_list arguments;
		std::string result;
		
		if(!format) {
			result = EMPTY;
			goto exit;
		}

		va_start(arguments, format);
		
		result.resize(FORMATTED_LEN_MAX);

		length = vsnprintf((char *) &result[0], FORMATTED_LEN_MAX, 
				format, arguments) + 1;
				
		if(length <= 0) {
			result = ERROR;
			std::perror(PTCE_DEFINES_EXCEPTION_STRING(
					PTCE_DEFINES_EXCEPTION_INVALID_FORMAT));
			goto cleanup;
		}
		
cleanup:
		va_end(arguments);
		
exit:
		return result;
	}
}
