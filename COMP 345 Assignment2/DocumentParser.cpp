#include "DocumentParser.h"

using namespace std; 





void processDocs(string listName){

	vector<string> names;
	int numDoc = 0;               
	int numWords = 0;
	string fileName = "";


	//***********************//
	//   MAIN WORD GATHER    //
	//***********************//

	// Read list of file names.
	ifstream ifs(listName.c_str());
	while (ifs >> fileName){
		names.push_back(fileName);
		cout << fileName << endl;
		numDoc++;
	}
	ifs.close();

	// Read words from each file.
	string word;
	for (int i = 0; i<numDoc; i++){
		ifs.open(names[i].c_str());
		while (ifs >> word){
			bool contains = 0;

			// Remove punctuation and make lower case (e.g. "It's" changes to "its").
			for (string::size_type i = 0, length = word.size(); i < length; ++i){
				if (ispunct(word[i])){
					word.erase(i--, 1);
					length = word.size();
				}
				word[i] = (char)tolower(word[i]);
			}

			// Loop to see if the word is in the base vector: O(n)
			for (vector<string>::const_iterator i = DocumentParser::base.begin(); i != DocumentParser::base.end(); ++i){
				if (*i == word){
					contains = 1;
				}
			}
			if (!contains){
				DocumentParser::base.push_back(word);	// Places words into base vector uniquely.
				numWords++;
			}
		}
		ifs.close();
	}


	//***********************//
	//    VECTOR CREATION    //
	//***********************//

	DocumentParser::base.shrink_to_fit();				// Optimize base vector size to it's contents size. 
	sort(DocumentParser::base.begin(), DocumentParser::base.end());		// Sort the base vector of numWords length into ascending order. 
	names.shrink_to_fit();              // Optimize the filename vector size to it's contents size. 

	// Create vectors of the same size as the base vector. 
	DocumentParser::docCount = numDoc;
	DocumentParser:: wordCount = numWords;

	vector<vector<int>> matrix;         // Create 2D vector matrix.
	matrix.resize(DocumentParser::docCount);                   // Resize matrix to length N (number of documents).

	for (int i = 0; i < DocumentParser::docCount; ++i){		// Creates and NxM matrix (documents x words)
		matrix[i].resize(DocumentParser::wordCount);
	}

	for (int i = 0; i < DocumentParser::docCount; i++){		// Initialize all matrix values to 0.
		for (int j = 0; j < DocumentParser::wordCount; j++){
			matrix[i][j] = 0;
		}
	}


	//***********************//
	//     VECTOR FILLING    //
	//***********************//

	// Read words from each file.
	for (int i = 0; i<numDoc; i++){
		ifs.open(names[i].c_str());
		while (ifs >> word){

			// Remove punctuation and make lower case (e.g. "It's" changes to "its").
			for (string::size_type i = 0, length = word.size(); i < length; ++i){
				if (ispunct(word[i])){
					word.erase(i--, 1);
					length = word.size();
				}
				word[i] = (char)tolower(word[i]);
			}

			for (int j = 0; j < wordCount; ++j){
				if (word == DocumentParser::base[j]){
					matrix[i][j]++;         // Word count for each word of each document.
				}
			}
		}
		ifs.close();
	}








}


vector<int> multiply(vector<int> & aQuery){












}


int DocumentParser::getdocCount(){
	return docCount;
}
