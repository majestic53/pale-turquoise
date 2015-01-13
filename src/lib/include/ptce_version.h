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

#ifndef PTCE_VERSION_H_
#define PTCE_VERSION_H_

namespace PTCE_NS {

	#define BUILD_TITLE "libptce"
	#define BUILD_COPYRIGHT "Copyright (C) 2015 David Jolly"

	#define BUILD_DATE __DATE__
	#define BUILD_TIME __TIME__

	#define VERSION_MAJ 0
	#define VERSION_MIN 1
	#define VERSION_REV 4
	#define VERSION_WEEK 1502
	
	#define VERSION_STR \
		"" CONCAT(VERSION_MAJ) "." CONCAT(VERSION_MIN) "." CONCAT(VERSION_WEEK) \
		"-" CONCAT(VERSION_REV)
	#define VERSION_STR_VERB VERSION_STR " (" BUILD_DATE ", " BUILD_TIME ")"
}

#endif // PTCE_VERSION_H_
