
#include <stdlib.h>

#include <iostream>
using namespace std;


unsigned int strlenth(char *s)  /* 获取字符串长度 */
{
	if (s == NULL)
		return 0;

	unsigned int lenth = 0;
	while (*s++ != '\0')
		++lenth;

	return lenth;
}

void strcopy(char **target, char *source)  /* 字符串拷贝 */
{
	if (source == NULL)
		return;

	int len = strlenth(source);
	char *temp = new char[len + 1];
	*target = temp;
	while (*source != '\0')
		*temp++ = *source++;
	*temp = '\0';
}

int strcompare(char *s, char *t)  /* 字符串比较，s>t，则返回1；s=t，则返回0；s<t，则返回-1 */
{
	if (s == NULL && t == NULL)
		return 0;
	if (s == NULL && t != NULL)
		return -1;
	if (s != NULL && t == NULL)
		return 1;

	while (*s != '\0' && *t != '\0')
	{
		if (*s > *t)
			return 1;
		if (*s < *t)
			return -1;
		++s;
		++t;
	}

	if (*s != '\0')
		return 1;
	if (*t != '\0')
		return -1;
	return 0;
}

void strcombine(char **x, char *s, char *t)  /* 字符串连接，将字符串t接到s后面，x为连接后的新串 */
{
	int len1 = strlenth(s);
	int len2 = strlenth(t);
	int len = len1 + len2;
	char *temp = new char[len + 1];
	*x = temp;

	while (s != NULL && *s != '\0')
		*temp++ = *s++;
	while (t != NULL && *t != '\0')
		*temp++ = *t++;
	*temp = '\0';
}

/* 字符串截取，从第index个字符开始，截取lenth长度的字符串，并输出到字符串t */
void strcatch(char *s, unsigned int index, unsigned int lenth, char **t)
{
	int s_len = strlenth(s);
	if (index + lenth > s_len || index > s_len || lenth == 0)
		return;

	char *temp = new char[lenth + 1];
	*t = temp;
	for (int i = 0; i < lenth; ++i)
		temp[i] = s[i + index];
	temp[lenth] = '\0';
}

bool strsubstr(char *s, char *sub)  /* 字符串子串查找，如果子串sub在s中存在，则返回1，否则返回0 */
{
	if (s == NULL || sub == NULL)
		return false;
	int len1 = strlenth(s);
	int len2 = strlenth(sub);
	if (!len1 && !len2)
		return true;

	for (int i = 0; i <= len1 - len2; ++i)
	{
		char *temp;
		strcatch(s, i, len2, &temp);
		if (strcompare(sub, temp) == 0)
			return true;
	}

	return false;
}