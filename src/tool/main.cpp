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

void 
start_server(
	__in ptce_parameter &parameters
	)
{
	ptce_ptr inst = NULL;

	TRACE_ENTRY();

	inst = ptce::acquire();
	inst->initialize();
	inst->acquire_game_manager()->start(parameters.port(), parameters.connections(), 
			!parameters.quiet(), parameters.show_board(), parameters.show_network());
	inst->acquire_game_manager()->stop(!parameters.quiet());
	inst->destroy();

	TRACE_EXIT("Return Value: 0x%x", 0);
}

int 
main(
	__in int argc, 
	__in const char **argv
	)
{
	ptce_parameter param;
	std::vector<std::string> parameters;
	int iter = 1, result = PTCE_ERR_NONE;

	try {

		if(argc > 1) {

			for(; iter < argc; ++iter) {
				parameters.push_back(argv[iter]);
			}

			param = ptce_parameter(parameters);
			if(param.show_help()) {
				std::cout << param.display_help(true) << std::endl;
			} else if(param.show_version()) {
				std::cout << param.display_version() << std::endl;
			} else {
				start_server(param);
			}
		} else {
			start_server(param);
		}
	} catch(std::runtime_error &exc) {
		std::cerr << exc.what() << std::endl << std::endl
				<< param.display_help() << std::endl;
		result = PTCE_ERR_EXCEPTION;
	}

	return result;
}
