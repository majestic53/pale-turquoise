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
		
		#define PARAMETER_DELIM '-'
		#define TOOL_TITLE_STR "ptce"
		#define TOOL_USAGE_STR "[-h | -v | -q | -b | -n] [-p PORT] [-c MAX CONN]"

		enum {
			PARAMATER_CONNECTIONS = 0,
			PARAMETER_HELP,
			PARAMETER_PORT,
			PARAMETER_QUIET,
			PARAMETER_SHOW_BOARD,
			PARAMETER_SHOW_NETWORK,
			PARAMETER_VERSION,
		};

		#define PARAMETER_MAX PARAMETER_VERSION

		static const std::string PARAMETER_DESC_STR[] = {
			"Maximum client connections",
			"Display help",
			"Server port",
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

		_ptce_parameter::_ptce_parameter(
			__in_opt size_t argc,
			__in_opt const char **argv
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

			parse(argc, argv);

			TRACE_EXIT("Return Value: 0x%x", 0);
		}

		_ptce_parameter::_ptce_parameter(
			__in const _ptce_parameter &other
			) :
				m_connections(other.m_connections),
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

		uint8_t &
		_ptce_parameter::connections(void)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);
			TRACE_EXIT("Return Value: %i", m_connections);
			return m_connections;
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
			__in_opt size_t argc,
			__in_opt const char **argv
			)
		{
			TRACE_ENTRY();
			SERIALIZE_CALL_RECUR(m_lock);

			// TODO: parse user parameters

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
