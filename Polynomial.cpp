#include <iostream>
using namespace std;

class Polynomial {
private:
	int numTerm;// store total number of terms in polynomial expression including constant term
	int* exponent; // pointing to integer array which stores exponents
	int* coefficient; // pointing to integer array to store coefficients of every variable 
public:

	// Default constructor
	Polynomial():numTerm(0),exponent(NULL),coefficient(NULL){}

	// Paramaterized constructor 
	Polynomial(int num) {
		numTerm = num+1;
		exponent = new int[numTerm];
		coefficient = new int[numTerm];
		for (int i = 0; i < numTerm; i++) {
			exponent[i] = 0;
			coefficient[i] = 0;
		}
	}
	//Parametrized constructor
	Polynomial(int num, int* exp, int* coeff) {
		numTerm = num+1; 
		exponent = new int[numTerm];
		coefficient = new int[numTerm];
		for (int i = 0; i <numTerm; i++) {
			exponent[i] = exp[i];
			coefficient[i] = coeff[i];
		}
	}

	//Setter function
	void setPolynomial(int num, int* exp, int* coeff) {
		if (coefficient)delete[]coefficient;
		if (exponent)delete[]exponent;
		numTerm = num + 1;
		exponent = new int[numTerm];
		coefficient = new int[numTerm];
		for (int i = 0; i <numTerm; i++) {
			exponent[i] = exp[i];
			coefficient[i] = coeff[i];
		}
	}

	void setPolynomial(int num) {
		if (coefficient)delete[]coefficient;
		if (exponent)delete[]exponent;
		numTerm = num + 1;
		exponent = new int[numTerm];
		coefficient = new int[numTerm];
		for (int i = 0; i < numTerm; i++) {
			exponent[i] = 0;
			coefficient[i] = 0;
		}
	}
	
	// Operator +
    Polynomial operator + (const Polynomial& poly) {
		Polynomial temp;
		if (numTerm == poly.numTerm) {
			temp.setPolynomial(numTerm - 1);
			for (int i = 0; i < temp.numTerm; i++) {
				temp.exponent[i] = exponent[i];
				temp.coefficient[i] = coefficient[i] + poly.coefficient[i];
			}
		}
		else if (numTerm > poly.numTerm) {
			int sub = numTerm - poly.numTerm;
			temp.setPolynomial(numTerm - 1);
			int i = 0, j = 0;
			for ( i = 0; i < temp.numTerm; i++) {
				if (i < sub) {
					temp.exponent[i] = exponent[i];
					temp.coefficient[i] = coefficient[i];
				}
				else {
					temp.exponent[i] = exponent[i];
					temp.coefficient[i] = coefficient[i] + poly.coefficient[j];
					j++;
				}
			}
		}
		else {
			int sub =poly.numTerm-numTerm;
			temp.setPolynomial(poly.numTerm - 1);
			int i = 0, j = 0;
			for (i = 0; i < temp.numTerm; i++) {
				if (i < sub) {
					temp.exponent[i] = poly.exponent[i];
					temp.coefficient[i] = poly.coefficient[i];
				}
				else {
					temp.exponent[i] = poly.exponent[i];
					temp.coefficient[i] = coefficient[j] + poly.coefficient[i];
					j++;
				}
			}
		}
		return temp;
	}

	// Operator -
	Polynomial operator - (const Polynomial& poly) {
		Polynomial temp;
		if (numTerm == poly.numTerm) {
			temp.setPolynomial(numTerm - 1);
			for (int i = 0; i < temp.numTerm; i++) {
				temp.exponent[i] = exponent[i];
				temp.coefficient[i] = coefficient[i] - poly.coefficient[i];
			}
		}
		else if (numTerm > poly.numTerm) {
			int sub = numTerm - poly.numTerm;
			temp.setPolynomial(numTerm - 1);
			int i = 0, j = 0;
			for (i = 0; i < temp.numTerm; i++) {
				if (i < sub) {
					temp.exponent[i] = exponent[i];
					temp.coefficient[i] = coefficient[i];
				}
				else {
					temp.exponent[i] = exponent[i];
					temp.coefficient[i] = coefficient[i] -poly.coefficient[j];
					j++;
				}
			}
		}
		else {
			int sub = poly.numTerm - numTerm;
			temp.setPolynomial(poly.numTerm - 1);
			int i = 0, j = 0;
			for (i = 0; i < temp.numTerm; i++) {
				if (i < sub) {
					temp.exponent[i] = poly.exponent[i];
					temp.coefficient[i] = poly.coefficient[i];
				}
				else {
					temp.exponent[i] = poly.exponent[i];
					temp.coefficient[i] = coefficient[j] - poly.coefficient[i];
					j++;
				}
			}
		}
		return temp;
	}
	
	// Insertion Operator <<
	friend ostream& operator << (ostream& out, const Polynomial& poly) {
		int i;
		for ( i = 0; i < poly.numTerm - 1; i++) {
			if (*(poly.coefficient + i) != 0 && *(poly.coefficient + i) > 0) {
				out << *(poly.coefficient + i) << "x^" << *(poly.exponent + i);
			}
			else if (*(poly.coefficient + i) != 0 && *(poly.coefficient + i) < 0) {
				out << " - " << -1 * *(poly.coefficient + i) << "x^" <<*(poly.exponent + i);
			}
		    if (*(poly.coefficient + i + 1) > 0)
				out << " + ";
		}
		if (*(poly.coefficient + i) != 0 && *(poly.coefficient + i) > 0) {
			out << *(poly.coefficient + i);
		}
		else if (*(poly.coefficient +i) != 0 && *(poly.coefficient +i) < 0) {
			out << " - " << -1 * *(poly.coefficient + i);
		}
		return out;
	}
	~Polynomial() {
		if (numTerm) {
			delete[]exponent;
			delete[]coefficient;
		}
	}
};

// Function to read the coefficients from user 
void polynomialReading(Polynomial& temp) {
	int num; // Variable for number of terms user enter
	cout << "Enter highest power of polynomial epression 1: ";
	cin >> num;
	while (num < 1) {
		cout << "Enter valid exponent: ";
		cin >> num;
	}
	cout << endl;
	int* power = new int[num + 1];
	int* coefficient = new int[num + 1];

	for (int i = 0; i <= num; i++) {
		*(power + i) = num - i;
		cout << "Enter coefficient of x^" << num - i << ": ";
		cin >> *(coefficient + i);
	}
	temp.setPolynomial(num, power, coefficient);
	delete[]power;
	delete[]coefficient;
}

// Main Function
int main() {
	
	Polynomial eq1;
	cout << "Enter details of polynomial expression1: " << endl;
	polynomialReading(eq1);
	cout << "************************************************************************************"
		 << "\npolynomial expression is :  " << eq1
		<<"\n**************************************************************************************" << endl << endl;

	Polynomial eq2;
	cout << "Enter details of polynomial expression2: " << endl;
	polynomialReading(eq2);
	cout << "************************************************************************************"
		<< "\npolynomial expression is :  " << eq2
		<< "\n**************************************************************************************" << endl << endl;

	cout << "\n\nAddition of two polynomials: "
		<< "Expression1 + Expression2 =  " << eq1 + eq2 
		<<"\n***************************************************************************************" << endl<<endl;
	cout << "\n\nSubtraction of two polynomials: "
		<< "Expression1 - Expression2 =  " << eq1 - eq2
		<< "\n***************************************************************************************" << endl;

}