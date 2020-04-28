template<typename T=int>
T foo()
{
	std::cout << "foo()\n";
	return T() + 1;
}

int main()
{
	std::cout << "main: foo<int>()="  << foo<int>() << "\n";
	std::cout << "main: foo<float>()" << foo<float>() << "\n";
	std::cout << "main: foo<>()"      << foo<>() << "\n";;
}
