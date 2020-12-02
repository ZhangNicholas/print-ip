#pragma once

#include <utility>
#include <type_traits>
#include <list>
#include <vector>

/**
 *  Enum defines container types which will be printed by the same overload of the print_ip function.
 */

namespace is_stl_container_impl {
	template <typename T>       struct is_stl_container :std::false_type {};
	template <typename... Args> struct is_stl_container<std::vector            <Args...>> :std::true_type {};
	template <typename... Args> struct is_stl_container<std::list              <Args...>> :std::true_type {};
}

template <typename T> struct is_stl_container {
	static constexpr bool const value = is_stl_container_impl::is_stl_container<std::decay_t<T>>::value;
};