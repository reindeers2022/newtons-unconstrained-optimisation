/*
newtons method for unconstrained optimisation problems involving simultaneous equation with multivariable function
LIMITATIONS OF THIS CODE
-works for polynomial eqn of degree of 3 or less
-can take only 2 simultaneous eqn that have only 2 independent variables i.e. m=n=2
-function must not contain product of two variables
-initial approximation (x,y)=(0,0)
*/

#include<iostream>
#include<cmath>
#include <iomanip>
using namespace std;

//class fn to store 3rd or lower degree polynomial equations
class fn{
	//needs to store ax^3+ey^3+bx^2+fy^2+cx+gy+d=0
	double a,e,b,f,c,g,d;
public:
	//declaring constructors
	fn(){}
	fn(double a, double e, double b, double f, double c, double g, double d);

	//display function
	void showF(){
		cout<<a<<"x^3+"<<e<<"y^3+"<<b<<"x^2+"<<f<<"y^2+"<<c<<"x+"<<g<<"y+"<<d<<endl;
	}

	// declaring setter method
	void setA(double a);
	void setB(double b);
	void setC(double c);
	void setD(double d);
	void setE(double e);
	void setF(double f);
	void setG(double g);
	
	//declaring getter method
	double getA();
	double getB();
	double getC();
	double getD();
	double getE();
	double getF();
	double getG();

	//evaluate function at x=q y=w
	double getValueAt(double q,double w);

	//find first order derivative
	fn firstDerivative(char wrt);
};

//defining constructor
fn::fn(double a, double e, double b, double f, double c, double g, double d){
	this->a=a;
	this->b=b;
	this->c=c;
	this->d=d;
	this->e=e;
	this->f=f;
	this->g=g;
}

//defining setter method
void fn::setA(double a){this->a=a;}
void fn::setB(double b){this->b=b;}
void fn::setC(double c){this->c=c;}
void fn::setD(double d){this->d=d;}
void fn::setE(double e){this->e=e;}
void fn::setF(double f){this->f=f;}
void fn::setG(double g){this->g=g;}

//defining getter method
double fn::getA(){return a;}
double fn::getB(){return b;}
double fn::getC(){return c;}
double fn::getD(){return d;}
double fn::getE(){return e;}
double fn::getF(){return f;}
double fn::getG(){return g;}

//defining valueAt() function
double fn::getValueAt(double q,double w){
	return (a*pow(q,3)+e*pow(w,3)+b*pow(q,2)+f*pow(w,2)+c*pow(q,1)+g*pow(w,1)+d);
}

//defining first derivative function
fn fn::firstDerivative(char wrt){
	fn temp;
	if(wrt=='x'){
		temp.setA(0);
		temp.setB(3*a);
		temp.setC(2*b);
		temp.setD(c);
		temp.setE(0);
		temp.setF(0);
		temp.setG(0);
	}else if(wrt=='y'){
		temp.setA(0);
		temp.setB(0);
		temp.setC(0);
		temp.setD(g);
		temp.setE(0);
		temp.setF(3*e);
		temp.setG(2*f);
	}else{
		cout<<"SOMETHING WENT WRONG!"<<endl;
	}
	
	return temp;
}


//class mat to store matrix and perform operations on them
class Matrix{
	//static int m,n;
	double myMat[2][2];
public:
	//declaring constructors
	Matrix();
	Matrix(double one,double two,double three,double four);

	//declaring a showM()
	void showM();

	//getter and setter methods
	void set00(double s00);
	void set10(double s10);
	void set01(double s01);
	void set11(double s11);

	double get00();
	double get10();
	double get01();
	double get11();

	//declaring operation
	Matrix getInverse();
	Matrix getDifference(Matrix obj);
	Matrix getProduct(Matrix obj);
};

//defining matrix constructors
Matrix::Matrix(){
	for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				myMat[i][j]=0;
			}
		}
}

Matrix::Matrix(double one,double two,double three,double four){
	myMat[0][0]=one;
	myMat[0][1]=two;
	myMat[1][0]=three;
	myMat[1][1]=four;
}


//defining showM()
void Matrix::showM(){
	for(int i=0;i<2;i++){
		cout<<"|";
		for(int j=0;j<2;j++){
			cout<<" "<<setw(12)<<myMat[i][j]<<" ";
		}
		cout<<"|\n";
	}
}

