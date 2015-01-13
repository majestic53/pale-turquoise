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

#ifndef PTCE_UID_TYPE_H_
#define PTCE_UID_TYPE_H_

namespace PTCE_NS {

	namespace PTCE_COMP_NS {

		#ifndef NDEBUG
		#define PTCE_UID_HEADER "(UID)"
		#else
		#define PTCE_UID_HEADER EXCEPTION_HEADER
		#endif // NDEBUG

		#define PTCE_UID_TRACE_HEADER "(UID)"

		enum {
			PTCE_UID_EXCEPTION_ACQUIRE_FAILED = 0,
			PTCE_UID_EXCEPTION_EXISTS,
			PTCE_UID_EXCEPTION_INITIALIZED,
			PTCE_UID_EXCEPTION_UNINITIALIZED,
			PTCE_UID_EXCEPTION_UNKNOWN_UID,
		};

		#define PTCE_UID_EXCEPTON_MAX PTCE_UID_EXCEPTION_UNKNOWN_UID

		static const std::string PTCE_UID_EXCEPTION_STR[] = {
			PTCE_UID_HEADER " Failed to acquire uid factory",
			PTCE_UID_HEADER " Uid already exists",
			PTCE_UID_HEADER " Uid factory is already initialized",
			PTCE_UID_HEADER " Uid factory is uninitialized",
			PTCE_UID_HEADER " Uid does not exist",
			};

		#define PTCE_UID_EXCEPTION_STRING(_EXCEPT_) \
			((_EXCEPT_) > PTCE_UID_EXCEPTON_MAX ? UNKNOWN_EXCEPTION : \
			PTCE_UID_EXCEPTION_STR[_EXCEPT_].c_str())

		#define THROW_PTCE_UID_EXCEPTION(_EXCEPT_) \
			THROW_EXCEPTION(PTCE_UID_EXCEPTION_STRING(_EXCEPT_))
		#define THROW_PTCE_UID_EXCEPTION_MESSAGE(_EXCEPT_, _FORMAT_, ...) \
			THROW_EXCEPTION_MESSAGE(PTCE_UID_EXCEPTION_STRING(_EXCEPT_), _FORMAT_, __VA_ARGS__)

		class _ptce_uid;
		typedef _ptce_uid ptce_uid, *ptce_uid_ptr;

		class _ptce_uid_factory;
		typedef _ptce_uid_factory ptce_uid_factory, *ptce_uid_factory_ptr;

		class _ptce_uid_base;
		typedef _ptce_uid_base ptce_uid_base, *ptce_uid_base_ptr;
	}
}

#endif // PTCE_UID_TYPE_H_
