20878#include <iostream>
#include <vector> 
#include <string> 
using namespace std;

vector<int> wordBoundaries(const string &input) {
  vector<int> result; 
  int counter=0; 
  string state{"intial"}; 
  // Cases: 
  // Initial
  // We encounter first character since spaces
  // We encouter a space after non space chararcters
  for( auto &s : input) {
    if (state == "initial")  {
      if ( s != ' ') {
        result.push_back(counter); 
        state = "inside_char";
      } 
    } else if (state == "inside_char") {
      if ( s == ' ') {
        result.push_back(counter); 
        state = "initial"; 
      } 
    } 
    counter++; 
  } 
  result.push_back(counter); 
  return result; 
} 

// To execute C++, please define "int main()"
int main() {
  vector<int> expected{3, 8 , 11, 16}; 
  string test("   hello   world"); 
  auto result = wordBoundaries(test); 
  
  cout << "result.size() " << result.size() << endl;
  
  if (result.size() != expected.size()){
    cout << "The sizes are not equal!" << endl; 
    return -1; 
  } 
  
  for (unsigned int i = 0; i < result.size(); ++i) 
  {
    if (expected[i] != result[i]) {
      cout << "Expected " << expected[i] << " but got " << result[i] << " at index = " << i << endl; 
      return -1; 
    } 
  } 
  
  return 0;
}


/* 
Your previous Plain Text content is preserved below:

Write a function that returns a list (or array or slice, etc.) of indices 
representing the beginning and end of each word in a string. 
A word is defined to be a maximum sequence of non-space characters.
The boundaries are "clopen". For example:

wordBoundaries("   hello   world")

returns: 
[3, 8, 11, 16]

 */
