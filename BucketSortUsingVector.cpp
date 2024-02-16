//Non-Comparison Sorting Algorithms

#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>
#include<iomanip>
#include<cmath>
#include<vector>

using namespace std;

long int count=0;

//Counting Sort
void CountingSort(int *a, int n, int k)
{
	int *c;
	int *b;
	
	c = new int[k+1];
	b = new int[n+1];
	
	for(int i=0;i<=k;i++)
	{
		count++;
		c[i] = 0;
	}
	
	for(int i=1;i<=n;i++)
	{
		count++;
		c[a[i]] += 1; 
	}
	for(int i=1;i<=k;i++)
	{
		count++;
		c[i] += c[i-1];
	}
	
	for(int i=n;i>=1;i--)
	{
		count++;
		b[c[a[i]]] = a[i];
		c[a[i]] -= 1;
	}
	
	//Copying the sorted elements from b[] to a[]
	for(int i=1;i<=n;i++)
		a[i] = b[i];
	
		
	delete(c);
	delete(b);
}


//Radix Sort
//Extracting 'i'th digit from a number 'x'
int GetDigit(int x,int i)
{
	int d;
	x = x / pow(10,i-1);
	d = x % 10;
	return d;
}

//Stable sort
void CountingSort(int *a, int n, int k, int d)
{
	//n - size of a
	//k - counting sort property - maximum element value - here, 0 to 9
	//d - digit: sorting to be done on which digit(d)
	//d=1 - 1's place; 	d=2 - 10's place;	d=3 - 100's place; etc.,

	int *b;
	int *c;
	
	int s;
	
	b = new int[n+1];
	c = new int[k+1];
	
	for(int i=0;i<=k;i++)
	{
		count++;
		c[i] = 0;
	}
	
	for(int i=1;i<=n;i++)
	{
		count++;
		s = GetDigit(a[i],d);
		c[s] += 1; 
	}
	for(int i=1;i<=k;i++)
	{
		count++;
		c[i] += c[i-1];
	}
	
	for(int i=n;i>=1;i--)
	{
		count++;
		s = GetDigit(a[i],d);
		b[c[s]] = a[i];
		c[s] -= 1;
	}
	
	//Copying the sorted elements from b[] to a[]
	for(int i=1;i<=n;i++)
		a[i] = b[i];

	delete(c);
	delete(b);
}

void RadixSort(int *a, int n, int d)
{
	//i=1 - 1's place; 	i=2 - 10's place;	i=3 - 100's place;
	for(int i=1;i<=d;i++)
	{
		CountingSort(a,n,9,i);
	}
}

void InsertionSort(vector<double> &a)
{
	int i,j,n;
	double key;
	n = a.size();	
	for(j=1;j<=n-1;j++)
	{
		i = j-1;
		key = a[j];
		
		while(i>=0 && a[i]>key)
		{
			count++;
			a[i+1] = a[i];
			i = i-1;		
		}
		count++;
				
		a[i+1] = key;
	}
}


void BucketSort(double a[],int n)
{
	//Creating array of 'n' buckets
	vector<double> *Buckets = new vector<double>[n];
	
	//Inserting elements from a[] into different buckets
	int bNo;
	for(int i=1;i<=n;i++)
	{
		bNo = a[i]*n;
		//cout<<"\t["<<a[i]<<":"<<bNo<<"]";
		Buckets[bNo].insert(Buckets[bNo].begin(),a[i]);
		count++;
	}

	//Sorting each buckets
	for(int i=0;i<n;i++)
	{
		count++;
		InsertionSort(Buckets[i]);
	}
	
	//Concatenating buckets
	double t;
	for(int i=0,j=1;i<n;i++)
	{
/*		cout<<"\nBucket Number: "<<i;
		for(int k=0;k<Buckets[i].size();k++)
			cout<<" "<<Buckets[i][k];
*/
		for(int p=0;p<Buckets[i].size();p++)
		{
			count++;
			t = Buckets[i][p];
			a[j++] = t;
		}
	}
//	delete(Buckets);
}

int main()
{
	cout<<showpoint<<setprecision(12);
	
	ofstream outf;
	ifstream inf;

	int n,k;
	int *a;
	
	cout<<"\nEnter n:";
	cin>>n;
	
	//Random numbers are going to be generated in the range 0 to n
	
	time_t stt;
	time(&stt);
	srand((long int)stt);
	
	//Loading numbers to input file
	outf.open("in.txt");
	for(int i=0;i<n;i++)
		outf<<"\t"<<rand()%(n+1);
	outf.close();
	
	//k is maximum element
	k=n;
	
	a = new int [n+1];
	
	//Counting Sort
	//Reading input in array from input file
		
	inf.open("in.txt");		
	for(int i=1;i<=n;i++)
	{
		inf>>a[i];
	}
	inf.close();
	
	count = 0;
	CountingSort(a,n,k); //k is maximum element in a[]
	
	//Writing sorted numbers to output file
	outf.open("CountingOut.txt");
	for(int i=1;i<=n;i++)
	{
		outf<<"\t"<<a[i];
	}
	outf.close();
	
	cout<<"\n\nCounting Sort - No. of Operations: "<<count;
	
	
	
	//Radix Sort
	//Reading input in array from input file
		
	inf.open("in.txt");		
	for(int i=1;i<=n;i++)
	{
		inf>>a[i];
	}
	inf.close();
	
	//d - No. of digits in maximum number n
	//Counting the maximum number of digits. Max value is k
	int tmp=k,d=0;
	while(tmp!=0)
	{
		d++;
		tmp/=10;
	}
	
	count = 0;
	RadixSort(a,n,d);
	
	//Writing sorted numbers to output file
	outf.open("RadixOut.txt");
	for(int i=1;i<=n;i++)
	{
		outf<<"\t"<<a[i];
	}
	outf.close();
	
	cout<<"\n\nRadix Sort - No. of Operations: "<<count;
	
	
	//Bucket Sort
	//Reading input in array from input file
	double *b = new double[n+1];	
	inf.open("in.txt");		
	for(int i=1;i<=n;i++)
	{
		inf>>a[i];
		//To make input integer number to a decimal within the range 0 to 1
		b[i] = a[i]/(double)(n+1); 
	}
	inf.close();
	
	count = 0;
	BucketSort(b,n); 
	
	//Writing sorted numbers to output file
	outf.open("BucketOut.txt");
	for(int i=1;i<=n;i++)
	{
		outf<<"\t"<<b[i];
	}
	outf.close();
	
	cout<<"\n\nBucket Sort - No. of Operations: "<<count;

	cout<<"\n\n";
	delete(a);
	delete(b);

}