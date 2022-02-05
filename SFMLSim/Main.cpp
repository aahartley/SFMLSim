#include "Sim.h"
#include <iostream>

void paraPi();
static long num_steps = 100000;
double step;

int main() {
	Sim sim;
	sim.draw();
/*	double start1 = omp_get_wtime();
	double pi, sum = 0.0;
	int numOft;
	step = 1.0 / (double)num_steps;
	#pragma omp parallel num_threads(4)
	{	
		double x;
		#pragma omp for reduction(+:sum) schedule(static)
		for (int i = 0; i < num_steps; i++) {
			if (omp_get_thread_num() == 0)numOft = omp_get_num_threads();
			x = (i + 0.5) * step;
			sum = sum + 4.0 / (1.0 + x * x);
		}
	}

	pi = step * sum;
	double end1 = omp_get_wtime();
	std::cout << pi << " time: "<<end1 - start1 << '\n';

	std::cout << numOft<<'\n';*/
	//paraPi();

	
	return 0;
}






void paraPi() {
	step = 1.0 / (double)num_steps;
	double pi = 0.0;
	double start = omp_get_wtime();
	int numberOfThreads{};
#pragma omp parallel num_threads(4)             
	{
		int i;
		double sum = 0.0;
		double x = 0.0;
		int id = omp_get_thread_num();
		int nt = omp_get_num_threads();
		if (id == 0)numberOfThreads = nt;
		for (i = id; i < num_steps; i = i + nt) {
			x = (i + 0.5) * step;
			sum = sum + 4.0 / (1.0 + x * x);

		}
#pragma omp atomic
		pi += sum * step;
	}
	double end = omp_get_wtime();
	std::cout << pi << "  2ndtime: " << end - start << '\n';
	std::cout << numberOfThreads;
}
