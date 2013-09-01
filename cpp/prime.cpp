#include <iostream>
#include <cstdio>
//#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <queue>
//#include <limits>
#include <sstream>
//#include <functional>
using namespace std;

#define len(array)  (sizeof (array) / sizeof *(array))
#define rep(i, s, e) for(int i = s;i < e;i++)
#define rrep(i, e, s) for(int i = e;s <= i;i--)
#define vrange(v) v.begin(), v.end()
#define vrrange(v) v.rbegin(), v.rend()
#define vsort(v) sort(vrange(v))
#define vrsort(v) sort(vrrange(v))
#define arange(a) a, a + len(a)
#define asort(a) sort(arange(a))
#define arsort(a, t) sort(arange(a), greater<t>())
#define afill(a, v) fill(arange(a), v)
#define afill2(a, v, t) fill((t *)a, (t *)(a + len(a)), v)
#define fmax(a, b) (a < b? b : a)
#define fmin(a, b) (a > b? b : a)
#define fabs(a) (a < 0? -a : a)
typedef unsigned int ui;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> P;
const int INF = (int)1e9;
const int MOD = (int)1e9 + 7;
const double EPS = 1e-10;
//const int dx[] = {1, -1, 0, 0, 1, -1, -1, 1};
//const int dy[] = {0, 0, 1, -1, -1, -1, 1, 1};
//const int weight[] = {0,1,10,100,1000,10000,100000,1000000,10000000};
//priority_queue<int, vector<int>, greater<int>> q;
typedef struct _Node {
  _Node(int arg1 = 0, int arg2 = 0 , int arg3 = 0) {
	i = arg1;
	j = arg2;
	k = arg3;
  }
  int i,j,k;
  bool operator <(const struct _Node &e) const{
    return i == e.i? j < e.j : i < e.i;
  }
  bool operator >(const struct _Node &e) const{
    return i == e.i? j > e.j : i > e.i;
  }
}node;

//calculate (a*b)%m
//http://discuss.codechef.com/questions/9723/witmath-editorial
ull bigMul(ull a, ull b, ull m){
	int base = (int)1e9;
	ull a_low = a % base, a_high = a / base, b_low = b % base, b_high = b / base, result; 
	result = (a_high * b_high) % m;
	rep(i, 0, 9) result = (result * 10) % m;
	result = (result + a_low*b_high + b_low*a_high) % m;
	rep(i, 0, 9) result = (result * 10) % m;
	result = (result + a_low*b_low) % m;
	return result;
}

//n**p % m
ull bigPowMod(ull n, ull p, ull m){
  ull ans = 1, ln = n;
  if(p <= 0) return 1;
  while(p != 0){
	if((p & 1) == 1) ans = bigMul(ans, ln, m); //ans = (ans*ln) % m;
	//ln = (ln * ln) % m;
	ln = bigMul(ln, ln, m);
	p = p >> 1;
  }
  return ans;
}

bool suspect(int a, int s, ull d, ull n) {
  ull x = bigPowMod(a, d, n);
  if (x == 1) return true;
  for (int r = 0; r < s; ++r) {
    if (x == n - 1) return true;
    //x = x * x % n;
	x = bigMul(x, x, n);
  }
  return false;
}
//MillerRabin primality test
// {2,7,61,-1}                 is for n < 4759123141 (= 2^32)
// {2,3,5,7,11,13,17,19,23,-1} is for n < 10^16 (at least)
int test[] = {2,3,5,7,11,13,17,19,23,-1};
bool MillerRabin(ull n) {
  if (n <= 1 || (n > 2 && n % 2 == 0)) return false;
  ull d = n - 1;
  int s = 0;
  while (d % 2 == 0) ++s, d /= 2;
  for (int i = 0; test[i] < n && test[i] != -1; ++i)
    if (!suspect(test[i], s, d, n)) return false;
  return true;
}

void doIt(){
  const int MAX_N = 10002;
  bool bPrimes[MAX_N];
  vector<int> primes;
  afill(bPrimes, true);
  bPrimes[0] = bPrimes[1] = false;
  rep(i, 2, MAX_N){
	if(bPrimes[i]){
	  primes.push_back(i);
	  for(int j = 2*i; j < MAX_N; j += i) bPrimes[j] = false;
	}
  }
}

//偶数は無視する
void doIt2(){
  const int MAX_N = 10002;
  bool bPrimes[MAX_N];
  vector<int> primes;
  afill(bPrimes, true);
  bPrimes[0] = bPrimes[1] = false;
  primes.push_back(2);
  for(int i = 3; i < MAX_N; i += 2){
	if(bPrimes[i]){
	  primes.push_back(i);
	  for(int j = 3*i; j < MAX_N; j += 2*i) bPrimes[j] = false;
	}
  }
  cout << primes.size() << endl;

}

void MillerRabinTest(){
	ull a = (ull)1e18;
	rep(i, 1, 21){
		cout << a-i << " is " << MillerRabin(a-i) << endl;
	}
}

int main() {
  //doIt();
  MillerRabinTest();
  return 0;
}