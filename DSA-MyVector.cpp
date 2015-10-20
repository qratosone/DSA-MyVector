// DSA-MyVector.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MyVector.h"
#include <iostream>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	int n, m;
	cin >> n >> m;
	MyVector<int> Points(n);
	for (int i = 0; i < n; i++)
	{
		int temp;
		cin >> temp;
		Points.insert(0, temp);
	}
	Points.qSort();
	Points.show();
	cout << endl;
	int a, b;
	for (int i = 0; i < m; i++)
	{
		scanf_s("%d %d", &a, &b);
		if (a>b) swap(a, b);
		int lo = Points.search(a);
		int hi = Points.search(b);
		int ans = hi - lo;


		if (Points[lo] == a)ans++;
		//if(Points[lo]<a&&b>Points.lastvalue())ans--;
		if (ans<0)ans = 0;
		printf("%d\n", ans);
	}
	return 0;
}

