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

#ifndef PTCE_UID_H_
#define PTCE_UID_H_

#include <map>
#include <random>

namespace PTCE_NS {

	namespace PTCE_COMP_NS {

		#define PTCE_UID_DEF 0

		typedef class _ptce_uid {

			public:

				_ptce_uid(
					__in_opt uint64_t uid = PTCE_UID_DEF
					);

				_ptce_uid(
					__in const _ptce_uid &other
					);

				virtual ~_ptce_uid(void);

				_ptce_uid &operator=(
					__in const _ptce_uid &other
					);

				bool operator==(
					__in const _ptce_uid &other
					);

				bool operator!=(
					__in const _ptce_uid &other
					);

				uint64_t &id(void);

				static std::string id_as_string(
					__in const _ptce_uid &uid,
					__in_opt bool verbose = false
					);

				virtual std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				friend bool operator==(
					__in const _ptce_uid &left,
					__in const _ptce_uid &right
					);

				friend bool operator<(
					__in const _ptce_uid &left,
					__in const _ptce_uid &right
					);

				friend class _ptce_uid_factory;

				uint64_t m_uid;

			private:

				std::recursive_mutex m_lock;

		} ptce_uid, *ptce_uid_ptr;

		bool operator==(
			__in const _ptce_uid &left,
			__in const _ptce_uid &right
			);

		bool operator<(
			__in const _ptce_uid &left,
			__in const _ptce_uid &right
			);

		#define UID_NULL ptce_uid(UINT64_MAX)

		void ptce_uid_factory_destroy(void);

		typedef class _ptce_uid_factory {

			public:

				~_ptce_uid_factory(void);

				static _ptce_uid_factory *acquire(void);

				size_t add(
					__in const ptce_uid &uid,
					__in_opt bool unique = false
					);

				bool contains(
					__in const ptce_uid &uid
					);

				size_t decrement_reference(
					__in const ptce_uid &uid
					);

				void destroy(void);

				ptce_uid generate(
					__in bool unique
					);

				size_t increment_reference(
					__in const ptce_uid &uid
					);

				void initialize(void);

				static bool is_allocated(void);

				bool is_initialized(void);

				size_t reference_count(
					__in const ptce_uid &uid
					);

				size_t size(void);

				std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				friend void ptce_uid_factory_destroy(void);

				_ptce_uid_factory(void);

				_ptce_uid_factory(
					__in const _ptce_uid_factory &other
					);

				_ptce_uid_factory &operator=(
					__in const _ptce_uid_factory &other
					);

				std::map<ptce_uid, size_t>::iterator find_uid(
					__in const ptce_uid &uid
					);

				std::uniform_int_distribution<uint32_t> m_distribution;

				std::default_random_engine m_generator;

				bool m_initialized;

				static _ptce_uid_factory *m_instance;

				std::map<ptce_uid, size_t> m_uid_map;

			private:

				std::recursive_mutex m_lock;

		} ptce_uid_factory, *ptce_uid_factory_ptr;

		typedef class _ptce_uid_base {

			public:

				_ptce_uid_base(void);

				_ptce_uid_base(
					__in const ptce_uid uid
					);

				_ptce_uid_base(
					__in const _ptce_uid_base &other
					);

				virtual ~_ptce_uid_base(void);

				_ptce_uid_base &operator=(
					__in const _ptce_uid_base &other
					);

				size_t decrement_reference(void);

				ptce_uid &id(void);

				size_t increment_reference(void);

				size_t reference_count(void);

				virtual std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				friend class _ptce_game_manager;

				ptce_uid generate_id(
					__in bool unique
					);

				ptce_uid m_uid;

			private:

				std::recursive_mutex m_lock;

		} ptce_uid_base, *ptce_uid_base_ptr;
	}
}

#endif // PTCE_UID_H_
