#include<iostream>
using namespace std;

int main()
{
	int i,j;
	for (i = 2; i <= 100; i++)
	{
		for (j = 2; j <= i;j++)
		{
			if (i%j == 0)//能整除则不是素数
			{
				break;	
			}	
		}
		if (j > i / 2)
		{
			cout << i << " ";
		}			
	}
	system("pause");
	return 0;


}