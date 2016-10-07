#include <iostream>
#include <fstream>
#include <sstream>
#include <string>       // provides string class
#include <cctype>       // provides isalpha() and tolower()
#include <vector>
#include

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
    string spell;
    double price;
} ;


vector<int> index_array;


void print(ostream & output, string & word) {
  output << word << endl;
}

int main(int argc, char *argv[]) {
  if( argc != 3 ) {
    cerr << "Usage: " << argv[0] << " book.txt index.txt" << endl;
    exit(1);
  }

  ifstream fin;
  fin.open(argv[1]);
  if( !fin.is_open() ) {
    cerr << "Unable to open " << argv[1] << endl;
    exit(2);
  }

  ofstream fout;
  fout.open(argv[2]);
  if( !fout.is_open() ) {
    cerr << "Unable to open " << argv[2] << endl;
    exit(3);
  }

  string line, word;
  while( !fin.eof() ) {
    getline(fin,line);
    lowercaseWords(line);
    istringstream iss(line, istringstream::in);
    while( iss >> word ) {
      print(fout, word);
    }
  }
}
