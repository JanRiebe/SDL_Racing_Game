#include "Association.h"



template<class A, class B>
Association<A, B>::Association()
{
}

template<class A, class B>
void Association<A, B>::add(A a, B b)
{
	ab[a] = b;
	ba[b] = a;
}



template<class A, class B>
void Association<A, B>::remove(A a)
{
	ba.erase(ab[a]);
	ab.erase(a);
}



template<class A, class B>
void Association<A, B>::remove(B b)
{
	ab.erase(ba[b]);
	ba.erase(b);
}

template<class A, class B>
A Association<A, B>::operator[](B b)
{
	return ba[b];
}

template<class A, class B>
B Association<A, B>::operator[](A a)
{
	return ab[a];
}

template<class A, class B>
bool Association<A, B>::contains(A a)
{
	return ab.count(a) > 0;
}

template<class A, class B>
bool Association<A, B>::contains(B b)
{
	return ba.count(b) > 0;
}
