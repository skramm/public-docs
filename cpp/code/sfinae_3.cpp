
//#include "common.hpp"

template<typename T>
typename std::enable_if<
	( std::is_same<T, int>::value || std::is_same<T, char>::value ), T
	>::type
myFunc(T data)
{
	std::cout << "myFunc() data=" << data << "\n";
	return data+1;
}

int main()
{
    std::cout << myFunc( 42 );  // ok, affiche 43
    std::cout << myFunc( 'a' );  // ok, affiche 'b'
//    std::cout << myFunc( 3.14 );  // Erreur !
}
