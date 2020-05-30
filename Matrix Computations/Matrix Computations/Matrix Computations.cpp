// MIT License
//
// Copyright(c) 2020 Bryce Tuton
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software andassociated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, andto permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice andthis permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// Matrix Computations.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>

using namespace std;

// Calculate the Matrix Determinant
long long CalDet(int *mat, int matSize) {
	if (matSize == 1) // Determinant is the only element
		return mat[0];
	else if (matSize == 2) { // Determinant = ad - bc
		return ((long long)mat[0] * (long long)mat[3]) - ((long long)mat[1] * (long long)mat[2]);
	} else { // Get determinant for smaller matricies within this matrix.
		int *newMat = new int[(matSize - 1) * (matSize - 1)]; // Create empty matrix for one step down.
		int det = 0;
		for (int i = 0; i < matSize; i++) {
			int count = 0;
			// Fill lower matrix for lower call. (reuse this array for the rest of the matricies)
			for (int j = matSize; j < matSize * matSize; j++) {
				if (j % matSize == i)
					continue;
				newMat[count] = mat[j];
				count++;
			}
			int additional = 1; // Alternate between positive and negative modifiers for determinant calculation
			if (i % 2 == 1)
				additional = -1;
			det += mat[i] * (CalDet(newMat, matSize - 1) * (long long)additional); // Add lower matrix determinant to this determinant.
		}
		delete[] newMat;
		return det;
	}
}

int main() {
	random_device rd;
	std::cout << "Matrix Size (n x n): ";
	int size;
	cin >> size;
	cout << "Creating Matrix of size: " << size << "x" << size << endl;
	int *mat = new int[size * size]();
	// Fill matrix
	for (int i = 0; i < size * size; i++) {
		mat[i] = rd() % (INT32_MAX / 8); // Limit placed to help avoid incorrect result from it being larger than int64 supports
		cout << mat[i];
		if (i % size == size - 1)
			cout << endl;
		else
			cout << ",";
	}
	cout << "Calculating" << endl;
	cout << "Determinant: "<< CalDet(mat, size);
	delete[] mat;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
