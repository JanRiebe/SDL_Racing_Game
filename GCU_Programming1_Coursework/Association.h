#pragma once

#include <map>

//A map that allows looking up elements in both directions. Each element is associated with a single other element.
template <class A, class B>
class Association
{

private:
	std::map<A, B> ab;
	std::map<B, A> ba;

public:
	Association();

	//Associates a with b and b with a. Will overwrite any previous associations either element has.
	void add(A a, B b);

	//Removes the association containing a.
	void remove(A a);

	//Removes the association containing b.
	void remove(B b);
	
	//Access elements via the [] operator
	A operator[](B b);
	B operator[](A a);
	
	//Returns whether an association has been made for the element
	bool contains(A a);
	
	//Returns whether an association has been made for the element
	bool contains(B b);

};










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
	if(ba.count(b)>0)
		return ba[b];
	else
		return nullptr;
}

template<class A, class B>
B Association<A, B>::operator[](A a)
{
	if (ab.count(a)>0)
		return ab[a];
	else
		return nullptr;
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
