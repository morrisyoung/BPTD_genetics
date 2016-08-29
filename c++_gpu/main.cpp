/*

Welcome! I'm the sampling program for the genetic tensor project

I will utilize GPU whenever necessary, to make the program run whole-genome data

*/


#include <iostream>
#include <vector>
#include <sys/time.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include "utility.h"
#include "global.h"
#include "data_interface.h"
#include "sampler.h"
#include "loglike.h"





using namespace std;





//==== global var definition
Matrix X;
Tensor Y;
Tensor markerset;
Tensor Y1;
Matrix U1;
Matrix V1;
Matrix T1;
Matrix Beta;
Tensor Y2;
Matrix U2;
Matrix V2;
Matrix T2;
float alpha = 1;
// NOTE: the following are the real scenario for chr22 and brain tensor
int K = 13;
int I = 159;
int J = 585;
int S = 14056;
int D1 = 40;
int D2 = 40;

int N_element = 0;





vector<float> loglike_total;
vector<float> loglike_data;
vector<float> loglike_Y1;
vector<float> loglike_Y2;
vector<float> loglike_U1;
vector<float> loglike_V1;
vector<float> loglike_T1;
vector<float> loglike_U2;
vector<float> loglike_V2;
vector<float> loglike_T2;
vector<float> loglike_Beta;
vector<float> loglike_alpha;







int main()
{
	cout << "now entering the sampling program..." << endl;


	//==== data loading
	//data_load_simu()
	data_load_real();


	//==== pre-setting some parameters
	// I will treat all observed variables as input of simu functions
	float mu = 0;						// TODO
	float lamb = 1.0;					// TODO
	float alpha0 = 1.0;					// TODO
	float beta0 = 0.5;					// TODO


	loglike_total.clear();
	loglike_data.clear();
	loglike_Y1.clear();
	loglike_Y2.clear();
	loglike_U1.clear();
	loglike_V1.clear();
	loglike_T1.clear();
	loglike_U2.clear();
	loglike_V2.clear();
	loglike_T2.clear();
	loglike_Beta.clear();
	loglike_alpha.clear();


	int ITER = 50;						// TODO
	for(int i=0; i<ITER; i++)
	{
		cout << "now working on iter#" << i << endl;

		//==== timer starts
		struct timeval time_start;
		struct timeval time_end;
		double time_diff;
		gettimeofday(&time_start, NULL);


		//==== sample all
		sampler_subT(lamb);
		sampler_factor(lamb, mu, lamb);
		sampler_precision(alpha0, beta0);


		//==== cal loglike
		loglike_cal(mu, lamb, alpha0, beta0);


		//==== timer ends
		gettimeofday(&time_end, NULL);
		time_diff = (double)(time_end.tv_sec-time_start.tv_sec) + (double)(time_end.tv_usec-time_start.tv_usec)/1000000;
		printf("time used per iteration is %f seconds.\n", time_diff);

	}




	//==== save the learned model
	data_save();



	cout << "we are done..." << endl;

	return 0;
}

