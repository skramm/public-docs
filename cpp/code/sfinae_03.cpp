struct A            // un type quelconque
{
    int val;
    A() { val=42; }
	void doSomething() { val++; }
};

//=========================
void foo( A& a )  //
{
    std::cout << "foo( A& )\n";
    a.doSomething();
}
void foo( const A& a )
{
    std::cout << "foo( const A& )\n";
}

//=========================
template<typename T>
void bar( T& a )
{
    std::cout << "bar, is_const=" << std::is_const<T>::value << "\n";
	foo(a);
}
//=========================
int main()
{
    A a1;
    const A a2;
    bar(a1);
    bar(a2);
}
