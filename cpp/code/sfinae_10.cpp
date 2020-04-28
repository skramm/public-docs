//-------------------------------------------
/// A type with 2 template parameters
template<typename T1, typename T2>
struct DataType
{
    T1 t1;
    T2 t2;
	using type1 = T1;
};


//-------------------------------------------
/// 2 concrete types
struct A
{
    int value;
};

struct B
{
    float value;
};

//-------------------------------------------
/// tags
struct isA{};
struct isB{};

//-------------------------------------------
/// traits class for AB
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
    using type = isA;
};

template<>
struct TraitsAB<B>
{
    static const bool is_A = false;
    static const bool is_B = true;
    using type = isB;
};



/// A function with 2 template parameters, the second used to trigger SFINAE and having default unused value
template<
	typename T,
    typename std::enable_if<TraitsAB<typename T::type1>::is_A,T>::type* = nullptr
>
void
foo( T t )
{
    std::cout << "foo A\n";
}

/// A function with 2 template parameters, the second used to trigger SFINAE and having default unused value
template<
	typename T,
    typename std::enable_if<TraitsAB<typename T::type1>::is_B,T>::type* = nullptr
>
void
foo( T t )
{
    std::cout << "foo B\n";
}


/// What we want to do
int main()
{

    DataType<A, int>   dta;
    DataType<B, float> dtb;


    foo( dta );
    foo( dtb );

}



