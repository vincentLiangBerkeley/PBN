#include <random>
double* weights(int n);
double randomDouble(double end);


double* weights(int n){
	double *weight = new double[n];
	weight[0] = randomDouble(1);
	double limit = 1 - weight[0];
	for (int i = 1; i < n - 1; ++i){
		weight[i] = randomDouble(limit);
		limit -= weight[i];
	}
	weight[n - 1] = limit; 
	return weight;
}

// This function only generates in (0, end)
double randomDouble(double end){
	random_device rd;
	mt19937	gen(rd());
	uniform_real_distribution<> dis(0, end);
	return dis(gen);
}