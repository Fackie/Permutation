#include<iostream>
using namespace std;
class permutation
{
	/*
	author:		fengchen
	time:		2017.4.13
	function:	generating permutation by 4 different algorithm

	USING EXAMPLE:
	/permutation p(9);
	/p.setnum(297191);
	/p.getupid();
	/p.uphex();
	you will get upid = 72642321
	and uphex permutation = 794635821
	*/

private:
	long len;
	long number;
	long nownum;
	int* downid;
	int* upid;
	int* dictid;
	int* up(long num , int n);
	int* down(long num , int n);
	int scanmin(int* p);
	int scanmax(int* p , int n);

public:
	permutation();//input to initialize
	permutation(int n);//direct initialize
	int* converse(int* p , int n);//converse p[n~end]
	int* swap(int* p ,int i, int j);//swap the position of p[i] and p[j]
	long factorial(int n);//get factorial number of n
	void setnum();
	void setnum(long n);//which one of permutation you want to get
	void getupid();// generate uphex number
	void getdownid();// generate downhex number
	//four different permutation algorithm
	void uphex();
	void downhex();
	void dict();
	void sjt();
	//caution: before using dict() and uphex() you need to run getupid();
	//		   same with downhex() and sjt() you need to run getdownid();
};
permutation::permutation()
{
	int n;
	cout<<"Please input permutation num: ";
	cin>>n;
	len = n;
	number = factorial(n);
	cout<<"Total permutation num is: "<<number<<endl;
}
permutation::permutation(int n)
{
	len = n;
	number = factorial(n);
	cout<<"Total permutation num is: "<<number<<endl;
}
int* permutation::down(long num , int n)
{
	int* result = new int[n];
	for(int i = 0 ; i < n ; i++)
	{
		result[n - i - 1] = (num % (n - i));
		num = num / (n - i);
	}
	return result;
}
int* permutation::up(long num , int n)
{
	int big = 0;
	for(int i = 1 ; i < n+1 ; i++)
	{
		if(num>=factorial(i)&&num<factorial(i+1))
		{
			big = i;
		}
	}	
	int* result = new int[n];
	for(int j = 0 ; j < big ; j++)
	{
		result[big - j - 1] = (num / factorial(big - j));
		num = num % factorial(big - j);
	}
	for(int j = big ; j < n ; j++)
		result[j] = 0;
	return result;
}
int permutation::scanmin(int* p)
{
	for(int i = 1; i < len ; i++)
	{
		if(p[len - i - 1] < p[len - i])
			return (len - i - 1);
	}
}
int permutation::scanmax(int* p , int n)
{
	for(int i = len - 1; i > n ; i--)
	{
		if(p[i] > p[n])
			return i;
	}
}
int* permutation::converse(int* p , int n)
{
	int* temp = new int[len];
	for(int i = 0; i < len ; i++)
		temp[i] = p[i];
	for(int i = n + 1; i < len ; i++)
	{
		temp[i] = p[len - i + n];
	}
	return temp;

}
int* permutation::swap(int* p ,int i, int j)
{
	int* temp = new int[len];
	for(int k = 0; k < len ; k++)
		temp[k] = p[k];
	temp[i] = p[j];
	temp[j] = p[i];
	return temp;
}
long permutation::factorial(int n)
{
	int number = 1;
	for(int i = 1 ; i < n+1 ; i++)
	{
		number *= i;
	}
	return number;
}
void permutation::setnum()
{
	cout<<"Please set the id of permutation number you want: ";
	cin>>nownum;
}
void permutation::setnum(long n)
{
	cout<<"You already set the id of permutation number as: "<<n;
	nownum = n;
}
void permutation::getupid()
{
	upid = up(nownum,len);
	cout<<"The uphex number of "<<nownum<<" is :";
	for(int i = 1 ; i < len ; i++)
		cout<<upid[len - i - 1];
	cout<<endl;
}
void permutation::getdownid()
{
	downid = down(nownum,len);
	cout<<"The downhex number of "<<nownum<<" is :";
	for(int i = 1 ; i < len ; i++)
		cout<<downid[i];
	cout<<endl;
}
void permutation::uphex()
{
	//uphex permutation generation
	int rightsmall;
	int* result = new int[len];
	for(int i = 0 ;i < len ; i++)
		result[i] = 0;
	for(int i = 1 ; i < len ; i++)
	{
		rightsmall = upid[len - i - 1];
		int bigger = 0;
		for(int j = 0 ; j < rightsmall + 1 ; j++)
		{
			if(result[j] > (len - i + 1))
				bigger++;
		}
		for(int j = rightsmall ; j < len ; j++)
		{
			if(result[j + bigger] ==0)
			{
				result[j + bigger] = len - i + 1;
				break;
			}
		}
	}
	for(int i = 0 ;i < len ; i++)
	{
		if(result[i] == 0)
			result[i] = 1;
	}
	cout<<"The uphex permutation of "<<nownum<<" is:";
	for(int i = 0 ; i < len ; i++)
		cout<<result[len - i - 1];
	cout<<endl;
}
void permutation::downhex()
{
	//downhex permutation generation
	int rightsmall;
	int* result = new int[len];
	for(int i = 0 ;i < len ; i++)
		result[i] = 0;
	for(int i = 1 ; i < len ; i++)
	{
		rightsmall = downid[len - i];
		int bigger = 0;
		for(int j = 0 ; j < rightsmall + 1 ; j++)
		{
			if(result[j] > (len - i + 1))
				bigger++;
		}
		for(int j = rightsmall ; j < len ; j++)
		{
			if(result[j + bigger] ==0)
			{
				result[j + bigger] = len - i + 1;
				break;
			}
		}
	}
	for(int i = 0 ;i < len ; i++)
	{
		if(result[i] == 0)
			result[i] = 1;
	}
	cout<<"The downhex permutation of "<<nownum<<" is:";
	for(int i = 0 ; i < len ; i++)
		cout<<result[len - i - 1];
	cout<<endl;
}
void permutation::sjt()
{
	int* result = new int[len];
	for(int i = 0 ; i < len ; i++)
		result[i] = 0;
	for(int i = 0; i < len - 1 ; i++)
	{
		int directioncount = 0;
		int position = 0;
		if((len - i)%2 == 1)
		{
			if(downid[len - i -2]%2 == 1)
			{
				for(int j = 0; j < len ; j++)
				{
					if(result[j] == 0)
						directioncount++;
					if(directioncount == downid[len - i - 1] + 1)
					{
						position = j;
						break;
					}
				}
				result[position] = len - i;
			}
			else
			{
				for(int j = len - 1; j >= 0 ; j--)
				{
					if(result[j] == 0)
						directioncount++;
					if(directioncount == downid[len - i - 1] + 1)
					{
						position = j;
						break;
					}
				}
				result[position] = len - i;
			}
		}
		else
		{
			if((downid[len - i -2]+downid[len - i -3])%2 == 1)
			{
				for(int j = 0; j < len ; j++)
				{
					if(result[j] == 0)
						directioncount++;
					if(directioncount == downid[len - i - 1] + 1)
					{
						position = j;
						break;
					}
				}
				result[position] = len - i;
			}
			else
			{
				for(int j = len - 1; j >= 0 ; j--)
				{
					if(result[j] == 0)
						directioncount++;
					if(directioncount == downid[len - i - 1] + 1)
					{
						position = j;
						break;
					}
				}
				result[position] = len - i;
			}
		}
	}
	for(int i = 0 ;i < len ; i++)
	{
		if(result[i] == 0)
			result[i] = 1;
	}
	cout<<"The sjt permutation of "<<nownum<<" is:";
	for(int i = 0 ; i < len ; i++)
		cout<<result[i];
	cout<<endl;
}
void permutation::dict()
{
	int* result = new int[len];
	for(int i = 0; i < len ; i++)
		result[i] = i + 1;
	int j , k;
	for(int i = 0 ; i < nownum ; i++)
	{
		j = scanmin(result);
		k = scanmax(result , j);
		result = swap(result , j , k);
		result = converse(result , j);
	}
	cout<<"The dict-order permutation of "<<nownum<<" is:";
	for(int i = 0; i < len ; i++)
		cout<<result[i];
	cout<<endl;
}
