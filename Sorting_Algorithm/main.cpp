#include <iostream> // input/output stream
#include <vector> // vector container
#include <algorithm> // algorithms like sort, swap, etc.
#include <chrono> // time measurement
#include <random> // random number generation
#include <iomanip> // input/output manipulators

using namespace std; // using standard namespace to avoid writing std:: before standard library functions
using namespace chrono; // using chrono namespace to avoid writing chrono:: before time measurement functions

// Bubble Sort implementation
void bubbleSort(vector<int>& arr) { // pass by reference to avoid copying the vector
	int n = arr.size(); // get the size of the vector
	for (int i = 0; i < n - 1; i++) { // iterate through the vector, n-1 times
		for (int j = 0; j < n - i - 1; j++) { // iterate through the vector, n-i-1 times
			if (arr[j] > arr[j + 1]) { // if the current element is greater than the next element
				std::swap(arr[j], arr[j + 1]); // swap the elements
            }
        }
    }
}

// Quick Sort implementation, partition function
int partition(vector<int>& arr, int low, int high) { // partition function to partition the array
	int pivot = arr[high]; // pivot element is the last element
	int i = low - 1; // index of smaller element

	for (int j = low; j < high; j++) { // iterate through the array
		if (arr[j] <= pivot) { // if the current element is less than or equal to the pivot element
			i++; // increment the index of smaller element
			swap(arr[i], arr[j]); // swap the elements
        }
    }
	swap(arr[i + 1], arr[high]); // swap the elements
	return i + 1; // return the index of the pivot element
}

// Quick Sort implementation, recursive function
void quickSort(vector<int>& arr, int low, int high) { // recursive function to sort the array
	if (low < high) { // if the low index is less than the high index
		int pi = partition(arr, low, high); // partition the array and get the index of the pivot element
		quickSort(arr, low, pi - 1); // recursively sort the left subarray
		quickSort(arr, pi + 1, high); // recursively sort the right subarray
    }
}

// Function to generate random array
vector<int> generateRandomArray(int size) { // function to generate a random array of given size
	vector<int> arr(size); // create a vector of given size
	random_device rd; // obtain a random number from hardware
	mt19937 gen(rd()); // seed the generator
	uniform_int_distribution<> dis(1, 1000000); // define the range

	for (int i = 0; i < size; i++) { // iterate through the vector
		arr[i] = dis(gen); // generate a random number and assign it to the current element
    }
	return arr; // return the generated array
}

// Function to measure sorting time
template <typename Func> // template function to measure sorting time
double measureSortingTime(Func sortFunc, vector<int>& arr) { // function to measure the sorting time of a given sorting function
	auto start = high_resolution_clock::now(); // get the current time
	sortFunc(arr); // call the sorting function
	auto end = high_resolution_clock::now(); // get the current time
	return duration_cast<microseconds>(end - start).count() / 1000.0; // return the time taken to sort the array in milliseconds
}

// Main function
int main() { // main function
	vector<int> sizes = { 100, 1000, 10000, 100000 }; // vector of sizes to test

	cout << setw(10) << "Size" << setw(15) << "Bubble Sort" << setw(15) << "Quick Sort" << setw(15) << "Sort" << endl; // print the header

	for (int size : sizes) { // iterate through the sizes
		vector<int> arr = generateRandomArray(size); // generate a random array of given size
		vector<int> arr_copy1 = arr; // create a copy of the array
		vector<int> arr_copy2 = arr; //	create another copy of the array

		double bubbleSortTime = measureSortingTime([](vector<int>& a) { bubbleSort(a); }, arr); // measure the time taken to sort the array using bubble sort

		double quickSortTime = measureSortingTime([](vector<int>& a) { quickSort(a, 0, a.size() - 1); }, arr_copy1); // measure the time taken to sort the array using quick sort

		double stdSortTime = measureSortingTime([](vector<int>& a) { sort(a.begin(), a.end()); }, arr_copy2); // measure the time taken to sort the array using std::sort

		cout << setw(10) << size // print the size of the array
			<< setw(15) << fixed << setprecision(3) << bubbleSortTime // print the time taken to sort the array using bubble sort
			<< setw(15) << fixed << setprecision(3) << quickSortTime // print the time taken to sort the array using quick sort
			<< setw(15) << fixed << setprecision(3) << stdSortTime << endl; // print the time taken to sort the array using std::sort
    }

	return 0; // return 0 to indicate successful completion
}