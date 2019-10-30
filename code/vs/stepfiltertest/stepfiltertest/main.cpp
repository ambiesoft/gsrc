
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
	C(int i) {
		cout << "C" << i << endl;
	}
	~C() {
		cout << "~C" << endl;
	}
};
int main()
{
	string s;
	s = "aaa";

	vector<int> vi;
	vi.push_back(1);
	vi.emplace_back(2);

	unique_ptr<C> uc = make_unique<C>();
	unique_ptr<C> uci = make_unique<C>(33);
	shared_ptr<C> sc = make_shared<C>();
	return 0;
}