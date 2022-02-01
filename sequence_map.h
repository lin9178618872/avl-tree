#ifndef SEQUENCEMAP_H
#define SEQUENCEMAP_H
#include<iostream>
#include<vector>
#include<string>
#include"dsexceptions.h"
using namespace std;
class SequenceMap{
private:
string recognition_sequence_;
vector<string> enzyme_acronyms_;
public:
//zero-parameter constructor
SequenceMap()=default;
//big five
//copy constructor
SequenceMap(const SequenceMap &rhs)=default;
//copy assignment
SequenceMap& operator=(const SequenceMap &rhs)=default;
//Move-constructor
SequenceMap(SequenceMap &&rhs)=default;
//move assignment
SequenceMap& operator=(SequenceMap &&rhs)=default;
//destructor
~SequenceMap()=default;
//overload the << operator
friend ostream& operator<<(ostream&os,const SequenceMap &rhs);
//merge function
void Merge(const SequenceMap &rhs) const;
//part 1
//constructor
SequenceMap(const string &a_rec_seq, const string &an_enz_acro){
    recognition_sequence_=a_rec_seq;//parameter assigns to private variable
    enzyme_acronyms_.push_back(an_enz_acro);//parameter as a number to be added by private variable
}
//parametered constructor
SequenceMap(const string &a_rec_seq){//parameter assigns to private variable
    recognition_sequence_=a_rec_seq;
    enzyme_acronyms_.push_back("");//empty string as a value to be added by private variable
}
//compare two string using < operator
bool operator<(const SequenceMap &rhs)const{
    return(recognition_sequence_<rhs.recognition_sequence_);
}
//printing out vector using << operator



friend std::ostream &operator<<(std::ostream &out, const SequenceMap &a_SequenceMap){
    out<<a_SequenceMap.recognition_sequence_<<" ";//output a word
    int i=0;
    while(i<a_SequenceMap.enzyme_acronyms_.size())
    {
        out<<a_SequenceMap.enzyme_acronyms_[i]<<" ";//print from low to high
        i++;
    }
    return out;
}





//Merge function
void Merge(const SequenceMap &other_sequence){
    int i=0;
    while(i<other_sequence.enzyme_acronyms_.size())
    {
        enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);//insert every word
        i++;
    }
}






//return the recognition_sequence_
string getRecognitionSequence() const{
    return recognition_sequence_;//return recognition_sequence
}




//print enzyme_acronyms
void printenzyme_acronyms_() const{
    int i=0;
    while(i<enzyme_acronyms_.size())
    {
        cout<<enzyme_acronyms_[i]<<" ";
        i++;
    }
    cout<<"\n";
}







};
#endif

