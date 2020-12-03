#include <cstddef> // std::size_t
#include <typeinfo> // typeid
#include <iostream>
#include <type_traits> // std::is_...
#include <vector>
#include <list>
#include <tuple>

#include "is_stl_container.h"

/**
* Integral types overload
*/

template <typename T> // integral types
auto print_ip(const T& someIntType)
-> std::enable_if_t<std::is_integral<T>::value>
{
	const uint8_t* val_lsb = reinterpret_cast<const uint8_t*>(&someIntType) + sizeof(someIntType) - 1; // pointer to the lsb
	for (size_t it = 0; it < sizeof(someIntType); ++it) {
		if (it != 0) {
			std::cout << ".";
		}
		std::cout << +*val_lsb;
		--val_lsb;
	}
	std::cout << std::endl;
}

/**
* Container types overload
*/

template <typename T> // vector, list
auto print_ip(const T& container)
-> std::enable_if_t<is_stl_container<T>::value>
{
	for (auto it = container.begin(); it != container.end(); ++it) {
		if (it != container.begin()) {
			std::cout << ".";
		}
		std::cout << +*it;
	}
	std::cout << std::endl;
}

/**
* String type overload
*/

template <typename T> // string
auto print_ip(const T& s)
-> std::enable_if_t<std::is_same_v<::std::string, T>>
{
	std::cout << s << std::endl;
}

//from namespace fake_std17
template<class...> struct conjunction : std::true_type { };
template<class B1> struct conjunction<B1> : B1 { };
template<class B1, class... Bn>
struct conjunction<B1, Bn...>
	: std::conditional_t<bool(B1::value), conjunction<Bn...>, B1> {};

// from namespace sfinae
template<typename Expected, typename... Actual>
using AreTypesSame = typename std::enable_if_t<conjunction<std::is_same<Actual, Expected>...>::value>;

template<typename T, typename... Args, typename = AreTypesSame<T, Args...>>
void print_ip(const std::tuple<T, Args...>& t) {
	//print_tuple_impl(ip, std::index_sequence_for<T, Args...>{}, ".");
	std::cout << "tuple overload with sfinae. All argumens have the same type" << std::endl;
}


int main() {
	std::vector<int> v{ 46, 45, 44, 43, 42 };
	std::list<int> l = { 52, 53, 54, 55 };
	std::string s{ "trololo" };

	std::tuple<int, int, int, int, int> t{ 255, 254, 253, 252, 251 };

	std::cout << "char(-1) as ";
	print_ip(char(-1));
	std::cout << "short(0) as ";
	print_ip(short(0));
	std::cout << "int(2130706433) as ";
	print_ip(int(2130706433));
	std::cout << "uint64_t(8875824491850138409) as ";
	print_ip(uint64_t(8875824491850138409));
	std::cout << "string as ";
	print_ip(s);
	std::cout << "vector as ";
	print_ip(v);
	std::cout << "list as ";
	print_ip(l);
	std::cout << "tuple of the elements of the same type ";
	print_ip(t);
}