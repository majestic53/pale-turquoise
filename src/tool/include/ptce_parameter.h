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

#ifndef PTCE_PARAMETER_H_
#define PTCE_PARAMETER_H_

#include "../../lib/include/ptce.h"

#ifndef PTCE_TOOL_NS
#define PTCE_TOOL_NS ptce_tool_ns
#endif // PTCE_TOOL_NS

namespace PTCE_NS {

	namespace PTCE_TOOL_NS {

		typedef enum _ptce_param_t {
			PARAMETER_CONNECTIONS = 0,
			PARAMETER_HELP,
			PARAMETER_PORT,
			PARAMETER_QUIET,
			PARAMETER_SHOW_BOARD,
			PARAMETER_SHOW_NETWORK,
			PARAMETER_VERSION,
		} ptce_param_t;

		#define PARAMETER_MAX PARAMETER_VERSION

		typedef std::map<ptce_param_t, std::pair<size_t, bool>> ptce_param_info_t;

		typedef class _ptce_parameter {

			public:

				_ptce_parameter(
					__in_opt size_t parameter_count = 0,
					__in_opt const char **parameters = NULL
					);

				_ptce_parameter(
					__in const _ptce_parameter &other
					);

				virtual ~_ptce_parameter(void);

				_ptce_parameter &operator=(
					__in const _ptce_parameter &other
					);

				uint8_t &connections(void);

				static std::string display_help(
					__in_opt bool verbose = false
					);

				static std::string display_version(
					__in_opt bool verbose = false
					);

				uint16_t &port(void);

				bool &quiet(void);

				bool &show_board(void);

				bool &show_help(void);

				bool &show_network(void);

				bool &show_version(void);

				virtual std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				bool determine_parameter_type(
					__out ptce_param_info_t &information,
					__in const char *parameter,
					__in_opt bool long_type = false
					);

				void parse(
					__in_opt size_t parameter_count = 0,
					__in_opt const char **parameters = NULL
					);

				uint8_t m_connections;

				uint16_t m_port;

				bool m_quiet;

				bool m_show_board;

				bool m_show_help;

				bool m_show_network;

				bool m_show_version;

			private:

				std::recursive_mutex m_lock;

		} ptce_parameter, *ptce_parameter_ptr;
	}
}

using namespace PTCE_NS::PTCE_TOOL_NS;

#endif // PTCE_PARAMETER_H_
