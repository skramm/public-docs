
// https://stackoverflow.com/a/12045843/193789
#include <type_traits>
#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <list>

template <typename Container>
struct is_container : std::false_type { };

template <typename... Ts> struct is_container<std::array<Ts... >> : std::true_type { };
template <typename... Ts> struct is_container<std::vector<Ts...>> : std::true_type { };
template <typename... Ts> struct is_container<std::set<Ts...   >> : std::true_type { };
template <typename... Ts> struct is_container<std::list<Ts...  >> : std::true_type { };

int main()
{
	std::cout << "vector:" << is_container<std::vector<int>>::value << '\n';
	std::cout << "array: " << is_container<std::array<int,5>>::value << '\n';
	std::cout << "set: "   << is_container<std::set<int>>::value << '\n';
	std::cout << "list: "  << is_container<std::list<int>>::value << '\n';
}
/*
I am looking for a way to SFINAE some function, that must be available only to some containers:
vector, list, array (set is there below only as a test)

Build upon this anwer, I tried the code below that uses a traits class that returns true only for the required containers.

As you can see online here, it fails for std::array.
What I understand is that this is due to the fact that std::array require a second template parameter.
I have a low experience with variadic templates, so my question is:

Is there a way to make this approach sucessful?




*/
