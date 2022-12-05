// 11/22 Vishal Indivar Kandala
// MEEN 689 Computing Concepts Project 3

// Last updated: 12/03
// Last Edit(s): Added the vector of alpha values from Amira. 
//		Added the command line user-input functionality by Thomas.

#ifndef INIT_H
#define INIT_H
#include<vector>
// Naming convention for functions:
// 	Action_Changedvariable()
using namespace std;

// To use global variables within the scope of the solver, a namespace called heat was created and all the variables of interest are declared in this scope.
namespace heat {
    // functions
    void Print_File(int it,int interactive);
    double Define_Tg(double x, int layup);
    double Define_Q(double x, int layup,int BC);
    double Define_Alpha(double x, int layup);
    vector<double> Set_Alpha(double alpha1,double alpha2,double alpha3,double alpha4,double alpha5);
    void Define_Vars(int temp,double temp2,double temp3,double temp4, int layup, string filename);
    void Print_Rfile();
    void Form_A(int layup,int v);
    void Form_B(int layup,int v, int it,int BC);
    void Solve_T(int layup,int v,int it);
    void Advance_dt(int layup,int v,int it,int BC);
    void Push_T(int layup,int v,int it);
    void Check_T(int layup,int v);
    double Define_Lambda(double x, int layup);
    void File_Read(string filename);        //Function that will read the config file and assign to variables    //void Assign_MatConfig(int config_it, string variable);  //Function that will assign the config variable value to the correct global variable for the solver
    
    // vars
    extern bool Crystal_Flag;
    extern double dr;
    extern int Num_of_nodes;
    extern int N;
    extern int Nt;
    extern double ft;
    extern double dt;
    extern double t;
    extern double avgcput;
    extern vector<vector<double>> T; 
    extern vector<vector<double>> Told; 
    extern vector<vector<double>> A; 
    extern vector<double> B; 
    extern vector<double> r;
    extern vector<double> Tg;   //
    
    extern vector<double> cp;   //vector that stores all Cp values of the materials
    extern vector<double> rho;  //vector that stores all rho values of the materials
    extern vector<double> k;    //vecor that stores all k values of the materials
    extern vector<double> glass_t;  //vector that stores all glassing temperatures of the materials
    extern vector<double> alpha;    //vector that stores all alpha values of the materials
    
    
    // create a structure that will store the user-input variables to run the solver
    typedef struct {
    	int v, N, outfreq, layup, BC;		//verbose, grid points, output frequency, material layup, and boundary condition
    	double dt, ft, felt_Add;	//time step size, final time, and additional felt
    	string filename;		//config filename 
    } userParams;
    // create global structure for the solver parameters
    extern userParams solverParams;
    
    //define function that will ask the user for the solver parameters
    userParams askUserParams();
}

#endif

