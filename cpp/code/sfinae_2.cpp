
//#include "common.hpp"

template<typename T>
typename std::enable_if<
	std::is_same<T, int>::value, T
	>::type
myFunc( T data )
{
	return data+1;
}


int main()
{
	std::cout << myFunc( 42 );  // ok, affiche 43
//	std::cout << myFunc( 'a' );  // Erreur !
//	std::cout << myFunc( 3.14 );  // Erreur !
}
