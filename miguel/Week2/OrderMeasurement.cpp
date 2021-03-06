// OrderMeasurement.cpp: Shows the relative runtime for an algorithm of order n, n-squared, and n-cubed.
//                       The data is written to files and is plotted using plot.ly, found at:
//                       https://plot.ly/create/#/
//

#include <stdio.h>
#include <windows.h>
#include <vector>

void doOrderOne();
void doOrderTwo();
void doOrderThree();
void doBinarySearch();

int main()
{
	int orderOfMagnitude;
	printf("Enter the order of magnitude (1-4): ");
	scanf("%d", &orderOfMagnitude);
	switch (orderOfMagnitude) {
	case 1:
		doOrderOne();
		break;
	case 2:
		doOrderTwo();
		break;
	case 3:
		doOrderThree();
		break;
	case 4:
		doBinarySearch();
		break;
	default:
		printf("Invalid input. Terminating...\n");
		return -1;
	}

    return 0;
}

void doOrderOne() {//O(n)
	int n;
	double startTime, endTime, totalTime;
	FILE *fp = fopen("orderOne.txt", "w");
	for (n = 0; n <= 80; ++n) {
		startTime = GetTickCount();//milliseconds, 2 operations
		for (int i = 0; i < n; ++i) {//i=0, 1 operation
			//3 operations per loop
			Sleep(10);//10 milliseconds
		}
		endTime = GetTickCount();//milliseconds, 2 operations
		totalTime = (endTime - startTime)/1000.0;//convert to seconds, 3 operations
		printf("%3d %lf\n", n, totalTime);
		fprintf(fp, "%lf,\n", totalTime);//CSV format for plot.ly
		fflush(fp);
	}//T(n) = 3n + 8;
	//O(n)
	fclose(fp);
}

void doOrderTwo() {//O(n-squared)
	int n;
	double startTime, endTime, totalTime;
	FILE *fp = fopen("orderTwo.txt", "w");
	for (n = 0; n <= 30; ++n) {
		startTime = GetTickCount();//milliseconds, 2 constant operations
		for (int i = 0; i < n; ++i) {//1 constant operation, 2 operations per n
			for (int j = 0; j < n; ++j) {//1 operation per n, 2 operations per n^2
				Sleep(1);//milliseconds, 1 operation per n^2
			}
		}
		endTime = GetTickCount();//milliseconds, 2 constant operations
		totalTime = (endTime - startTime) / 1000.0;//convert to seconds, 3 operations
		printf("%3d %lf\n", n, totalTime);
		fprintf(fp, "%lf,\n", totalTime);//CSV format for plot.ly
		fflush(fp);
	}//T(n) = 3n^2 + 3n + 8;
	//O(n^2)
	fclose(fp);
}


void doOrderThree() {//O(n-cubed)
	int n;
	double startTime, endTime, totalTime;
	FILE *fp = fopen("orderThree.txt", "w");
	for (n = 0; n <= 15; ++n) {
		startTime = GetTickCount();//milliseconds
		for (int i = 0; i < 5*n; ++i) {
			for (int j = 0; j < n; ++j) {
				for (int k = 0; k < 5*n; ++k) {
					Sleep(1);//milliseconds
				}
			}
		}
		endTime = GetTickCount();//milliseconds
		totalTime = (endTime - startTime) / 1000.0;//convert to seconds
		printf("%3d %lf\n", n, totalTime);
		fprintf(fp, "%lf,\n", totalTime);//CSV format for plot.ly
		fflush(fp);
	}
	fclose(fp);
}

void doBinarySearch() {
	int n;
	int iterations;
	int intArray[100000], key;
	FILE *fp = fopen("binarySearch.txt", "w");
	for (n = 0; n < 100000; ++n) {//Initialize the array
		intArray[n] = n;
	}
	for (n = 1; n < 100000; ++n) {
		iterations = 0;//a statistic, don't count
    	int index = -1;//1 operation
	    int low = 0;//1 operation
		int high = n - 1;//2 operations
	    int mid=0;//1 operation
		key = n-1;//Will always be at the lowest leaf of the tree, 2 operations
		while (low <= high && index == -1) {//1 constant operation, 2 operations per n
			++iterations;//a statistic, don't count
		    mid = (low + high) / 2;//3 operations per n
			if (key < intArray[mid])//1 operation per n
			    high = mid - 1;//2 operations per n
		    else if (key > intArray[mid])//1 operation per n
			    low = mid + 1;//2 operations per n
		    else
			    index = mid;//1 constant operation
	    }/*while*/
		printf("n:%d iterations:%d index:%d\n", n, iterations, index);
		fprintf(fp, "n:%d iterations:%d index:%d\n", n, iterations, index);
	}
	fclose(fp);
}
