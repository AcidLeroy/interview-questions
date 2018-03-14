//given a string S = "123" and an integer K = 1;  remove K digits from S, so the remaining string is the smallest (in terms of an integer)
// leading zeros will be removed for free 
// Example:  S = "123"  K = 1;   return "12"
// Example:  S = "465"  K = 1;   return "45"
// Example:  S = "1023" K = 1;   return "23"
// Example:  S = "12300";    K = 1;  return "1200"
// Example:  S = "123001";    K = 1;  return "12001"

#include <iostream> 
#include <vector> 
#include <string> 
#include <algorithm> 

using namespace std; 

string RemoveK(string &input, int K) {
	if (K >= input.size()) {
		return "0";
	}
	bool flag = false;
	vector<string> my_str; 
	string temp = ""; 
	for (auto &i : input)  {
		//cout << "i = " << i <<endl;
		int v = i -'0';
		if (i == '0') {
			temp += i; 
			flag = true;  
		}else {
			temp += i; 
			my_str.push_back(temp) ; 
			temp = ""; 
		}
	} 

	auto my_sort = [=](string a, string b) {
		int v = stoi(a);
		int w = stoi(b);
		return v < w; 
	};

	// Copy vector
	auto original_order = my_str; 
	for (auto &i : original_order) {
		cout << "i = " << i << endl;
	} 

	// Sort my_str
	sort(my_str.begin(), my_str.end(), my_sort);    

	// Copy last K elements
	vector<string> k_elements(K); 
	copy(my_str.begin()+my_str.size() -K, my_str.end(), k_elements.begin());

	// Copy everything expecpt for k_elements
	string result ="";  
	for(int i = 0; i < original_order.size(); i++) {
		auto it = find(k_elements.begin(), k_elements.end(), original_order[i]); 
		// Only add to the result if it is not contained in k_elements
		if (it == k_elements.end()) {
			result += original_order[i]; 
		} 
	}

	return result;  
}

class KHelper {
	public: 
		string input; 
		int k; 
		string expected_output; 
}; 

int main() {
	// Example:  S = "123"  K = 1;   return "12"
	// Example:  S = "465"  K = 1;   return "45"
	// Example:  S = "1023" K = 1;   return "23"
	// Example:  S = "12300";    K = 1;  return "1200"
	// Example:  S = "123001";    K = 1;  return "12001"
	
	string input = "1023";
	int k = 1;

	vector<KHelper> test; 
	test.push_back(KHelper{"1023", 1, "12"}); 
	test.push_back(KHelper{"123", 1, "12"}); 
	test.push_back(KHelper{"465", 1, "45"}); 
	test.push_back(KHelper{"12300", 1, "1200"}); 
	test.push_back(KHelper{"123001", 1, "12001"}); 

	for (auto &t : test) {
		cout << "input = " << t.input << endl;
		string res = RemoveK(t.input, t.k);
		cout << "Expected = " << t.expected_output << " got " << res << endl;

	} 

}
