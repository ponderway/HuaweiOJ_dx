#include <stdlib.h>
#include "oj.h"
int PktTrans(char* pInput, int iLen, char* pOutput)
{
	if (pInput == NULL || pOutput == NULL || iLen < 0)
		return -1;

	if (iLen == 0)
		return 0;

	*pOutput++ = 0x7E;
	for (int i = 0; i < iLen; ++i)
	{
		if (pInput[i] == 0x7E)
		{
			*pOutput++ = 0x7D;
			*pOutput++ = 0x5E;
		}
		else if (pInput[i] == 0x7D)
		{
			*pOutput++ = 0x7D;
			*pOutput++ = 0x5D;
		}
		else
			*pOutput++ = pInput[i];
	}
	*pOutput++ = 0x7E;
	*pOutput = '\0';

	return 0;
}