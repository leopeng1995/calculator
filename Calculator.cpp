#include "Calculator.h"
#include "BigInt.h"
#include <iostream>

CBigInt Calculator::result()
{
	token last_op, top_op;
	CBigInt result_value, current_value;
	stack<token> op_stack;
	stack<CBigInt> data_stack;
	char *str = expression;

	while (true)
	{
		last_op = get_op(current_value);
		if (last_op == EOL) break;
		
		switch (last_op)
		{
			case VALUE: data_stack.push(current_value); break;
			case CPAREN:
				while (!op_stack.empty() && (top_op = op_stack.top()) != OPAREN)
				{
					binary_op(top_op, data_stack);
					op_stack.pop();
				}
				if (top_op != OPAREN) cerr << "Require OPAREN" << endl;
				break;
			case OPAREN: op_stack.push(OPAREN); break;
			case EXP: op_stack.push(EXP); break;
			case MULTI: case DIV:
				while (!op_stack.empty() && op_stack.top() >= MULTI)
				{
					binary_op(op_stack.top(), data_stack);
					op_stack.pop();
				}
				op_stack.push(last_op);
				break;
			case ADD: case SUB:
				while (!op_stack.empty() && op_stack.top() != OPAREN)
				{
					binary_op(op_stack.top(), data_stack);
					op_stack.pop();
				}
				op_stack.push(last_op);
		}
	}

	while (!op_stack.empty())
	{
		binary_op(op_stack.top(), data_stack);
		op_stack.pop();
	}
	if (data_stack.empty())
	{
		cout << "No Result" << endl;
		return 0;
	}
	result_value = data_stack.top();
	data_stack.pop();
	if (!data_stack.empty())
	{
		cout << "Require Op" << endl;
		return 0;
	}

	expression = str;
	return result_value;
}

void Calculator::binary_op(token op, stack<CBigInt> &data_stack)
{
	CBigInt num1, num2;

	if (data_stack.empty())
	{
		cerr << "Error"; 
	}
	else
	{	
 		num2 = data_stack.top();
		data_stack.pop();
	}
	if (data_stack.empty())
	{
		cerr << "Error";
	}
	else
	{
		num1 = data_stack.top();
		data_stack.pop();
	}

	switch (op)
	{
		case ADD: data_stack.push(num1 + num2); break;
		case SUB: data_stack.push(num1 - num2); break;
		case MULTI: data_stack.push(num1 * num2); break;
		case DIV: data_stack.push(num1 / num2); break;
		case EXP: data_stack.push(num1 ^ num2); break;
	}
}

Calculator::token Calculator::get_op(CBigInt &value)
{
	while (*expression)
	{
		while (*expression && *expression == ' ')
			++expression;
		
		if (*expression >= '0' && *expression <= '9')
		{
			value = 0;
			while (*expression >= '0' && *expression <= '9')
			{
				value = value * 10 + *expression - '0';
				++expression;
			}
			return VALUE;
		}

		switch (*expression)
		{
			case '(': ++expression; return OPAREN;
			case ')': ++expression; return CPAREN;
			case '+': ++expression; return ADD;
			case '-': ++expression; return SUB;
			case '*': ++expression; return MULTI;
			case '/': ++expression; return DIV;
			case '^': ++expression; return EXP;
		}
	}
	return EOL;
}