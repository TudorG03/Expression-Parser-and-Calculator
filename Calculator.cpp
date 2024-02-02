#include "Calculator.h"
#include "Parser.h"
#include "Stack.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

Calculator::Calculator()
{
	expression = "";
	result = 0.0f;
	validExpression = false;
}

Calculator::Calculator(string expression)
{
	validExpression = true;
	this->expression = expression;
	Parser aux(this->expression);
	p = aux;
	result = setResult();
}

double Calculator::setResult() // construiesc rezultatul pe baza expresiei postfixate primite
{
	string postfix = p.getPostfix();
	if (!p)
	{
		try
		{
			Lexer l(postfix);
			int s = 0;
			for (int i = 0; i < l.size; i++)
				if ((int)l[i] == -1)
					s++;
			Stack stack(s);
			for (int i = 0; i < l.size; i++)
			{
				if ((string)l[i] == "NUM")
					stack += l.tokens[i].getValue();
				else
				{
					double b = --stack;
					double a = --stack;
					double c = calculate(a, b, l.tokens[i].getType()[0]);
					stack.push(c);
				}
			}
			double res;
			if (!stack.isEmpty())
				res = --stack;
			else
				throw invalid_argument("Unable to calculate!");
			return res;
		}
		catch (const invalid_argument& e)
		{
			cerr << e.what() << endl;
		}
	}
	validExpression = false;
	return 0;
}

double Calculator::getResult()
{
	return result;
}

void Calculator::setExpression(string expr)
{
	Calculator aux(expr);
	*this = aux;
}

string Calculator::getExpression()
{
	return expression;
}

bool Calculator::getValidExpression()
{
	return validExpression;
}

double Calculator::calculate(double a, double b, char op) // in functie de caracterul din op efectuez operatia potrivita
{
	double res = 0.0;
	switch (op)
	{
	case '+':
		res = a + b;
		break;
	case '-':
		res = a - b;
		break;
	case '*':
	{
		res = a * b;
		if (res == -0)
			res = 0;
		break;
	}
	case '/':
	{
		if (fabs(b - 0.0) < 0.01)
		{
			Parser::parserCount--;
			validExpression = false;
			throw invalid_argument("Division by 0 is prohibited!");
		}
		res = a / b;
		break;
	}
	case '^':
		res = pow(a, b);
		break;
	case '#':
	{
		int n = (int)b;
		if (n <= 0)
		{
			Parser::parserCount--;
			validExpression = false;
			throw invalid_argument("Negative or 0 root is prohibited!");
		}
		if (n % 2 == 0 && a < 0.0)
		{
			Parser::parserCount--;
			validExpression = false;
			throw invalid_argument("Negative number is prohibited with even root order!");
		}
		res = pow(a, 1.0 / n);
		break;
	}
	default:
		Parser::parserCount--;
		cout << "Invalid operation!\n";
		break;
	}
	return res;
}

string Calculator::removeTraillingZeros(double result) // elimin zero-urile de la capatul numerelor cu zecimale
{
	string aux = to_string(result);
	int traillingZeros;
	for (traillingZeros = aux.length() - 1; traillingZeros >= 0 && aux[traillingZeros] == '0'; traillingZeros--);
	return aux.substr(0, traillingZeros + 1);
}

//supraincarc operatorii < si > pentru a compara rezultatul calcului cu rezultatul din alt obiect sau un numar de tip double

bool Calculator::operator<(Calculator c)
{
	return result < c.result;
}

bool Calculator::operator>(Calculator c)
{
	return result > c.result;
}

bool Calculator::operator<(double num)
{
	return result < num;
}

bool Calculator::operator>(double num)
{
	return result > num;
}

void Calculator::operator()() // functia permite calcule consecutive pana la introducerea cuvantului exit
{
	Calculator c;
	string ans, aux;
	do
	{
		aux = "";
		cout << "Enter an expression to calculate: ";
		getline(cin, ans);
		for (int i = 0; i < ans.length(); aux += tolower(ans[i]), i++);
		ans = aux;
		if (ans != "exit")
		{
			c.setExpression(ans);
			cout << c;
		}
	} while (ans != "exit");
	cout << "\nYou've made " << Parser::parserCount << " calculations!\n";
}

ostream& operator<<(ostream& out, Calculator c)
{
	out << c.getExpression() << " = ";
	double res = c.getResult();
	if (c.getValidExpression())
	{
		if (res != (int)res)
		{
			out << c.removeTraillingZeros(res) << "\n\n";
		}
		else
		{
			out << res << "\n\n";
		}
	}
	else
		out << "Unable to calculate!\n\n";
	return out;
}

istream& operator>>(istream& in, Calculator& c)
{
	string expr;
	cout << "Enter an expression to calculate: ";
	getline(in, expr);
	Calculator aux(expr);
	c = aux;
	return in;
}


