template<typename T>
struct DataType
{
    T t1;
};

struct A
{
    int value;
};

struct B
{
    float value;
};

// traits class for AB
template<typename T>
struct TraitsAB
{
    static const bool is_A = false;
    static const bool is_B = false;
};


template<>
struct TraitsAB<A>
{
    static const bool is_A = true;
    static const bool is_B = false;
};

template<>
struct TraitsAB<B>
{
    static const bool is_A = false;
    static const bool is_B = true;
};


template<typename T>
void bar
(
	T a,
	typename std::enable_if<std::is_same<T, B>::value, B>::type* = nullptr
)
{
	std::cout << "bar B\n";
}

template<typename T>
void bar
(
	T a,
	typename std::enable_if<TraitsAB<T>::is_A, A>::type* = nullptr
)
{
	std::cout << "bar A\n";
}


/// What we want to do
int main()
{
    DataType<A> dta;
    DataType<B> dtb;
	A a;
	B b;

	bar(b );
    bar( a );
}



