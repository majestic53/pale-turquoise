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

#include "./include/ptce_parameter.h"

enum {
	PTCE_ERR_NONE = 0,
	PTCE_ERR_EXCEPTION,
};

int 
main(
	__in int argc, 
	__in const char **argv
	)
{
	ptce_ptr inst = NULL;
	int result = PTCE_ERR_NONE;
	ptce_parameter param(argc, argv);

	if(param.show_help()) {
		std::cout << param.display_help(true) << std::endl;
	} else if(param.show_version()) {
		std::cout << param.display_version() << std::endl;
	} else {

		try {
			inst = ptce::acquire();
			inst->initialize();
			inst->acquire_game_manager()->start(param.port(), param.connections(), !param.quiet(),
					param.show_board(), param.show_network());
			inst->acquire_game_manager()->stop(!param.quiet());
			inst->destroy();
		} catch(std::runtime_error &exc) {
			std::cerr << exc.what() << std::endl << std::endl
					<< param.display_help() << std::endl;
			result = PTCE_ERR_EXCEPTION;
		}
	}

	return result;
}
