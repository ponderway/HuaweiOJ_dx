#include <iostream>
#include <string>
#include <math.h>
using namespace std;

const double Exp = 1e-6;
double number[4];
string expr[4];
int cnt = 0;
int flag = false;

void Find(int n)
{
	if (n == 1)
	{
		if (fabs(number[0] - 24) <= Exp)
		{
			++cnt;
			flag = true;
			cout << expr[0] << endl;
		}
		else
		{
			//
		}
		return;
	}

	for (int i = 0; i < n; ++i)
	for (int j = i + 1; j < n; ++j)
	{
		double a, b;
		string expa, expb;
		a = number[i];
		b = number[j];
		number[j] = number[n - 1];
		expa = expr[i];
		expb = expr[j];
		expr[j] = expr[n - 1];

		number[i] = a + b;
		expr[i] = '(' + expa + '+' + expb + ')';
		Find(n - 1);

		number[i] = a - b;
		expr[i] = '(' + expa + '-' + expb + ')';
		Find(n - 1);

		number[i] = b - a;
		expr[i] = '(' + expb + '-' + expa + ')';
		Find(n - 1);

		number[i] = a * b;
		expr[i] = '(' + expa + '*' + expb + ')';
		Find(n - 1);

		if (b != 0)
		{
			number[i] = a / b;
			expr[i] = '(' + expa + '/' + expb + ')';
			Find(n - 1);
		}

		if (a != 0)
		{
			number[i] = b / a;
			expr[i] = '(' + expb + '/' + expa + ')';
			Find(n - 1);
		}

		number[i] = a;
		number[j] = b;
		expr[i] = expa;
		expr[j] = expb;
	}
}

bool game24(int a, int b, int c, int d)
{
	number[0] = a;
	number[1] = b;
	number[2] = c;
	number[3] = d;

	char ch[20];
	
	for (int i = 0; i < 4; ++i)
	{
		_itoa_s(number[i], ch, 10, 10);
		expr[i] = ch;

		cout << expr[i] << endl;
	}
	Find(4);
	return 1;
}

int main()
{
	bool flag = game24(3, 8, 4, 4);
	//cout << 3 / 7 << endl;
	cout << cnt << endl;
}


// 参考；
// http://blog.csdn.net/luoweifu/article/details/11578457
// http://blog.csdn.net/wangqiulin123456/article/details/8145545