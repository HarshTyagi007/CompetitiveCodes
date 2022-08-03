//https://codeforces.com/contest/339/problem/D
#include<bits/stdc++.h>
using namespace std;
typedef long long int lli;

void build(int idx, int low, int high, int arr[], int seg[], int orr) {
	if (low == high) {
		seg[idx] = arr[low];
		return;
	}
	int mid = (low + high) / 2;
	build(2 * idx + 1, low, mid, arr, seg, !orr);
	build(2 * idx + 2, mid + 1, high, arr, seg, !orr);
	if (orr)
		seg[idx] = seg[2 * idx + 1] | seg[2 * idx + 2];
	else seg[idx] = seg[2 * idx + 1] ^ seg[2 * idx + 2];
}

void update(int idx, int low, int high, int seg[], int orr, int i, int val) {
	if (low == high) {
		seg[idx] = val;
		return;
	}
	int mid = (low + high) / 2;
	if (i <= mid)
		update(2 * idx + 1, low, mid, seg, !orr, i, val);
	else update(2 * idx + 2, mid + 1, high, seg, !orr, i, val);

	if (orr)
		seg[idx] = seg[2 * idx + 1] | seg[2 * idx + 2];
	else seg[idx] = seg[2 * idx + 1] ^ seg[2 * idx + 2];
}

void solve() {
	int n, q;
	cin >> n >> q;
	int s = pow(2, n);
	int arr[s];
	for (int i = 0; i < s; i++)
		cin >> arr[i];
	int seg[4 * s];
	if (n % 2 == 0)
		build(0, 0, s - 1, arr, seg, 0);
	else build(0, 0, s - 1, arr, seg, 1);
	// for (int i = 0; i < 8; i++)
	// 	cout << seg[i] << ' ';
	// cout << '\n';
	while (q--) {
		int i, val;
		cin >> i >> val;
		if (n % 2 == 0)
			update(0, 0, s - 1, seg, 0, i - 1, val);
		else update(0, 0, s - 1, seg, 1, i - 1, val);
		// for (int i = 0; i < 8; i++)
		// 	cout << seg[i] << ' ';
		// cout << '\n';
		cout << seg[0] << '\n';
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
