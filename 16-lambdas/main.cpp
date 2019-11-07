#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

using namespace std;

// lambda syntax
auto l = []() -> void {
	
};

bool compare_ints(int lhs, int rhs) {
	return lhs > rhs;
}

int main(int argc, char* argv[]) {
	
	srand(time(NULL));
	vector<int> v;

	for(int i = 0; i < 1024*10; i++) {
		v.push_back(rand());
	}

	auto print_vector = [](vector<int>& v) -> void {
		cout << "===================================\n";		
		for(int i = 0; i < 15; i++)
			cout << v[i] << endl;
	};	

	print_vector(v);

	// by default, sort goes in ascending order
	sort(v.begin(), v.end());
	print_vector(v);

	// sort the vector in descending order with a lambda
	sort(
		v.begin(), 
		v.end(), 
		[](int lhs, int rhs) -> bool {
			return lhs > rhs;
		}
	);

	print_vector(v);
	long int sum;

	// create a thread to sum the elements together
	thread mythread(
		[&v,&sum]() {
			long int total = 0;
			for(auto i : v) {
				total += i;			
			}
			sum = total;
		}
	);

	cout << "Hello World" << endl;

	mythread.join();
	cout << "Sum: " << sum << endl;

	return 0;
}

