#include <iostream>
#include "sparse.h"
using namespace std;


int main(){
	sparse a(3,3);
	a.put(1,1,4);
	a.put(1,2,4);
	a.put(1,3,4);
	a.put(2,1,4);
	a.put(2,2,4);
	a.put(2,3,4);
	a.put(3,1,4);
	a.put(3,2,4);
	a.put(3,3,4);
	a.print();
	//a.resize(2,4);
	a.print();
	//cout<<a.is_zero(2,4)<<endl;
	cout<<a.is_zero(1,2)<<endl;
	//a.make_zero(1,2);
	cout<<a.is_zero(1,2)<<endl;
	cout<<a.get(1,2)<<endl;
	cout<<a.get(1,3)<<endl;

	sparse b(3,3);
	b.put(1,1,4);
	b.put(1,2,4);
	b.put(1,3,4);
	b.put(2,1,4);
	b.put(2,2,4);
	b.put(2,3,4);
	b.put(3,1,4);
	b.put(3,2,4);
	b.put(3,3,4);
	cout<<"/////////////"<<endl;
	sparse c(3,3);
	c=a+b;
	c.print();

	cout<<(a==b)<<endl;
	return 0;
}
