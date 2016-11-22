#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__

#include "BigInt.h"
#include <stack>
#include <cstring>
using namespace std;

class Calculator
{
private:
	char *expression;
	enum token { OPAREN, ADD, SUB, MULTI, DIV, EXP, CPAREN, VALUE, EOL };
private:
	void binary_op(token op, stack<CBigInt> &data_stack);
	token get_op(CBigInt &value);

public:
	Calculator(char *s)
		{ expression = new char[strlen(s) + 1]; strcpy(expression, s); }
	~Calculator() { delete expression; }

	CBigInt result();
};

#endif // __CALCULATOR_H__
