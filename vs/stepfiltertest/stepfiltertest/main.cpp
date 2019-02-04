
#include <vector>
#include <string>
#include <iostream>
#include <memory>

using namespace std;


class C {
public:
	C() {
		cout << "C" << endl;
	}
	~C() {
		cout << "~C" << endl;
	}
};
int main()
{
	string s;
	s = "aaa";

	unique_ptr<C> uc = make_unique<C>();
	shared_ptr<C> sc = make_shared<C>();
	return 0;
}