#include <iostream>
#include <fstream>
#include <sstream>
#include <string>       // provides string class
#include <cctype>       // provides isalpha() and tolower()
#include <vector>

using namespace std;

// The following function should be moved into your skiplist.cc file when you
// write that.  It implements the random bit generation.
#include <ctime>                // for time()
#include <cstdlib>              // for rand(), srand(), and RAND_MAX

int randBit(void) {             // return a "random" bit
    static int bitsUpperBd=0;
    static int bits;              // store bits returned by rand()
    if( bitsUpperBd == 0 ) {      // refresh store when empty
        bitsUpperBd = RAND_MAX;
        bits = rand();
    }
    int b = bits & 1;
    bits >>= 1;
    bitsUpperBd >>= 1;
    return b;
}


// Remove all characters except letters (A-Z,a-z) from line,
// except keep '-' or '\'' if they are between letters.
void lowercaseWords(string & line) {
    for( string::iterator it = line.begin(); it != line.end(); ++it ) {
        if( !isalpha(*it) ) {
            if( (*it != '-' && *it != '\'') ||
               it == line.begin() || it+1 == line.end() ||
               !isalpha(*(it-1)) || !isalpha(*(it+1)) ) {
                *it = ' ';
            }
        } else {
            *it = tolower(*it);
        }
    }
}

/*
 Mile stone 1 Array as an structure
 */

//(a) Look up (find) the entry for that word in a data structure that you implement called
//the index structure.
//(b) If it is not found, insert a new entry.
//(c) Update the entry to reflect the new occurrence of the word.

struct word {
    string character;
    int count;
    vector<int> pageList;
} ;


vector<word> index_array;


//compare if word1< word2
bool compare(string word1, string word2){
    
    int word1_length =  word1.length();
    int word2_length =  word2.length();
    
    //parse the strign into char array to compare each char
    char *word1_charArr=new char[word1_length+1];
    char *word2_charArr=new char[word2_length+1];
    
    //pick the one with smaller length as compare base
    //word1 < word2:
    //  -ai< bi where ai denote a char at i position in word1 and bi denote a char at
    //  i position in word2
    //  -ai < bi for all char in the smaller words. Then smaller word < larger word
    if(word1_length <= word2_length){
        for(int index=0; index< word1_length+1; index++){
            int asciiW1 = word1_charArr[index];
            int asciiW2 = word2_charArr[index];
            if(asciiW1 <= asciiW2){
            }else{
                return false;
            }
            return true;
        }
    }else{
        for(int index=0; index< word2_length+1; index++){
            int asciiW1 = word1_charArr[index];
            int asciiW2 = word2_charArr[index];
            if(asciiW2 > asciiW1){
                return true;
            }
            return false;
        }
    }
    
    return false;
}

//employed linear search on index_array to find the key
word find(vector<word> index_array, string key){
    word *to_return;
    for(int index=0; index<index_array.size(); index++) {
        if(index_array[index].character.compare(key)){
            to_return = &index_array[index];
            return *to_return;
        }
    }
    
    return *to_return;
}

//insert an element to index array
void insert(vector<word> index_array, string key,int page){
    vector<int> pageList;
    pageList.push_back(page);
    word key_word = {key, 1, pageList};
    
    //check if the word on the list
    //yes increment the count and append page number if not exist
    //no insert the element
    for(int index =0; index< index_array.size(); index++){
        if (index_array[index].character.compare(key)) {
            index_array[index].count++;
            index_array[index].pageList.push_back(page);
            return;
        }
        else if(compare(key, index_array[index].character)){
                //insert and return
            
        }
    }

}





void print(ostream & output, string & word) {
    output << word << endl;
}

int main(int argc, char *argv[]) {
    
    //test case for compare
    cout<<compare("ab","ab")<<"\n";
    cout<<compare("ab","a")<<"\n";
    cout<<compare("a","ab")<<"\n";
    cout<<compare("ab","abc")<<"\n";

    
//    if( argc != 3 ) {
//        cerr << "Usage: " << argv[0] << " book.txt index.txt" << endl;
//        exit(1);
//    }
//    
//    ifstream fin;
//    fin.open(argv[1]);
//    if( !fin.is_open() ) {
//        cerr << "Unable to open " << argv[1] << endl;
//        exit(2);
//    }
//    
//    ofstream fout;
//    fout.open(argv[2]);
//    if( !fout.is_open() ) {
//        cerr << "Unable to open " << argv[2] << endl;
//        exit(3);
//    }
//    
//    string line, word;
//    while( !fin.eof() ) {
//        getline(fin,line);
//        lowercaseWords(line);
//        istringstream iss(line, istringstream::in);
//        while( iss >> word ) {
//            print(fout, word);
//        }
//    }
}
