#include<iostream>
#include <algorithm>
#include<cmath>
#include<cstdio>
#include <cstdlib>
#include <ctime>
#include<sstream>
#include <vector>
using namespace std;
#define MAX 10000
string A[MAX][MAX],B[MAX][MAX];
bool missing[MAX][MAX];
char buf [5000];
string firstline ;
int max_row = -1, max_col = -1;
vector< pair<double, string> > results;
void load_from_csv ( string a [MAX][MAX] , string filename, int skip_first=1){
	FILE *fp = fopen(filename.c_str(),"r");
	string s ;
	if(skip_first)fscanf(fp, "%s",buf);
	firstline = buf;
	int row = 0, col = 0;
	max_row = -1, max_col = -1;
	while (fscanf(fp, "%s",buf)!=EOF){
		s = buf;
//		cout<<s<<endl;
		for(int i =0 ; i<s.size(); i++)
		{	if( s[i] == ',') s[i]= ' ';
		}
		istringstream in (s);
		string number;
		
		while( in >> number ) {
		//	cout<<number<<endl;
			istringstream inn (number);
			//double temp ;	inn >> temp; if(number[0] != 'N' && number[0]!='T') a[row][col++] = temp;	else a[row][col++] = -1;
			a[row][col] = number;
			col++;
			if(col > max_col) max_col = col;
			
			//cout<<"hi"<<endl;
		}
		row ++;
		col = 0;
		if(row > max_row) max_row = row;
	//	cout<<row<<" "<<col<<endl;
	}
	fclose(fp);
}
void find_rms(string filename, int skip_first= 1){
	load_from_csv(B, filename.c_str(),skip_first);
	//cout<<max_row<<" "<<max_col<<endl;
	
     double rms = 0;
     int cnt = 0;
	 for(int i =0 ; i<max_row; i++)
	for(int j =0 ; j<max_col; j++)
		if( A[i][j]!=B[i][j] and A[i][j][0]!='N')
		{
		//	cout<<i<<" "<<j<<endl; cout<<A[i][j]<<endl; cout<<B[i][j]<<endl; cout<<(left-right)*(left-right)<<endl;
				istringstream in (A[i][j]);
				double left, right;
				in >> left;
				istringstream in1 (B[i][j]);
				in1>>right;
			if(left!=right) {
				cnt++;
				rms += (left-right)*(left-right);
			}
				
		}
		
	if(cnt == 0)cout<<"No mis matches\t"<<filename<<endl;	
	else {
		//cout<<"Mismatches created = "<<cnt<<"\t";
		//cout<<filename<<"\t"<<sqrt(rms/cnt)<<endl;
		results.push_back(  make_pair(sqrt(rms/cnt),filename));
	}
}
int main(){
	srand(time(NULL));
	load_from_csv(A, "caioriginal12.csv");
	
	for(int k = 1; k<=50; k++){
		ostringstream outx;
		outx<<k;	
		find_rms("pca_bpca_" + outx.str() + ".csv");
	}

	sort(results.begin(), results.end());
	for(int i =0 ; i<results.size(); i++)
	{
		cout<<results[i].second<<"  \t"<<results[i].first<<endl;
	}
/*	find_rms("caimissing1.csv",0);
	find_rms("MissingValue_Result_1_Vadde_Anugu.csv",0);
	
	for(int i = 2; i<=14; i++){
		ostringstream outx;
		outx<<i;	
		find_rms("k" + outx.str() + ".csv",0);
	}
*/


     return 0;
} 
