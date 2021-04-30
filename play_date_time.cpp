// Date and Time

#include <iostream>
#include <chrono>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

// C++ program to find the execution time of code
int main()
{
	auto start = chrono::steady_clock::now();

	// do some stuff here
	// sleep(3);

	auto end = chrono::steady_clock::now();

	cout << "Elapsed time in nanoseconds : "
		<< chrono::duration_cast<chrono::nanoseconds>(end - start).count()
		<< " ns" << endl;

	cout << "Elapsed time in microseconds : "
		<< chrono::duration_cast<chrono::microseconds>(end - start).count()
		<< " Âµs" << endl;

	cout << "Elapsed time in milliseconds : "
		<< chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;

	cout << "Elapsed time in seconds : "
		<< chrono::duration_cast<chrono::seconds>(end - start).count()
		<< " sec";

    auto start = high_resolution_clock::now(); 
  
    // Get ending timepoint 
    auto stop = high_resolution_clock::now(); 
  
    // Get duration. Substart timepoints to  
    // get durarion. To cast it to proper unit 
    // use duration cast method 
    auto duration = duration_cast<microseconds>(stop - start); 
  
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 


	return 0;
}
