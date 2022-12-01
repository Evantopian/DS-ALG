#include <iostream>
#include <vector>
using namespace std;


class SequenceMap
{
public:

    // Big Five.
    SequenceMap() = default;
  	// Copy-constructor.
    SequenceMap(const SequenceMap &rhs) = default;
  	// Copy-assignment. 
    SequenceMap& operator=(const SequenceMap &rhs) = default;
  	// Move-constructor. 
    SequenceMap(SequenceMap &&rhs) = default;
  	// Move-assignment.
    SequenceMap& operator=(SequenceMap &&rhs) = default;
    ~SequenceMap() = default;


    // one param constructor
    SequenceMap(const string &a_rec_seq) : recognition_sequence_(a_rec_seq) {};

    // two parameter constructor.
    SequenceMap(const string &a_rec_seq, const string &an_enz_acro) 
    : recognition_sequence_(a_rec_seq){
        enzyme_acronymns_.push_back(an_enz_acro);
    }



    // >, < operator overloads for string comparisons
    bool operator<(const SequenceMap &rhs) const{
        return (recognition_sequence_ < rhs.recognition_sequence_);
    }

    bool operator>(const SequenceMap &rhs) const{
        return (recognition_sequence_ > rhs.recognition_sequence_);
    }



    // Merge function:
    // appends none duplicated elements given another sequence.
    void Merge(const SequenceMap &other_sequence){
        for (auto it : other_sequence.enzyme_acronymns_)
            if (find(enzyme_acronymns_, it)) enzyme_acronymns_.push_back(it);
    }

    // helper function for finding elements in vectors.

    bool find(vector<string> &v, string s){
        for (auto it : v) 
            if (s == it) return false;
        return true;
    }

    // accessors 
    string get_reco_seq() const{
        return recognition_sequence_;
    }

    vector<string> get_enz_acro() const{
        return enzyme_acronymns_;
    }


        
    // << ostream operator overload
    friend ostream& operator<<(ostream& os, const SequenceMap & seq){
        const SequenceMap *pSeq = &seq;
        if (pSeq == nullptr) return os << "Not Found\n"; 

        for (size_t i = 0; i < seq.enzyme_acronymns_.size(); ++i){
            os << seq.enzyme_acronymns_[i];
            os << (i+1 > seq.enzyme_acronymns_.size() ? "" : " ");
        }
        return os << "\n";
    }

    // >> istream operator overload
    friend istream &operator>>(istream &in, SequenceMap &seq){
        string line;
        

        return in;
    }


private:
    string recognition_sequence_;
    
    // vector containing ancronymns for enzymes.
    vector<string> enzyme_acronymns_;
};