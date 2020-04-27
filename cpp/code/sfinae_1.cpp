
// un type
struct Int
{
	int val;
	Int( int a ): val(a) {}
	using value_type = int;
};

void
foo( int i )
{
	std::cout << "foo(int)\n";
}

template <typename T>
void
foo(const T& t)
{
	typename T::value_type vt;
	std::cout << "foo(T)\n";
}

int main()
{
	int a=42;
	foo( a );

	Int b=42;
	foo( b );
}

