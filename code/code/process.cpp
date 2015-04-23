#include<iostream>
#include<ctime>
#include<cstdio>
#include <cstdlib>
#include <ctime>
#include<sstream>
using namespace std;
#define MAX 10000
string A[MAX][MAX];
bool missing[MAX][MAX];
int missing_in_row[MAX], missing_in_col[MAX];
char buf [5000];
string firstline ;
int max_row = -1, max_col = -1;
void load_from_csv ( string a [MAX][MAX] , string filename){
	FILE *fp = fopen(filename.c_str(),"r");
	string s ;
	fscanf(fp, "%s",buf);
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
			A[row][col] = number;
			col++;
			if(col > max_col) max_col = col;
			if(A[row][col][0] == 'N') {
				missing_in_row[row]++;
	 			missing_in_col[col]++;
			} 
			//cout<<"hi"<<endl;
		}
		row ++;
		col = 0;
		if(row > max_row) max_row = row;
	//	cout<<row<<" "<<col<<endl;
	}
	fclose(fp);
}
int main(){
	srand(time(NULL));
	load_from_csv(A, "caioriginal12.csv");
	cout<<max_row<<" "<<max_col<<endl;
	
	
	 int todisappear = max_row*max_col/10, disappeared = 0;
	 while(disappeared < todisappear){
	 	int x = rand()% max_row;
	 	int y = rand()% max_col;
	 	if(A[x][y][0] != 'N'){
	 		//if( 2*missing_in_row[x] >= max_row or 2*missing_in_col[y] >= max_col ) continue;
			disappeared++;
	 		cout<<disappeared<<" "<<x+2<<" "<<y<<" "<<A[x][y]<<endl;
	 		A[x][y] = "NA";
	 		missing_in_row[x]++;
	 		missing_in_col[y]++;
		 }
	 }
	 FILE * out = fopen("12_missing.csv","w");
	fprintf(out,"%s\n", firstline.c_str());
	 
	 for(int i =0 ; i<max_row; i++){
	for(int j =0 ; j<max_col; j++){
		if( j) fprintf(out,",");
	 fprintf(out,"%s", A[i][j].c_str());
	} 
	fprintf(out,"\n");
	} 
	fclose(out);
	
	return 0;
}
