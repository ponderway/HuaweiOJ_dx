// 字符串最后一个单词的长度
#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s;
	getline(cin, s);

	int len = s.length();
	int i = len - 1;
	int N = 0; // 最后一个单词长度
	while (i >= 0 && s[i] != ' ')
	{
		--i;
		++N;
	}
	cout << N << endl;
}