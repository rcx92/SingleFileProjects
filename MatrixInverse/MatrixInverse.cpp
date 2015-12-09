#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

typedef vector<vector<double> > Matrix;

const double EPS = 1e-8;

bool dec(vector<double> &target, const vector<double> &bullet, double rate, int start = 0){
	if(target.size() != bullet.size()) return false;
	for(int i = start; i < target.size(); ++i){
		target[i] -= bullet[i] * rate;
	}
	return true;
}

void divide(vector<double> &target, double rate){
	for(int i = 0; i < target.size(); ++i){
		target[i] /= rate;
	}
}

double GetDeterminantValue(const vector<vector<double> > &matrix){
	vector<vector<double> > a(matrix);
	if(matrix.size() == 0 || matrix[0].size() != matrix.size()) return NAN;
	double rate = 1.0;
	int n = matrix.size();
	for(int i = 0; i < n; ++i){
		int best = i;
		for(int j = i + 1; j < n; ++j){
			if(fabs(a[j][i]) > fabs(a[best][i])) best = j;
		}
		if(best != i) {
			swap(a[i], a[best]);
			rate = -rate;
		}
		if(fabs(a[i][i]) < EPS){
			return 0.0;
		}
		for(int j = i + 1; j < n; ++j){
			dec(a[j], a[i], a[j][i] / a[i][i], i);
		}
	}
	double result = rate;
	for(int i = 0; i < n; ++i) result *= a[i][i];
	return result;
}

bool GetInverse(const vector<vector<double> > &matrix, vector<vector<double> > &result){
	vector<vector<double> > a(matrix);
	if(matrix.size() == 0 || matrix[0].size() != matrix.size()) return false;
	int n = matrix[0].size();
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(j == i) a[i].push_back(1.0); else a[i].push_back(0.0);
		}
	}
	for(int i = 0; i < n; ++i){
		int best = i;
		for(int j = i + 1; j < n; ++j){
			if(fabs(a[j][i]) > fabs(a[best][i])) best = j;
		}
		if(best != i) swap(a[i], a[best]);
		if(fabs(a[i][i]) < EPS){
			return false;
		}
		divide(a[i], a[i][i]);
		for(int j = i + 1; j < n; ++j){
			dec(a[j], a[i], a[j][i], i);
		}
		
	}
	for(int i = n - 1; i >= 0; --i){
		for(int j = i + 1; j < n; ++j){
			dec(a[i], a[j], a[i][j], j);
		}
	}
	result.clear();
	result.resize(n, vector<double>());
	for(int i = 0; i < n; ++i){
		for(int j = n; j < n * 2; ++j){
			result[i].push_back(a[i][j]);
		}
	}
	return true;
}

double printDouble(double x){
	if(fabs(x) < EPS) return 0.0;
	return x;
}

int main(){
	ios::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<vector<double> > v;
	for(int i = 0; i < n; ++i){
		v.push_back(vector<double>());
		for(int j = 0; j < n; ++j){
			double x;
			cin >> x;
			v.back().push_back(x);
		}
	}
	vector<vector<double> > result;
	printf("%.2f\n", printDouble(GetDeterminantValue(v)));
	if(GetInverse(v, result)){
		for(int i = 0; i < result.size(); ++i){
			for(int j = 0; j < result[i].size(); ++j){
				if(j > 0) printf(" ");
				printf("%.2f", printDouble(result[i][j]));
				if(j + 1 == result[i].size()) printf("\n");
			}
		}
	} else {
		printf("No Inverse Matrix!\n");
	}
	return 0;
	
}
