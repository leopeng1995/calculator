#include "Calculator.h"
#include <stack>
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	CBigInt value = 9;
	CBigInt n = 81;
	CBigInt r = value ^ n;

	r /= 100000000;
	r /= 3600;
	r /= 24;
	r /= 365;
	std::string rrr;
	r.PutToString(rrr, 10);
	std::cout << rrr << std::endl;

	value.GetFromString("6670903752021072936960", 10);
	n.GetFromString("6000000000", 10);

	r = value / n;
	r.PutToString(rrr, 10);
	std::cout << rrr << std::endl;

    char s[10] = "3*6/2+5";
	Calculator expr(s);
	CBigInt result = expr.result();
	result.PutToString(rrr, 10);
	cout << rrr << endl;

	return 0;
}
