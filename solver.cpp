// 11/22 Vishal Indivar KandL:ala
// MEEN 689 Computing Concepts Project 3
#include <iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include "heat.hpp"

using namespace std;
////////////////////////////////////////////
void heat::Form_A(int layup,int v){
// Boundary condition at center
A[0][0] = 0.0;
A[0][1] = 1 + 2*Define_Lambda(r[0],layup); //((dt/pow(dr,2))*Define_Alpha(r[0],layup)); // The thermal diffusivity of steel is used here as steel is always the
A[0][2] = -1*2*Define_Lambda(r[0],layup);   //((dt/pow(dr,2))*Define_Alpha(r[0],layup)); 
// Interior points
for(int i=1;i<N-1;i++){
A[i][0] = -1*Define_Lambda(r[i],layup); //((dt/pow(dr,2))*Define_Alpha(r[i],layup)); 
A[i][1] = 1 + (2*Define_Lambda(r[i],layup)); //*(dt/pow(dr,2))*Define_Alpha(r[i],layup));        	
A[i][2] = -1*Define_Lambda(r[i],layup); //((dt/pow(dr,2))*Define_Alpha(r[i],layup)); 
}	
// Boundary condition at edge
A[N-1][0] =  -1*2*Define_Lambda(r[N-1],layup); //*((dt/pow(dr,2))*Define_Alpha(r[N-1],layup));
A[N-1][1] =  1 + (2*Define_Lambda(r[N-1],layup));  //*(dt/pow(dr,2))*Define_Alpha(r[N-1],layup));
A[N-1][2] = 0.0;
// Visualize the A matrix.
if(v==2){
cout<<"A matrix --layup:"<<layup<<endl;
for(int i = 0;i<N;i++){
cout<<A[i][0]<<"\t"<<A[i][1]<<"\t"<<A[i][2]<<endl;
}
}
}

void heat::Form_B(int layup,int v, int it,int BC){
//r = 0.0 Boundary condition
B[0] = Told[0][layup] + 2*dr*(Define_Q(r[0],layup,BC))*Define_Lambda(r[0],layup);  //((dt/pow(dr,2))*Define_Alpha(r[0],layup));	// 2*Q/k*(alpha*dt/dx**2)
for(int i =1;i<N-1;i++){
B[i] = Told[i][layup];
}
//r = 8.0 Boundary condition
B[N-1] = Told[N-1][layup] +  2*dr*(Define_Q(r[N-1],layup,BC))*Define_Lambda(r[N-1],layup); //((dt/pow(dr,2))*Define_Alpha(r[N-1],layup));	// 2*Q/k*(alpha*dt/dx**2)
//Visualize the B vector
if(v==3 && it>0){
cout<<"B vector --layup:"<<layup<<endl;
for(int i = 0;i<N;i++){
cout<<B[i]-200.0<<endl;
}
}
}
////////////////////////////////////////
// 11/22 Thomas Algorithm code Amira Bushagour, Yash Narendra, Akib Sarwar
void heat::Solve_T(int layup,int v,int it){
  clock_t cputstart = clock();
  vector<vector<double>> At;
  At.resize(N); // Atemp
  //copy A matrix into At
  for(int i = 0;i<N;i++){
  	At[i].resize(3);
  	for(int j = 0; j<3;j++){
  		At[i][j] = A[i][j];	
  	}
  }
//begin with the second row
  int i = 1;
  double ratio;
  while (i < N){
    //set the elimination ratio
    ratio = (At[i][0] / At[i-1][1]);
    //update diagonal values 
    At[i][1] = At[i][1] - ratio * At[i - 1][2];
    //update lower diagonal values
    At[i][0] = At[i][0] - ratio * At[i-1][1];
    //update the collumB of temperatures in accordaBce w/Gauss elimiBatioB
    B[i] = B[i] - ratio * B[i - 1];
    //iterate through i
    i ++;
  }
  //print a matrix if verbose v is chosen
  if(v==4 && it == 2){
	cout<<"At & A matrices -- Atfter Elimination:"<<layup<<endl;
        for(int i = 0;i<N;i++){
        cout<<At[i][0]<<"\t"<<At[i][1]<<"\t"<<At[i][2]<<"|"<<A[i][0]<<A[i][1]<<A[i][2]<<endl;
        }
  }	
  // backwards substitution for the first row 
  T[N-1][layup] = B[N-1] / At[N-1][1];
  //iterate through back substitution in accordance w/Thomas algorithm
  for(int i = N-2;i>=0;i--){
    T[i][layup] = (B[i]- (At[i][2] * T[i +1][layup])) / At[i][1];
  }
  //return the temperatures
  
clock_t cputend = clock();
double cput = 1000.0*(cputend-cputstart)/CLOCKS_PER_SEC; // calculating the time for calculation in milliseconds from clock speed.
avgcput+=cput;
}
void heat::Push_T(int layup,int v,int it){
for(int i=0;i<N;i++){
	Told[i][layup] = T[i][layup];
	}
if(v==5 && it>0){
cout<<"i,Told,T"<<endl;
for(int i = 0; i<N;i++){
cout<<i<<","<<Told[i][layup]<<","<<T[i][layup]<<endl;
}
}
}

void heat::Advance_dt(int layup,int v, int it,int BC){
	// Form the co-efficient matrix as it is being modified in Solve_T.
	//Form_A(layup,v);
	// Form the right hand side vector for the linear equation which depends on Told.
	Form_B(layup,v,it,BC);
	//if(v==2){cout<<"B"<<endl;}
	// Solve the linear system with A formed outside the implicit function before the temporal loop.
	Solve_T(layup,v,it);
	// Check if Glass temperatures are reached.
	Check_T(layup,v);
	if(Crystal_Flag == false){
	Push_T(layup,v,it);}	// Push T values back to Told for next timestep 
}

void heat::Check_T(int layup,int v){
//	cout<<Crystal_Flag<<endl;
	if(Crystal_Flag==false){
		for(int i = 0;i<N;i++){
			if (T[i][layup] >Tg[i] || T[i][layup] == Tg[i]){
				cout<<"Location of Failure:"<<r[i]<<","<<T[i][layup]<<endl;
				Crystal_Flag = true;
		        }	
		}	
	}
}
