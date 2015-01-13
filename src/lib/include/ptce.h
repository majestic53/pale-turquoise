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

#ifndef PTCE_H_
#define PTCE_H_

#define NDEBUG

#ifndef PTCE_NS
#define PTCE_NS ptce_ns
#endif // PTCE_NS

#include "ptce_defines.h"
#include "ptce_version.h"
#include "ptce_exception.h"
#include "ptce_trace.h"

#ifndef PTCE_COMP_NS
#define PTCE_COMP_NS ptce_comp_ns
#endif // PTCE_COMP_NS

#include "ptce_uid.h"
#include "ptce_node.h"

using namespace PTCE_NS;
using namespace PTCE_NS::PTCE_COMP_NS;

namespace PTCE_NS {

	void ptce_destroy(void);

	typedef class _ptce {
	
		public:
		
			~_ptce(void);
		
			static _ptce *acquire(void);

			ptce_node_factory_ptr acquire_node_factory(void);
			
			ptce_uid_factory_ptr acquire_uid_factory(void);

			void destroy(void);
			
			void initialize(void);
		
			static bool is_allocated(void);
		
			bool is_initialized(void);
		
			std::string to_string(
				__in_opt bool verbose = false
				);
		
			static std::string version(
				__in_opt bool verbose = false
				);
		
		protected:
		
			friend void ptce_destroy(void);
		
			_ptce(void);
			
			_ptce(
				__in const _ptce &other
				);
				
			_ptce &operator=(
				__in const _ptce &other
				);
				
			bool m_initialized;
				
			static _ptce *m_instance;
		
			ptce_node_factory_ptr m_factory_node;

			ptce_uid_factory_ptr m_factory_uid;

		private:
		
			std::recursive_mutex m_lock;
	
	} ptce, *ptce_ptr;
}

#endif // PTCE_H_
