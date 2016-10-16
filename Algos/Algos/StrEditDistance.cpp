#include <iostream>
using namespace std;

long recurseAndReturnMinVal(string str1, string str2, long ** dp_arr, long indx1, long indx2) {
	long val0 = LONG_MAX, val1 = LONG_MAX, val2 = LONG_MAX, val_eq = LONG_MAX, val_ineq = LONG_MAX;

	if (indx1 == -1) {
		return 1 + indx2;
	}
	if (indx2 == -1) {
		return 1 + indx1;
	}

	if (dp_arr[indx1][indx2] != -1) {
		return dp_arr[indx1][indx2];
	}

	if (str1[indx1] == str2[indx2]) {
		val_eq = recurseAndReturnMinVal(str1, str2, dp_arr, indx1 - 1, indx2 - 1);
	}
	else {
		val0 = 1 + recurseAndReturnMinVal(str1, str2, dp_arr, indx1 - 1, indx2 - 1);
		val1 = 1 + recurseAndReturnMinVal(str1, str2, dp_arr, indx1, indx2 - 1);
		val2 = 1 + recurseAndReturnMinVal(str1, str2, dp_arr, indx1 - 1, indx2);

		val_ineq = (val1 < val2) ? val1 : val2;
		val_ineq = (val_ineq < val0) ? val_ineq : val0; 
	}

	dp_arr[indx1][indx2] = (val_eq < val_ineq) ? val_eq : val_ineq;

	return dp_arr[indx1][indx2];
}

long editDistance(string str1, string str2) {
	long str1Len = str1.length();
	long str2Len = str2.length();

	long **dp_arr = new long*[str1Len];
	for (long i = 0; i < str1Len; i++)
		dp_arr[i] = new long[str2Len];

	for (long i = 0; i < str1Len; i++)
		for (long j = 0; j < str2Len; j++)
			dp_arr[i][j] = -1;

	recurseAndReturnMinVal(str1, str2, dp_arr, str1Len - 1, str2Len - 1);
	long return_val = dp_arr[str1Len - 1][str2Len - 1];

	for (long i = 0; i < str1Len; i++) {
		for (long j = 0; j < str2Len; j++) {
			if (dp_arr[i][j] == -1) {
				cout << "-" << "\t";
				dp_arr[i][j] = LONG_MAX;
			}
			else {
				cout << dp_arr[i][j] << "\t";
			}
		}
		cout << endl;
	}
	cout << endl << "Edit path:" << endl;

	long trace_indx1 = str1Len - 1;
	long trace_indx2 = str2Len - 1;

	while (trace_indx1 > 0 && trace_indx2 > 0) {

		long curr = dp_arr[trace_indx1][trace_indx2];
		long top_left = dp_arr[trace_indx1 - 1][trace_indx2 - 1];
		long top = dp_arr[trace_indx1 - 1][trace_indx2];
		long left = dp_arr[trace_indx1][trace_indx2 - 1];
		
		if (top_left <= top && top_left <= left) {
			if (top_left < curr) {
				cout << "Replace a character" << endl;
			}
			else {
				cout << "Match" << endl;
			}
			trace_indx1--;
			trace_indx2--;
		}
		else if (left < top) {
			cout << "Remove a character from str2" << endl;
			trace_indx2--;
		}
		else {
			cout << "Remove a character from str1" << endl;
			trace_indx1--;
		}
	}
	if (trace_indx1 > 0) {
		cout << "remove " << dp_arr[trace_indx1][trace_indx2] << " characters from str1" << endl;
	}
	else if (trace_indx2 > 0) {
		cout << "remove " << dp_arr[trace_indx1][trace_indx2] << " characters from str2" << endl;
	}
	else if (dp_arr[0][0] == 1) {
		cout << "Replace a charater" << endl;
	}
	else {
		cout << "Match" << endl;
	}



	for (int i = 0; i < str1Len; i++) {
		delete[] dp_arr[i];
	}
	delete[] dp_arr;

	return return_val;
}

void main() {
	string str1 = "tooloi ikis ";
	string str2 = "_______tolaoo iik ";

	cout << editDistance(str1, str2);
	getchar();
}