//defining getter and setter
void Matrix::set00(double s00){myMat[0][0]=s00;}
void Matrix::set10(double s10){myMat[1][0]=s10;}
void Matrix::set01(double s01){myMat[0][1]=s01;}
void Matrix::set11(double s11){myMat[1][1]=s11;}

double Matrix::get00(){return myMat[0][0];}
double Matrix::get10(){return myMat[1][0];}
double Matrix::get01(){return myMat[0][1];}
double Matrix::get11(){return myMat[1][1];}


//defining operations
Matrix Matrix::getInverse(){
	Matrix temp;
	double det=((get00()*get11())-(get01()*get10()));
	temp.set00(get11()/det);
	temp.set10(-get10()/det);
	temp.set01(-get01()/det);
	temp.set11(get00()/det);
	return temp;
}
Matrix Matrix::getDifference(Matrix obj){
	Matrix temp;
	temp.set00(get00()-obj.get00());
	temp.set10(get10()-obj.get10());
	temp.set01(get01()-obj.get01());
	temp.set11(get11()-obj.get11());
	return temp;
}
Matrix Matrix::getProduct(Matrix obj){
	//(2x2)*(2x1)=(2x1)
	Matrix temp;
	temp.set00((get00()*obj.get00())+(get01()*obj.get10()));
	temp.set01(0);
	temp.set10((get10()*obj.get00())+(get11()*obj.get10()));
	temp.set11(0);
	return temp;
}

int main(){

	// m is number of simultaneous equations having n variables
	int m=2,n=2; //n is fixed to two for now  
	cout<<"enter two simultaneous equations having two independent varibles:"<<endl;	

	//take input of m simultaneous equations
	int i=0;
	fn f[m];
	while(i!=m){	// i interates from 0 to m-1 (m-1 included)
		cout<<i+1<<".ax^3+ey^3+bx^2+fy^2+cx+gy+d=0; accordingly enter a,e,b,f,c,g and d: "<<endl;
		cout<<"(example-> x^3+y-1=0 is 1 0 0 0 0 1 -1)"<<endl;
		double aInput,bInput,cInput,dInput,eInput,fInput,gInput;
		cin>>aInput>>eInput>>bInput>>fInput>>cInput>>gInput>>dInput;
		f[i]=fn(aInput,eInput,bInput,fInput,cInput,gInput,dInput);
		i++;
	}

	//input how many iteration to perform
	cout<<"how many iterations do you wish to find: ";
	int nItr;
	cin>>nItr;

	//initial approximation
	//for i=0 => X_1 = (0,0)
	Matrix myXi[nItr];
	myXi[0]=Matrix(0,0,0,0);
	int currentIndex=1;//current empty index
	for(int i=0;i<nItr;i++){
		for(int k=0;k<6;k++){
			cout<<"----";
		}
		cout<<"ITERATION "<<i+1<<"\nfor i="<<i+1<<":"<<endl;
		//X_i+1 = X_i - (B_i)^(-1) * (A_i)
		
		//finding A_i
		Matrix A_i = Matrix(f[0].getValueAt(myXi[currentIndex-1].get00(),myXi[currentIndex-1].get10()),0,f[1].getValueAt(myXi[currentIndex-1].get00(),myXi[currentIndex-1].get10()),0);

		//finding B_i then its inverse
		fn f1x=f[0].firstDerivative('x');
		fn f1y=f[0].firstDerivative('y');
		fn f2x=f[1].firstDerivative('x');
		fn f2y=f[1].firstDerivative('y');
		Matrix B_i=Matrix(f1x.getValueAt(myXi[currentIndex-1].get00(),0),f1y.getValueAt(0,myXi[currentIndex-1].get10()),f2x.getValueAt(myXi[currentIndex-1].get00(),0),f2y.getValueAt(0,myXi[currentIndex-1].get10()));
		Matrix B_i_inverse = B_i.getInverse();
		
		//subtracting from X_i
		Matrix temp = myXi[currentIndex-1].getDifference(B_i_inverse.getProduct(A_i));

		//display the final answer
		cout<<"X_"<<i+2<<" = "<<endl;
		temp.showM();

		//append X_i and increment counter
		myXi[currentIndex]=temp;
		currentIndex++;
	}

	return 0;
}