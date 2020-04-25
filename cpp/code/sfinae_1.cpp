

//#include "common.hpp"

// un type
struct Int
{
	int val;
	Int( int a ): val(a) {}
	using value_type = int;
};

int
negate( int i )
{
	std::cout << "i=" << i << "\n";
	return 2*i;
}

/*template <typename T>
typename T::value_type
negate(const T& t)
{
	return 2*t;
}*/

int main()
{
	int a=42;
	std::cout << negate(a) << "\n";
//	Int b=42;
//	std::cout << negate(b) << "\n";
}

