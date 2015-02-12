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

#include "../include/ptce_parameter.h"
#include "../include/ptce_parameter_type.h"

namespace PTCE_NS {

	namespace PTCE_TOOL_NS {
		
		#define ARGUMENT_CONNECTIONS_MAX (UINT8_MAX)
		#define PARAMETER_DELIM '-'
		#define TOOL_TITLE_STR "ptce"
		#define TOOL_USAGE_STR "[-h | -v | -q | -b | -n] [-p PORT] [-c MAX CONN]"

		static const std::string PARAMETER_DESC_STR[] = {
			"Maximum client connections (default: 5, max: 255)",
			"Display help",
			"Server port (default: 2000, max: 65536)",
			"Quiet mode",
			"Display game boards",
			"Display game network traffic",
			"Display version",
			};

		#define PARAMETER_DESCRIPTION_STRING(_TYPE_) \
			((_TYPE_) > PARAMETER_MAX ? UNKNOWN : \
			PARAMETER_DESC_STR[_TYPE_].c_str())

		static const std::string PARAMETER_SHORT_STR[] = {
			"c", "h", "p", "q", "b", "n", "v",
			};

		#define PARAMETER_SHORT_STRING(_TYPE_) \
			((_TYPE_) > PARAMETER_MAX ? UNKNOWN : \
			PARAMETER_SHORT_STR[_TYPE_].c_str())

		static const std::string PARAMETER_LONG_STR[] = {
			"conn", "help", "port", "quiet", "board", "net", "version",
			};

		#define PARAMETER_LONG_STRING(_TYPE_) \
			((_TYPE_) > PARAMETER_MAX ? UNKNOWN : \
			PARAMETER_LONG_STR[_TYPE_].c_str())

		static const ptce_param_info_map PARAMETER_INFO_MAP = {
			std::pair<ptce_param_t, ptce_param_info_t>(PARAMETER_CONNECTIONS, ptce_param_info_t(1, false)),
			std::pair<ptce_param_t, ptce_param_info_t>(PARAMETER_HELP, ptce_param_info_t(0, false)),
			std::pair<ptce_param_t, ptce_param_info_t>(PARAMETER_PORT, ptce_param_info_t(1, false)),
			std::pair<ptce_param_t, ptce_param_info_t>(PARAMETER_QUIET, ptce_param_info_t(0, false)),
			std::pair<ptce_param_t, ptce_param_info_t>(PARAMETER_SHOW_BOARD, ptce_param_info_t(0, false)),
			std::pair<ptce_param_t, ptce_param_info_t>(PARAMETER_SHOW_NETWORK, ptce_param_info_t(0, false)),
			std::pair<ptce_param_t, ptce_param_info_t>(PARAMETER_VERSION, ptce_param_info_t(0, false)),
			};

