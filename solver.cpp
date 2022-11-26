// 11/22 Vishal Indivar Kandala
// MEEN 689 Computing Concepts Project 3
#include <iostream>
#include<cmath>
#include<vector>
#include "heat.hpp"

using namespace std;
////////////////////////////////////////////
void heat::Form_A(int layup,int v){
// Boundary condition at center
A[0][0] = 0.0;
A[0][1] = 1 + 2*(dt/pow(dr,2))*Define_Alpha(0,layup); // The thermal diffusivity of steel is used here as steel is always the
A[0][2] = 2*(dt/pow(dr,2))*Define_Alpha(0,layup); 
// Interior points
for(int i=1;i<N-1;i++){
A[i][0] = (dt/pow(dr,2))*Define_Alpha(i,layup); 
A[i][1] = 1 + 2*(dt/pow(dr,2))*Define_Alpha(i,layup);        	
A[i][2] = (dt/pow(dr,2))*Define_Alpha(i,layup); 
}	
// Boundary condition at edge
A[N-1][0] =  1 + 2*(dt/pow(dr,2))*Define_Alpha(N-1,layup);
A[N-1][1] =  2*(dt/pow(dr,2))*Define_Alpha(N-1,layup);
A[N-1][2] = 0.0;
// Visualize the A matrix.
if(v==2){
cout<<"A matrix --layup:"<<layup<<endl;
for(int i = 0;i<N;i++){
cout<<A[i][0]<<"\t"<<A[i][1]<<"\t"<<A[i][2]<<endl;
}
}
}

void heat::Form_B(int layup,int v){

for(int i =0;i<N-1;i++){
B[i] = Told[i][layup];
}	
// Boundary condition
B[N-1] = Told[N-1][layup] + Define_Q(layup)*2*dr;
//Visualize the B vector
if(v==3){
cout<<"B vector --layup:"<<layup<<endl;
for(int i = 0;i<N;i++){
cout<<B[i]<<endl;
}
}
}
////////////////////////////////////////
// 11/22 Thomas Algorithm code Amira Bushagour, Yash Narendra, Akib Sarwar
void heat::Solve_T(int layup){
  //set N to the size of the matrix
  //int N = n.size();
  //begin iterating at the second row (i = 1)
  int i = 1;
  while (i < N){
    //update the diagonal value for a gauss elimination
    A[i][1] = A[i][1] - (A[i][0] / A[i-1][1]) * A[i - 1][2];
    //update the collumB of temperatures iB accordaBce w/Gauss elimiBatioB
    B[i] = B[i] - (A[i][0] / A[i-1][1]) * B[i - 1];
    //iterate through i
    i ++;
  }
  //initialize a vector x (the temperatures at the current point)
  //vector<double> x (N, 0);
  // backwards substitution for the first row
  i = N-1;
  
  T[i][layup] = B[i] / A[i][i];
  i--;
  //a bit more complicated backwards substitution
  while (i >= 0){
    T[i][layup] = (B[i]- A[i][i+1] * T[i +1][layup]) / A[i][i];
    i--;
  }
  //return the temperatures
  }
void heat::Push_T(int layup){
for(int i=0;i<N;i++){
	Told[i][layup] = T[i][layup];
	}
}

void heat::Advance_dt(int layup,int v){
	// Form the right hand side vector for the linear equation which depends on Told.
	Form_B(layup,v);
	// Solve the linear system with A formed outside the implicit function before the temporal loop.
	Solve_T(layup);
	// Push T values back to Told for next timestep 
	Push_T(layup);
}
