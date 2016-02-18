// 有测试用例未通过，未找到原因
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
using namespace std;

map<string, vector<string>> myDictionary;

string GetKey(string str)
{
	string key = str;
	sort(key.begin(), key.end());
	return key;
}

int AddOneWord(char* Word)
{
	if (Word == NULL || *Word == '\0')
		return -1;
	string key = GetKey(Word);
	if (myDictionary.count(key))
	{
		vector<string> brotherWords = myDictionary[key];
		for (int i = 0; i < brotherWords.size(); ++i)
		{
			if (brotherWords[i] == Word)
				return -1;	
		}
		// 如此写浪费时间和空间
		brotherWords.push_back(Word);
		sort(brotherWords.begin(), brotherWords.end());
		myDictionary[key] = brotherWords;
	}
	else
	{
		vector<string> brotherWords;
		brotherWords.push_back(Word);
		myDictionary[key] = brotherWords;
	}

	return 0;
}

int FindSimilarWordNum(char* Word)
{
	if (Word == NULL)
		return 0;

	string key = GetKey(Word);
	if (myDictionary.count(key))
	{
		vector<string>	brotherWords = myDictionary[key];
		for (int i = 0; i < brotherWords.size(); ++i)
		{
			if (brotherWords[i] == Word)
				return myDictionary[key].size() - 1;
		}
		return myDictionary[key].size();
	}
	return 0;
}

int FindOneSimilarWord(char* Word, int Seq, char* SimilarWord)
{
	if (Word == NULL || Seq < 1)
	{
		*SimilarWord = '\0';
		return -1;
	}
	string key = GetKey(Word);
	if (!myDictionary.count(key))
	{
		*SimilarWord = '\0';
		return -1;
	}

	vector<string>	brotherWords = myDictionary[key];
	int pos = -1;
	for (int i = 0; i < brotherWords.size(); ++i)
	{
		if (brotherWords[i] == Word)
		{
			pos = i;
			break;
		}	
	}

	if (pos == -1 || pos + Seq >= brotherWords.size())
	{
		*SimilarWord = '\0';
		return -1;
	}

	string temp = brotherWords[pos + Seq];
	strncpy(SimilarWord, temp.c_str(), temp.length());
	SimilarWord[temp.length()] = '\0';
	return 0;
}

void ClearAllWords(void)
{
	map<string, vector<string>>::iterator ip;
	for (ip = myDictionary.begin(); ip != myDictionary.end(); ++ip)
	{
		ip->second.clear();
	}
	myDictionary.clear();
}

char *Test_Word[7] = {
	"mock",
	"aabc",
	"abc",
	"ckom",
	"bcaa",
	"abca", };

int main()
{
	AddOneWord(Test_Word[0]);
	AddOneWord(Test_Word[1]);
	AddOneWord(Test_Word[2]);
	AddOneWord(Test_Word[3]);
	AddOneWord(Test_Word[4]);
	AddOneWord(Test_Word[5]);

	int Expectnumber = 1;
	int ActualNumber;
	int Ret;

	ActualNumber = FindSimilarWordNum(Test_Word[0]);
	cout << ActualNumber << endl;

	char SimilarWord[51] = { '\0' };
	int Seq = 2;
	 Ret = FindOneSimilarWord(Test_Word[1], Seq, SimilarWord);
	cout << SimilarWord << endl;

	ClearAllWords();
	cout << endl;
}