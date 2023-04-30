#include<iostream>
#include <string>

class box {
	public:
	int volume();//function declaration
	int h;
	int w;
	int l;
};

int box :: volume(){
	int v;
	v= h*w*l;
}

int main(){
box big;
big.h=10;
big.w=10;
big.l=10;

int V = big.volume();

	std::cout <<V;
    return 0;
}
