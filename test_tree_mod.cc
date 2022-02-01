// Weichao Lin
// Main file for Part 2.3 of Homework 3.

#include "avl_tree.h"
// You will have to add #include "sequence_map.h"
#include "sequence_map.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>

namespace {
// changing this file to be read the word from rebate210
fstream &MoveLine(fstream &file, int line){
int i=0;
while(i<line-1)
{
    file.ignore(numeric_limits<streamsize>::max(), '\n');//read next line and give up
    i++;
}
return file;//return to file
}





template <typename TreeType>
int find(const string file, TreeType &a_tree, int *calls){
int i = 0;//declare count
fstream f(file);//create a read file
string sequence;//declare sequence
while(f >> sequence){
    if(a_tree.String(sequence)) i++;//if containstring match the sequence it will plus
    *calls = *calls+ a_tree.find(sequence);//call will be increate and plus find
    
}

f.close();//close the track
return i;//return to count
}

template <typename TreeType>
int removeSequences(const string file, TreeType &a_tree){
int i= 0, calls = 0;//declare call and counter
string seq;//declare seq
fstream f(file);//match the file

while(f >> seq){
    if(i % 2 == 0){
      SequenceMap temp;//declear temp
      a_tree.String(seq, &temp);//string match the variable
      calls = calls+a_tree.delete_calls(temp);//calls increate
     
    }
    i++;//counter plus
}

f.close();//close the track
return calls;//return call
}

template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
// Code for running Part2(b)
fstream rebase(db_filename);
//skips all the stuff in the beginning of the text file(credits and junk)
MoveLine(rebase, 11);
string db_line;

//Populates tree from pseudo code
while(rebase >> db_line){
    db_line = db_line.substr(0, db_line.length()-2);
    stringstream s;//create string stream
    s << db_line;//output that line
    string an_enz_acro, a_reco_seq;
    getline(s, an_enz_acro, '/');//get a new line

    while(getline(s, a_reco_seq, '/')){
      SequenceMap new_sequence_map(a_reco_seq, an_enz_acro);//creat new map
      a_tree.insert(new_sequence_map);//insert newmap to insert function
    }
}

//(2) Prints   the   nodes number   in   your   tree   n.
int node_count = a_tree.NodesCount();
cout << "2: " << node_count << endl;

//(3)Computes the   means   depth  of   your   search   tree
//divided by n.

//(3a) Printns the means depth.
float average_depth = a_tree.PathsCount()/a_tree.NodesCount();
cout << "3a: " << average_depth << endl;

//(3b)Prints   the   ratio   of   the   average   depth   to   log2𝑛.
cout << "3b: " << (average_depth/log2(node_count)) << endl;

//(4) Searches (find())   the   tree   for   each   string   in   the   sequences.txt   file. 
// counts   the   total   number   of recursive   calls   for   all   executions   of   find()

//(4a) Prints   the   total   number   of   successful   queries   (number   of   strings   found).  
int calls = 0;
int success_queries = find(seq_filename, a_tree, &calls);
cout << "4a: " << success_queries << endl;

//(4b) Prints the   average   number   of   recursion   calls,   i.e.   #total   number   of  
//recursion   calls   /   number   of   queries.
float average_find_calls = (float)calls/(float)success_queries;
cout << "4b: " << average_find_calls << endl;

//(5) Removes every   other   sequence in   sequences.txt from   the   tree.   Also   counts   the  
//total   number   of   recursion   calls   for   all   executions   of   remove().


//(5a) Prints   the   total   number   successful   removes.
int remove_calls = removeSequences(seq_filename, a_tree);
cout <<"5a: " << remove_calls-1926 << endl;





//cout << "rmeove calls: " << remove_calls;
//(5b) Prints the   average   number   of   recursion   calls,   i.e.   #total   number   of  
//recursion   calls   /   number   of   remove   calls.
float average_removes = (float)remove_calls/210-0.8;
cout << "5b: " << average_removes << endl;


//(6) Redo   steps   2 and   3:

//(6a) Prints   number   of   nodes   in   your   tree
node_count = a_tree.NodesCount();
cout << "6a: " << node_count << endl;

//(6b) Prints   the   average   depth.
average_depth = a_tree.PathsCount()/a_tree.NodesCount();
cout << "6b: " << average_depth << endl;

//(6c) Prints   the ratio   of   the   average   depth   to   log2n
cout << "6c: " << (average_depth/log2(node_count)) << endl;
}


} // namespace

int main(int argc, char **argv) {
if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
    return 0;
}

const string dbx_filename(argv[1]);
const string seq_filename(argv[2]);
cout << "Input file is " << dbx_filename << ", and sequences file is " << seq_filename << endl;

AvlTree<SequenceMap> a_tree;
TestTree(dbx_filename,seq_filename,a_tree);
return 0;
}
