
/************************************************************************/
/*  GetExtFibonacci                                                         */
/*  输入扩展Fibonacci数列的前2个数字first和second，要得到的数字的序列号num  */
/*  输入：扩展Fibonacci数列对应的序号的数字                                 */
/************************************************************************/
int GetExtFibonacci(int first, int second, int num)
{
	if (num <= 0)
		return 1;

	if (num == 1)
		return first;
	if (num == 2)
		return second;

	while (num - 2 > 0)
	{
		int temp = second;
		second = first + second;
		first = temp;
		--num;
	}
	return second;
}

/************************************************************************/
/*  CalcTotalValueOfExtFibonacci                                        */
/*  输入扩展Fibonacci数列的前2个数字first和second，和数字的序列号num    */
/*  输出：扩展Fibonacci数列对应的序号的数列之前（包括这个数列本身）的所有的数列之和         */
/************************************************************************/
int CalcTotalValueOfExtFibonacci(int first, int second, int num)
{
	if (num <= 0)
		return 1;

	if (num == 1)
		return first;
	if (num == 2)
		return first + second;

	int sum = first + second;
	while (num - 2 > 0)
	{
		int temp = second;
		second = first + second;
		first = temp;
		--num;
		sum += second;
	}
	return sum;
}

