#include "IPAddressValid.h"
#include<iostream>

bool isSubIpValid(char* pSubIp)
{
	if (pSubIp == NULL)
		return false;

	int len = strlen(pSubIp);
	for (int i = 0; i < len; ++i)
	{
		if (pSubIp[i] < '0' || pSubIp[i] > '9')
			return false;
	}

	if (len > 3)
		return false;

	if (len > 1 && pSubIp[0] == '0')
		return false;

	int a = atoi(pSubIp);
	if (a > 255)
		return false;

	return true;
}

bool isIPAddressValid(const char* pszIPAddr)
{
	if (pszIPAddr == NULL)
		return false;

	int len = strlen(pszIPAddr);
	int start = 0, end = 0;
	

	while (pszIPAddr[start] == ' ')
		++start;

	while (pszIPAddr[end] == ' ')
		--end;
/*
	for (int i = 0; i < len; ++i)
	{
		if (pszIPAddr[i] != ' ')
		{
			start = i;
			break;
		}
	}
	
	for (int i = len - 1; i >= 0; --i)
	{
		if (pszIPAddr[i] != ' ')
		{
			end = i;
			break;
		}
	}
*/
	int len2 = end - start + 1;
	char pTempIp[100];
	strncpy(pTempIp, pszIPAddr + start, len2);
	pTempIp[len2] = '\0';

	int pointNum = 0;
	for (int i = 0; i < len2; ++i)
	{
		if (pTempIp[i] == '.')
			++pointNum;
	}

	if (pointNum != 3)
		return false;

	char* pSubIp = NULL;
	int subNum = 0;
	pSubIp = strtok(pTempIp, ".");
	while (pSubIp != NULL)
	{
		++subNum;
		if (!isSubIpValid(pSubIp))
			return false;
		pSubIp = strtok(NULL, ".");
	}

	if (subNum == 4)
		return true;
	else
		return false;
}