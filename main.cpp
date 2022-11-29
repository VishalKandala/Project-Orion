// 11/22 Vishal Indivar Kandala
// MEEN 689 Computing Concepts Project 3
#include<iostream>
#include<cmath>
#include "heat.hpp"
using namespace std;
int main(int argc, char **argv){
    int v = stoi(argv[1]);  
    // v for verbose: when v = 1, basic info.
    // v = 2, A matrix.
    // v = 3 , B vector at every time step.

    // Reading command line inputs.	
    int N = stoi(argv[2]); // Command line input for Number of nodes in radial direction.  
    double dt = stod(argv[3]); // Command line input for time step size. 
    double ft = stod(argv[4]); // Command line input for simulation interval.
    int outfreq = stoi(argv[5]);     
    int layup;
    layup = 1;
    // Define global variables using inputs.
    heat::Define_Vars(N,dt,ft);
    //-------------------
    if(v==1){
    // Print out basic info when v = 1
    cout << "Number of Nodes: "<<heat::Num_of_nodes << endl;
    cout << "Grid size: "<<heat::dr << endl;
    cout<<"Time step: "<<heat::dt<<endl;
    cout<<"Final time: "<<heat::ft<<endl;
    cout<<"No.of Time steps: "<<heat::Nt<<endl;
    cout << "Heat Flux: "<<heat::Define_Q(layup) << endl;
    }
    //-------------------
    // Time loop
    heat::Print_File(0,0);
    heat::Form_A(layup,v); 
    for(int it = 1;it<=heat::Nt;it++){
    // Advance the solution by one Timestep(dt)	    
    heat::Advance_dt(layup,v);
    // Update solution monitor time t.
    heat::t+=heat::dt;
    // If statement for outputting to file
    if(it%outfreq == 0){
    // Print solution at t to file.
    heat::Print_File(it,0);
    // Print the simulation monitor time.
    cout<<"t = "<<heat::t<<endl;
    	}
    }
    if(v==1){
    cout<<"Average CPU Time for T_Solve in ms: "<<heat::avgcput/heat::Nt<<endl;
    }
  

return 0;
}
