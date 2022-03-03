#include "Matrix.h"

Matrix::Matrix(float x, float y, float n) {
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {
			m[i][j] = x;
			m[i][j+1] = y;
			m[i][j+2] = n;

		}
	}
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << m[i][j] << " ";

		}
	}
	std::cout << '\n';
}
void Matrix::multiply() {
	float transform[3][1]{  { 1},
							{1.05 },
							{1} 
	};
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << "m: " << m[i][j] << " " << " trans: " << transform[j][i]<<" ";
			m[i][j] *=transform[j][0];
		}
	}
	std::cout << "\n";
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << m[i][j] << " ";

		}
	}

}