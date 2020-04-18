#include "stdafx.h"
#include "funtions.h"
#include <math.h>
#include <iostream>

using namespace std;

/*************************************************
//功能：确定2-n范围内的所有质数，并打印至状态栏
*************************************************/
void pickPrime(int maxVal)
{
	
	cout << "pick out prime by trial division algorithm "<< endl <<endl;
	//筛选2-n范围内的质数
	int sum = 0;
	for (int i = 2; i <= maxVal; i++) {
		if (isPrime(i)) {
			//cout << i <<" ";
			sum++;
			//每20个换行
			//if(sum%20==0) cout << endl;
		}
	}

	cout << endl <<"the sum of prime is "<< sum << endl << endl;
}


/*************************************************
试除法检查质数
假设有自然数x，如需要确定x是否为质数，只需确定x能否被2到√x范围内的奇数整除
*************************************************/
bool isPrime(int x)
{
	//1及负数不为质数
	if (x < 2)return false;
	//2为最小质数
	if (x == 2)return true;
	//偶数必不为质数
	if (x%2 == 0)return false;

	//确定是否能被2到到√x范围内的奇数整除
	int sqrt_x = sqrt(x);
	for (int i = 3; i <= sqrt_x; i+=2) {
		if (x%i == 0)return false;
	}
	
	return true;
}

void EratosSieve(int maxVal)
{
	cout << "pick out prime by Eratosthenes's algorithm " << endl << endl;

	bool * flag = new bool[maxVal+1];
	memset(flag, true, sizeof(bool)*(maxVal+1));

	flag[0] = false;
	flag[1] = false;

	int sum = 0;
	for (int i = 2; i <= maxVal; ++i) {
		if (flag[i]) {
			//如果第i号为质数
			//cout << i << " ";
			sum++;
			//每20个换行
			//if (sum % 20 == 0) cout << endl;
			for (long long j = i*i; j <= maxVal; j += i) {
			    flag[j] = false;
			}
		} 
	}

	delete[] flag;

	cout << endl << "the sum of prime is " << sum << endl << endl;
}