		_ptce_parameter::_ptce_parameter(
			__in_opt const std::vector<std::string> &parameters
			) :
				m_connections(GAME_CONNECTION_DEF),
				m_port(GAME_PORT_DEF),
				m_quiet(false),
				m_show_board(false),
				m_show_help(false),
				m_show_network(false),
				m_show_version(false)
		{
			TRACE_ENTRY();

			if(!parameters.empty()) {
				parse(parameters);
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_parameter::_ptce_parameter(
			__in const _ptce_parameter &other
			) :
				m_connections(other.m_connections),
				m_found(other.m_found),
				m_port(other.m_port),
				m_quiet(other.m_quiet),
				m_show_board(other.m_show_board),
				m_show_help(other.m_show_help),
				m_show_network(other.m_show_network),
				m_show_version(other.m_show_version)
		{
			TRACE_ENTRY();
			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_parameter::~_ptce_parameter(void)
		{
			TRACE_ENTRY();

			m_found.clear();

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_parameter &
		_ptce_parameter::operator=(
			__in const _ptce_parameter &other
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(this != &other) {
				m_connections = other.m_connections;
				m_found = other.m_found;
				m_port = other.m_port;
				m_quiet = other.m_quiet;
				m_show_board = other.m_show_board;
				m_show_help = other.m_show_help;
				m_show_network = other.m_show_network;
				m_show_version = other.m_show_version;
			}

			TRACE_EXIT("Return Value: 0x%p", this);
			return *this;
		}

		uint16_t &
		_ptce_parameter::connections(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: %i", m_connections);
			return m_connections;
		}

		bool 
		_ptce_parameter::determine_parameter_type(
			__out ptce_param_info_map::const_iterator &information,
			__in const std::string &parameter,
			__in_opt bool long_type
			)
		{
			size_t iter = 0;
			bool result = false;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			if(parameter.empty()) {
				THROW_PTCE_PARAMETER_EXCEPTION(PTCE_PARMAETER_EXCEPTION_EMPTY_PARAMETER);
			}

			for(; iter <= PARAMETER_MAX; ++iter) {

				if(parameter == (long_type ? PARAMETER_LONG_STRING(iter) 
						: PARAMETER_SHORT_STRING(iter))) {

					information = PARAMETER_INFO_MAP.find((ptce_param_t) iter);
					if(information == PARAMETER_INFO_MAP.end()) {
						THROW_PTCE_PARAMETER_EXCEPTION_MESSAGE(PTCE_PARAMETER_EXCEPTION_INVALID_PARAMETER,
							"%s", (long_type ? PARAMETER_LONG_STRING(iter) 
							: PARAMETER_SHORT_STRING(iter)));
					}

					result = true;
					break;
				}
			}

			TRACE_EXIT("Return Value: 0x%x", result);
			return result;
		}

		std::string 
		_ptce_parameter::display_help(
			__in_opt bool verbose
			)
		{
			size_t iter = 0;
			std::stringstream result;

			TRACE_ENTRY();

			if(verbose) {
				result << display_version(true) << std::endl << std::endl;
			}

			result << TOOL_TITLE_STR << " " << TOOL_USAGE_STR << std::endl;

			for(; iter <= PARAMETER_MAX; ++iter) {
				result << std::endl << PARAMETER_DELIM << PARAMETER_SHORT_STRING(iter) << " | "
						<< PARAMETER_DELIM << PARAMETER_DELIM << PARAMETER_LONG_STRING(iter)
						<< "\t" << PARAMETER_DESCRIPTION_STRING(iter);
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}

		std::string 
		_ptce_parameter::display_version(
			__in_opt bool verbose
			)
		{
			std::stringstream result;

			TRACE_ENTRY();

			if(verbose) {
				result << BUILD_TITLE << " ";
			}

			result << ptce::version();

			if(verbose) {
				result << std::endl << BUILD_COPYRIGHT;
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}

		void 
		_ptce_parameter::parse(
			__in_opt const std::vector<std::string> &parameters
			)
		{
			bool long_type;
			std::string param;
			size_t arg_iter, iter;
			std::stringstream convert;
			std::vector<std::string> arguments;
			ptce_param_info_map::const_iterator information;
			ptce_param_info_map::const_iterator param_map_iter;
			std::vector<std::string>::const_iterator param_iter;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			m_connections = GAME_CONNECTION_DEF;
			m_found.clear();
			m_found.resize(PARAMETER_MAX + 1, false);
			m_port = GAME_PORT_DEF;
			m_quiet = false;
			m_show_board = false;
			m_show_help = false;
			m_show_network = false;
			m_show_version = false;

			for(iter = 0, param_iter = parameters.begin(); param_iter != parameters.end(); ++iter, ++param_iter) {
				param = *param_iter;
				std::transform(param.begin(), param.end(), param.begin(), ::tolower);
				arguments.clear();
				long_type = false;

				if(param.empty()) {
					THROW_PTCE_PARAMETER_EXCEPTION_MESSAGE(PTCE_PARMAETER_EXCEPTION_EMPTY_PARAMETER,
						"[%lu]", iter);
				} else if(param.front() != PARAMETER_DELIM) {
					THROW_PTCE_PARAMETER_EXCEPTION_MESSAGE(PTCE_PARAMETER_EXCEPTION_INVALID_PARAMETER,
						"[%lu] %s", iter, param.c_str());
				}

				param = param.substr(1, param.size());

				if(param.front() == PARAMETER_DELIM) {
					param = param.substr(1, param.size());
					long_type = true;
				}

				if(!determine_parameter_type(information, param, long_type)) {
					THROW_PTCE_PARAMETER_EXCEPTION_MESSAGE(PTCE_PARAMETER_EXCEPTION_UNKNOWN_PARAMETER,
						"[%lu] %s", iter, param.c_str());
				}

				if(m_found.at((size_t) information->first)) {
					THROW_PTCE_PARAMETER_EXCEPTION_MESSAGE(PTCE_PARAMETER_EXCEPTION_DUPLICATE_PARAMETER,
						"[%lu] %s", iter, param.c_str());
				}

				if(information->second.first) {
					arg_iter = 0;

					do {

						++param_iter;
						if((param_iter == parameters.end())
								|| (param_iter->front() == PARAMETER_DELIM)) {
							THROW_PTCE_PARAMETER_EXCEPTION_MESSAGE(PTCE_PARAMETER_EXCEPTION_MISSING_PARAMETER_ARGUMENT,
								"[%lu] %s (req: %lu)", iter, param.c_str(), information->second.first);
						}

						arguments.push_back(*param_iter);
					} while(++arg_iter < information->second.first);
				}

				switch(information->first) {
					case PARAMETER_CONNECTIONS:
					case PARAMETER_PORT:

						if(!arguments.empty()) {
							convert.clear();
							convert.str(arguments.front());

							if(information->first == PARAMETER_CONNECTIONS) {
								convert >> m_connections;

								if(m_connections > ARGUMENT_CONNECTIONS_MAX) {
									THROW_PTCE_PARAMETER_EXCEPTION_MESSAGE(
										PTCE_PARAMETER_EXCEPTION_INVALID_PARAMETER_ARGUMENT,
										"[%lu] %s (must be at most: %i)", iter, param.c_str(), 
										ARGUMENT_CONNECTIONS_MAX);
								}
							} else {
								convert >> m_port;
							}
						}
						break;
					case PARAMETER_HELP:
						m_show_help = true;
						break;
					case PARAMETER_QUIET:
						m_quiet = true;
						break;
					case PARAMETER_SHOW_BOARD:
						m_show_board = true;
						break;
					case PARAMETER_SHOW_NETWORK:
						m_show_network = true;
						break;
					case PARAMETER_VERSION:
						m_show_version = true;
						break;
					default:
						THROW_PTCE_PARAMETER_EXCEPTION_MESSAGE(PTCE_PARAMETER_EXCEPTION_UNKNOWN_PARAMETER,
							"[%lu] %s", iter, param.c_str());
				}

				m_found.at((size_t) information->first) = true;
			}

			for(iter = 0, param_map_iter = PARAMETER_INFO_MAP.begin(); param_map_iter != PARAMETER_INFO_MAP.end(); 
					++iter, ++param_map_iter) {

				if(!m_found.at(iter) && param_map_iter->second.second) {
					THROW_PTCE_PARAMETER_EXCEPTION_MESSAGE(PTCE_PARAMETER_EXCEPTION_MISSING_PARAMETER,
						"[%lu] %s", iter, PARAMETER_LONG_STRING(param_map_iter->first));
				}
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		uint16_t &
		_ptce_parameter::port(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: %i", m_port);
			return m_port;
		}

		bool &
		_ptce_parameter::quiet(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_quiet);
			return m_quiet;
		}

		bool &
		_ptce_parameter::show_board(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_show_board);
			return m_show_board;
		}

		bool &
		_ptce_parameter::show_help(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_show_help);
			return m_show_help;
		}

		bool &
		_ptce_parameter::show_network(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_show_network);
			return m_show_network;
		}

		bool &
		_ptce_parameter::show_version(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: 0x%x", m_show_version);
			return m_show_version;
		}

		std::string 
		_ptce_parameter::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;

			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			result << "Port: " << m_port << ", Max Connections: " << (int) m_connections;

			if(verbose) {

				if(!m_quiet) {
					result << ", Debug Mode: {";

					if(m_show_board) {
						result << "BOARD";
					}

					if(m_show_network) {

						if(m_show_board) {
							result << " | ";
						}

						result << "NETWORK";
					}

					result << "}";
				} else {
					result << ", Quiet";
				} 
			}

			TRACE_EXIT("Return Value: 0x%x", 0);
			return result.str();
		}
	}
}
