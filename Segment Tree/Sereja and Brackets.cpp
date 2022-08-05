//https://codeforces.com/contest/380/problem/C
/*
Sereja has a bracket sequence s1, s2, ..., sn, or, in other words, a string s of length n, consisting of characters "(" and ")".

Sereja needs to answer m queries, each of them is described by two integers li, ri (1 ≤ li ≤ ri ≤ n). The answer to the i-th query is the length of the maximum correct bracket subsequence of sequence sli, sli + 1, ..., sri. Help Sereja answer all queries.

You can find the definitions for a subsequence and a correct bracket sequence in the notes.

Input
The first line contains a sequence of characters s1, s2, ..., sn (1 ≤ n ≤ 106) without any spaces. Each character is either a "(" or a ")". The second line contains integer m (1 ≤ m ≤ 105) — the number of queries. Each of the next m lines contains a pair of integers. The i-th line contains integers li, ri (1 ≤ li ≤ ri ≤ n) — the description of the i-th query.

Output
Print the answer to each question on a single line. Print the answers in the order they go in the input.

Examples
inputCopy
())(())(())(
7
1 1
2 3
1 2
1 12
8 12
5 11
2 10
outputCopy
0
0
2
10
4
6
6
Note
A subsequence of length |x| of string s = s1s2... s|s| (where |s| is the length of string s) is string x = sk1sk2... sk|x| (1 ≤ k1 < k2 < ... < k|x| ≤ |s|).

A correct bracket sequence is a bracket sequence that can be transformed into a correct aryphmetic expression by inserting characters "1" and "+" between the characters of the string. For example, bracket sequences "()()", "(())" are correct (the resulting expressions "(1)+(1)", "((1+1)+1)"), and ")(" and "(" are not.

For the third query required sequence will be «()».

For the fourth query required sequence will be «()(())(())».
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;

struct Node {
	int open = 0, close = 0, full = 0;
};

void build(int idx, int low, int high, string str, Node seg[]) {
	if (low == high)
	{
		if (str[low] == '(')
			seg[idx].open = 1;
		else seg[idx].close = 1;
		return;
	}
	int mid = (low + high) >> 1;
	build(2 * idx + 1, low, mid, str, seg);
	build(2 * idx + 2, mid + 1, high, str, seg);

	Node leftNode = seg[2 * idx + 1], rightNode = seg[2 * idx + 2];
	seg[idx].full = leftNode.full + rightNode.full + min(leftNode.open , rightNode.close);
	seg[idx].open = leftNode.open + rightNode.open - min(leftNode.open , rightNode.close);
	seg[idx].close = leftNode.close + rightNode.close - min(leftNode.open , rightNode.close);

}

Node query(int idx, int i, int j, int low, int high, Node seg[]) {
	if (i <= low and high <= j)
	{
		return seg[idx];
	}
	else if (j<low or i>high)
	{
		Node node;
		return node;
	}
	else {
		int mid = (low + high) >> 1;
		Node leftAns = query(2 * idx + 1, i, j, low, mid, seg);
		Node rightAns = query(2 * idx + 2, i, j, mid + 1, high, seg);
		Node ansNode;
		ansNode.full = leftAns.full + rightAns.full + min(leftAns.open, rightAns.close);
		ansNode.open = leftAns.open + rightAns.open - min(leftAns.open, rightAns.close);
		ansNode.close = leftAns.close + rightAns.close - min(leftAns.open, rightAns.close);
		return ansNode;
	}
}

void solve() {
	string str;
	getline(cin, str);
	int q;
	cin >> q;
	int n = str.length();
	Node seg[4 * n];

	build(0, 0, n - 1, str, seg);

	// for (int i = 0; i <= 22; i++) {
	// 	cout << "Idx :" << i << "\n";
	// 	cout << "		Open ->" << seg[i].open << '\n';
	// 	cout << "		Close ->" << seg[i].close << '\n';
	// 	cout << "		Full ->" << seg[i].full << '\n';
	// }

	while (q--) {
		int i, j;

		cin >> i >> j;
		i--, j--;
		Node ans = query(0, i, j, 0, n - 1, seg);
		cout << 2 * ans.full << '\n';
	}
}

int main()
{
#ifndef ONLINE_JUDGE
	//for getting input from input.txt
	freopen("input.txt", "r", stdin);
	//for writing output to output.txt
	freopen("output.txt", "w", stdout);
#endif

	solve();
	return 0;
}
