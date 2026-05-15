const int MAXN=1e6+5;

// d1[i] = max odd palindrome centered on i
// si d1[i] = k, existe un palíndromo en s[i-k+1, ..., i+k-1] de length 2*k-1
int d1[MAXN];
//d2[i] = max even palindrome centered on i
// si d2[i] = k, existe un palíndromo en s[i-k, ..., i+k-1] de length 2*k
int d2[MAXN];
//s  aabbaacaabbaa
//d1 1111117111111
//d2 0103010010301
void manacher(string& s){
	int l=0,r=-1,n=s.size();
	forr(i,0,n){
		int k=i>r?1:min(d1[l+r-i],r-i);
		while(i+k<n&&i-k>=0&&s[i+k]==s[i-k])k++;
		d1[i]=k--;
		if(i+k>r)l=i-k,r=i+k;
	}
	l=0;r=-1;
	forr(i,0,n){
		int k=i>r?0:min(d2[l+r-i+1],r-i+1);k++;
		while(i+k<=n&&i-k>=0&&s[i+k-1]==s[i-k])k++;
		d2[i]=--k;
		if(i+k-1>r)l=i-k,r=i+k-1;
	}
}