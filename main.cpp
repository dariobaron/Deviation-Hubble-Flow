#include <iostream>
#include <vector>

using namespace std;

struct Base{
	struct ParamsType{};
	static constexpr unsigned n_params = 0;
	Base() {};
	Base(ParamsType ) {};
	virtual unsigned getNparams() const {
		return n_params;
	}
	virtual ParamsType getParams() const {
		return ParamsType();
	}
	virtual void print() {
		cout << "Nparams=" << n_params << " with type " << typeid(ParamsType).name() << endl;
	}
	virtual void printAddresses() {
		cout << "*this at " << this << endl;
	}
};

struct DerivedA : Base{
	struct ParamsType{
		double x;
		ParamsType(double * ptr) : x(*ptr) {};
	};
	static constexpr unsigned n_params = 1;
	double x;
	DerivedA() : x(0) {};
	DerivedA(double x) : x(x) {};
	DerivedA(ParamsType params) : x(params.x) {};
	unsigned getNparams() const {
		return n_params;
	}
//	ParamsType getParams() const {
//		return ParamsType();
//	}
	void print() {
		cout << "Nparams=" << n_params << " with type " << typeid(ParamsType).name() << " and x=" << x << endl;
	}
	void printAddresses() {
		cout << "*this at " << this << "\tx at " << &x << endl;
	}
};

struct DerivedB : Base{
	struct ParamsType{
		double x, y;
		ParamsType(double * ptr) : x(*ptr), y(*(ptr+1)) {};
	};
	static constexpr unsigned n_params = 2;
	double x, y;
	DerivedB() : x(0), y(0) {};
	DerivedB(double x, double y) : x(x), y(y) {};
	DerivedB(ParamsType params) : x(params.x), y(params.y) {};
	unsigned getNparams() const {
		return n_params;
	}
//	ParamsType getParams() const {
//		return ParamsType();
//	}
	void print() {
		cout << "Nparams=" << n_params << " with type " << typeid(ParamsType).name() << " and x=" << x << ",y=" << y << endl;
	}
	void printAddresses() {
		cout << "*this at " << this << "\tx at " << &x << "\ty at " << &y << endl;
	}
};

int main() {

cout << endl;

std::vector<double> params = {1, 2, 3, 4};

double * ptr = params.data();
Base::ParamsType * ptr_base = reinterpret_cast<Base::ParamsType*>(ptr);
//ptr += Base::n_params;
ptr = reinterpret_cast<double*>(&ptr_base[1]);
DerivedA::ParamsType * ptr_A = reinterpret_cast<DerivedA::ParamsType*>(ptr);
//ptr += DerivedA::n_params;
ptr = reinterpret_cast<double*>(&ptr_A[1]);
DerivedB::ParamsType * ptr_B = reinterpret_cast<DerivedB::ParamsType*>(ptr);

cout << "Addresses:\t" << params.data() << "\t" << ptr_base << "\t" << ptr_A << "\t" << ptr_B << endl;
cout << "Contents:\t" << *params.data() << "\t" << *reinterpret_cast<double*>(ptr_base) << "\t" << *reinterpret_cast<double*>(ptr_A) << "\t" << *reinterpret_cast<double*>(ptr_B) << endl;
cout << "Sizes of ParamsType:\t" << sizeof(Base::ParamsType) << "\t" << sizeof(DerivedA::ParamsType) << "\t" << sizeof(DerivedB::ParamsType) << endl;
cout << "Sizes of Type:\t" << sizeof(Base) << "\t" << sizeof(DerivedA) << "\t" << sizeof(DerivedB) << endl;

Base a(*ptr_base);
DerivedA b(*ptr_A);
DerivedB c(*ptr_B);

cout << endl;
a.print();
b.print();
c.print();

cout << endl;
a.printAddresses();
b.printAddresses();
c.printAddresses();

cout << endl;
cout << "The size of DerivedA is " << sizeof(DerivedA) << endl;
cout << "The size of DerivedA::ParamsType is " << sizeof(DerivedA::ParamsType) << endl;
DerivedA trial[3];
for (unsigned i = 0; i < 3; ++i) {
	trial[i].printAddresses();
}

cout << "\n--------------------------------\n" << endl;

std::vector<Base*> objects;
DerivedA a1(5);
objects.push_back(&a1);
DerivedB b1(6, 7);
objects.push_back(&b1);

for (auto & obj : objects) {
	cout << obj->getNparams() << endl;
	obj->print();
	obj->printAddresses();
}

cout << endl;

return 0;
}