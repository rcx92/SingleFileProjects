#include <cstdio>

class Foo{
public:
	virtual void vPrint(){
		printf("v hello world\n");
	}
	void nvPrint(){
		printf("nv hello world\n");
	}
};

class SubFoo : public Foo{
public:
	virtual void vPrint(){
		printf("Sub v hello world\n");
	}
	void nvPrint(){
		printf("Sub nv hello world\n");
	}
};


int main(){
	Foo *f = NULL;
	SubFoo *sf = NULL;
	f->nvPrint();
	sf->nvPrint();
	f->vPrint();
	sf->nvPrint();

	getchar();
}