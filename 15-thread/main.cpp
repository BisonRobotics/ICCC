#include <iostream>
#include <thread>
#include <vector>
#include <stdio.h>

using namespace std;

void my_threaded_func(int j) {
	for(int i = 0; i < 10; i++) {
		cout << "  " << j << endl;
	}
}

void other_threaded_func(double d) {
	d *= d;
	d *= d;
	
	printf(" result of other_threaded_func: %lf\n", d);

}

int main(int argc, char* argv[]) {

	// place to store thread objects
	vector<thread> thread_vector;

	for(int k = 0; k < 6; k++) {
		thread_vector.push_back(thread(my_threaded_func, k));
		thread_vector.push_back(thread(other_threaded_func, (double)k));
	}

	for(char& t : thread_vector)
		t.join();

    return 0;
}

