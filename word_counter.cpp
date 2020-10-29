#include <algorithm> // for find()
#include <fstream> // for file handling
#include <iostream>
#include <map> // for maps
#include <string>
#include <vector> // for vectors

// Example text file path -> /Users/aysilsimge/Word_Counter/file.txt

using namespace std;

// MARK: Functions

void wordCount(string str); // This function counts the frequency of words and outputs count of total words and the most 5 used words to the user.
void sortWords(map<string, int> frequency_of_words); // Sort words in increasing order and return it
multimap<int, string> invert(map<string, int> & mymap); // Function to convert a map<key,value> to a multimap<value,key>
void calculateReadingTime(int word_count); // This function calculates the estimating reading time

int main() {
    string directory; // Input: Directory of the txt file
    string input_str = ""; //The text in the file
    int char_count; // Character count
    int char_count_wo_ws; // Character count without whitespaces
    int paragraph_count = 0;

    cout << "\033[2J\033[1;1H"; // Clears the terminal
    cout << "------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t  WELCOME!" << endl;
    cout << "\t\t\t\tWORD COUNTER" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
    
    // Input for the user enter the directory of the file
    cout << "Please enter your file's directory: ";
    cin >> directory;

    ifstream input_file;
    
    input_file.open(directory); // open file

    string line; 
    while ( getline (input_file,line) ) // Read file line by line
    {
        // Save file content as a string
        input_str += line;
        input_str += "\n";

    // Calculate the paragraph count
      if (!(line == "")) {
          paragraph_count += 1;
      }
    }

    input_file.close(); // Close the file

    char_count = input_str.size() - paragraph_count; // Calculate the all characters count

    // Calculate characters count without whitespaces
    string input_str_wo_ws = input_str;
    input_str_wo_ws.erase(remove(input_str_wo_ws.begin(), input_str_wo_ws.end(), ' '), input_str_wo_ws.end());
    input_str_wo_ws.erase(remove(input_str_wo_ws.begin(), input_str_wo_ws.end(), '\n'), input_str_wo_ws.end());
    char_count_wo_ws = input_str_wo_ws.size();

    // Output: Show to user Paragraph, Characters and Characters Without Whitespaces Count
    //cout << input_str << endl;
    cout << "\tPARAGRAPHS: " << paragraph_count << endl;
    cout << "\tCHARACTERS: " << char_count << endl;
    cout << "\tCHARACTERS WITHOUT WHITESPACES: " << char_count_wo_ws << endl;

    wordCount(input_str); // Print out how many words in text and the frequency of words
}

// This function creates an words map consists of words and words' frquency and count words.
void wordCount(string str) {
    int word_count = 0; // Count of words
    string new_word = "";
    map<string, int> words_and_frequency; // map value for store how many times which word is used
    vector<char> punctuation_marks = {'!', '.', ',', '?', '"'}; // vector consists of punctuation marks

    // Count how many words in text and it's frequency per word.
    for (int i = 0; i < str.size(); i++) {
        if (!(str[i] == ' ') && !(str[i] == '\n')) { // str[i] == ' ' means the word is finished
            vector<char>::iterator it = find(punctuation_marks.begin(), punctuation_marks.end(), str[i]); // Check if the letter is a punctuation mark
            if (it == punctuation_marks.end()) { // if letter is not a punctiation mark then add letter to new_word string.
                new_word += tolower(str[i]);
            }
        } else { // if the word is completed then add it to the words_and_frequency value
        // Check the word is already in map or not
            if (words_and_frequency[new_word]) {
                words_and_frequency[new_word] += 1;
            } else {
                words_and_frequency[new_word] = 1;
            }
            new_word = ""; // Reset the new_word
            word_count += 1; // increase word count by 1
        }
    }

    cout << "\tWORDS: " << word_count << endl; // Output word count

    sortWords(words_and_frequency); // Sort words_and_frequency and print out top 5 used words.

    calculateReadingTime(word_count); // Calculates and prints out the estimating reading time
}

void sortWords(map<string, int> frequency_of_words) {
    multimap<int, string> words_frequency_sorted = invert(frequency_of_words); // invert frequency_of_words using the invert function

    cout << "\tMOST 5 USED WORDS: " << endl;

    multimap<int, string> :: reverse_iterator iter; // Create a map reverse iterator
    for (iter=words_frequency_sorted.rbegin(); iter!=next(words_frequency_sorted.rbegin(), 5); iter++) // Show first 5 elements of words_frequency_sorted
    {
        // Printing the second value first because the order of (key,value) is reversed in the multimap
        cout << "\t\t" << iter->second << ": " << iter->first << endl; 
    }

    // This commented code prints all words in the text
    // for (iter=sorted_words.rbegin(); iter!=sorted_words.rend(); iter++) 
    // {
    //     // printing the second value first because the 
    //     // order of (key,value) is reversed in the multimap
    //     cout << iter->second << ": " << iter->first << endl; 
    // }
}

/*
    This function converts map<string, int> to a multimap<int, string>. Main reasons;
    1. Convert <string, int> to <int, string> to sort the map by it's keys
    2. Convert map to multimap to use same keys in the list (In map every key must be unique)
*/
multimap<int, string> invert(map<string, int> & mymap) {
	multimap<int, string> multiMap;

	map<string, int> :: iterator it;
	for (it=mymap.begin(); it!=mymap.end(); it++) 
	{
		multiMap.insert(make_pair(it->second, it->first));
	}

	return multiMap;
}

// Calculate the estimated reading time
void calculateReadingTime(int word_count) {
    double words_per_minute = 200; // Average people reads between 200-250 words per minute
    double minutes = double(word_count) / words_per_minute; // minutes to read
    double seconds = minutes - floor(minutes); // seconds to read

    // Output the reading time
    cout << "\tESTIMATED READING TIME: ";
    cout << floor(minutes) << " minutes " << floor(seconds*100) << " seconds" << endl;
}


// for (const auto& x : words_and_frequency) {
//     cout << x.first << ": " << x.second << "\n";
// }
//cout << "The map, sorted by value is: " << endl;
// multimap<int, string> :: reverse_iterator iter;
// for (iter=newmap.rbegin(); iter!=newmap.rend(); iter++) 
// {
// 	// printing the second value first because the 
// 	// order of (key,value) is reversed in the multimap
// 	cout << iter->second << ": " << iter->first << endl; 
// }


