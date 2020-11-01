#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;
class SA{
private:
	int low,high;
	int *p;
public:
	SA(){
		low=0;
		high=-1;
		p=NULL;
	}
	SA(int l,int h){
		if((h-l+1)<=0){
			cout<<"constructor error in bounds definition"<<endl;
			exit(1);
		}
		low=l;
		high=h;
		p=new int[h-l+1];
	}
	SA(int i){
		low=0;
		high=i-1;
		p=new int[i];
	}
	SA(const SA & s){
		int size=s.high-s.low+1;
		p=new int[size];
		for(int i=0; i<size; i++)
			p[i]=s.p[i];
		low=s.low;
		high=s.high;
	 }
	~SA(){
		delete [] p;
	}


	int& operator[](int i){
		if(i<low || i>high){
			cout<<"index "<<i<<" out of range SA"<<endl;
			exit(1);
		}
			return p[i-low];
	}
	SA & operator = (SA s){
		if(this==&s)
			return *this;
		delete [] p;
		int size=s.high-s.low+1;
		 p=new int[size];
		 for(int i=0; i<size;i++)
			 p[i]=s.p[i];
		 low=s.low;
		 high=s.high;
		 return *this;
	}
	friend ostream& operator<<(ostream& os, SA s);
};
ostream& operator <<(ostream& os,SA s){
		int size=s.high-s.low+1;
		for(int i=0;i<size;i++)
			cout<<s.p[i]<<" ";
		cout<<endl;
		return os;
};


class SM{
private:
	int r_low,r_high,c_low,c_high;
	SA *p;
public:

	SM(){
		r_low=0;
		c_low=0;
		r_high=-1;
		c_high=-1;
		p=NULL;
	}

	SM(int r,int c){
		r_low=c_low=0;
		r_high=r-1;
		c_high=c-1;
		p=new SA[r];
		for(int i=0;i<r;i++){
			new (&p[i]) SA(c);
		}

	}
	SM(int r_low,int r_high,int c_low,int c_high){
		if((r_high-r_low+1)<=0 || (c_high-c_low+1)<=0){
			cout<<"constructor error in bounds definition"<<endl;
			exit(1);
		}
		this->r_low=r_low;
		this->r_high=r_high;
		this->c_low=c_low;
		this->c_high=c_high;
		p=new SA(r_low,r_high);
		for(int i=r_low;i<=r_high;i++){
			new (&p[i]) SA(c_low,c_high);
		}
	}
	~SM(){
	}
	SA& operator [] (int i){
		if(i<r_low || i>r_high){
			cout<< "index "<<i<<" out of range SM";
			cout<<endl;
		 exit(1);
		 }
		 return p[i];
	}
	SM operator * (SM& s){
		if((this->c_high-this->c_low) != (s.r_high-s.r_low)){
			cout<<"the number of columns in the first matrix must be equal to the number of rows in the second matrix.";
			cout<<endl;
			exit(1);
		}
		int row=this->r_high-this->r_low+1;
		int col=s.c_high-s.c_low+1;
		int k=this->c_high-this->c_low+1;
		SM ans(row,col);
		for(int i=0;i<row;i++){
			for(int j=0;j<col;j++){
					ans[i][j]=0;
				for(int m=0;m<k;m++){
					ans[i][j]+=(*this)[i+this->r_low][m+this->c_low]*s[m+s.r_low][j+s.c_low];
				}
			}
		}
		return ans;
	}

	friend ostream& operator << (ostream& os, SM s);

};
ostream& operator <<(ostream& os, SM s){
	for(int i=s.r_low;i<=s.r_high;i++){
		cout<<s[i];
	}
	return os;
};

int main(){
	int r=8;
	int c1=2;
	SM a(r,c1);
	for(int i=0;i<r;i++){
		for(int j=0;j<c1;j++){
			a[i][j]=i*5+j;
		}
	}
	cout<<"printing a ";
	cout<<endl;
	cout<<a;
	SM c(1,2,2,9);
	for(int i=1;i<=2;i++){
		for(int j=2;j<=9;j++){
			c[i][j]=i*3+j;
		}
	}
	cout<<"printing c "<<endl;
	cout<<c;
	cout<<"printing a*c "<<endl;
	cout<<a*c;

}
