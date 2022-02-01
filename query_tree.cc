//Weichao Lin
// Main file for Part 2.1 of Homework 3.

#include "avl_tree.h"
// You will have to add #include "sequence_map.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
// empty.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
// Code for running Part2.1
// Open file
ifstream input;
input.open(db_filename);
if (!input) { //test if file is openable
    cout << "can't open file" << endl;
}

string db_line;

if (db_filename == "rebase210.txt") {
    //delete the header of the file
    for (int i = 0; i < 10; ++i) {
      getline(input, db_line);
    }

    // Start to set and store the sequence itself
    while(getline(input, db_line)) {
      if (db_line.empty()) {
        break;
      }

      stringstream s(db_line);
      string enzAcro;
      getline(s, enzAcro, '/'); // Store enzyme only

      string recSeq;
      while(getline(s, recSeq, '/')) { // Store recognition sequence
        if (recSeq != "") { // If the recognition sequence is NOT empty
          SequenceMap tempSequenceMap(recSeq, enzAcro);
          a_tree.insert(tempSequenceMap);
        }    
      }
    }
}

if (db_filename == "sequences.txt") { //file contains only sequences
    // Start to set and store the sequence itself
    while(getline(input, db_line)) {
      SequenceMap tempSequenceMap(db_line);
      a_tree.insert(tempSequenceMap);
    }
}

input.close();

//later

// Take in sequences from user
string userSequence;
while (getline(cin, userSequence)) {
    if (!a_tree.contains(userSequence)) {
        cout << "Not Found" << endl;
      }
    else { // Find sequence and print out the enzyme acronym
        a_tree.search(userSequence);
      }  
    }

// You can use public functions of TreeType. For example:
//a_tree.insert(10);
//a_tree.printTree();

} // QueryTree

} // namespace

int
main(int argc, char **argv) {
if (argc != 2) {
    cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
    return 0;
}
const string dbx_filename(argv[1]);
cout << "Input filename is " << dbx_filename << endl;
// Note that you will replace the type AvlTree<int> with AvlTree<SequenceMap>
AvlTree<SequenceMap> a_tree;
QueryTree(dbx_filename, a_tree);
return 0;
}
