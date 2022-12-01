// --> Evan Huang
/*
    Points2D:
    - A class that represents a sequence of points using a std::array<T, n> pointer
    to other instances where points may be added. 

    Included Members:

    Functions:
    - Zero parameter constructor.
    - Copy constructor and assignment.
    - Move constructor and assignment.
    - Destructor.
    - Overloading operators (>>, <<, +, [])

    Variables:
    - std::array<T, n> *sequence_;
    - size_t size_;

    Sample usuage:
        Points2d<int> a;
        cin >> a; (2 4 5 6 10)
        
        Points2d<int> b{a};
        Points2D<int> d = a+b;
        cout << d; ( (8, 10) (12, 20) );
*/

#ifndef CSCI335_HOMEWORK1_POINTS2D_H_
#define CSCI335_HOMEWORK1_POINTS2D_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {


template<typename Object>
class Points2D {
  public:


    // Zero-parameter constructor.
    // Set size to 0.
    Points2D(size_t len = 0) : size_(len){};


    // Copy-constructor. 
    // if rhs = 0, then set members to null and defaults.
    // else, copy memebers.
    Points2D(const Points2D &rhs){
        if (rhs.size() == 0) {
            size_ = 0;
            sequence_ = nullptr;
        } else { 
            size_ = rhs.size();
            sequence_ = new std::array<Object, 2>[size_];
            // iterate over rhs's sequence to the end and store in this.sequence_
            std::copy(rhs.sequence_, rhs.sequence_+rhs.size_, sequence_);
        }
    }


    // Copy-assignment.
    // deep copy rhs through a tmp variable, copy, then swap
    // return the deep copy.
    Points2D& operator=(const Points2D &rhs){
        Points2D copy = rhs; 
        std::swap(*this, copy);
        return *this;
    }


    // Move-constructor.
    // copy resources from rhs.sequence and rhs.size_ to "this".
    // then delete moved resources.
    Points2D(Points2D &&rhs)
        : sequence_(std::move(rhs.sequence_))
        , size_(std::move(rhs.size_)){
            
        rhs.sequence_ = nullptr;
        rhs.size_ = 0;
    }   
        

    // Move-assignment.
    // Just use std::swap() for all variables.
    // return the swapped resources
    Points2D& operator=(Points2D &&rhs){
        if (this != &rhs){
            std::swap(sequence_, rhs.sequence_);
            std::swap(size_, rhs.size_);
        }

        return *this;
    }


    // delete sequence & set size_ to 0.
    ~Points2D(){
        delete sequence_;
        size_ = 0;
    };


    // End of big-five.


    // One parameter constructor.
    Points2D(const std::array<Object, 2>& item) {
        // intalize sequence_ with elements of item.
        sequence_ = new std::array<Object, 2>{item};
        size_ = 1; // array<T, n>: n = 2.. pairs so, 2/1 = 1.
    }


    // getter for size_.
    size_t size() const {
        return size_;
    }


    // @location: an index to a location in the sequence.
    // @returns the point at @location.
    // const version.
    // abort() if out-of-range.
    const std::array<Object, 2>& operator[](size_t location) const {
        if (location < 0 || location >= size_){
            std::cerr << "ERROR" << std::endl;
            abort();
        };
        // e.g sequence_[location][location] = (sequence_[location])[location];
        return sequence_[location];
    }


    //  @c1: A sequence.
    //  @c2: A second sequence.
    //  @return their sum. If the sequences are not of the same size, append the
    //    result with the remaining part of the larger sequence.
    /*  
        Let c3 = sequence of the summed pairs of c1, c2.        

        Checks:
            If both sequences = 0, return first sequence.
            If one sequence = 0, return the non-zero sequence.
    */
    friend Points2D operator+(const Points2D &c1, const Points2D &c2) {
        
        if (c1.size() == 0 && c2.size() == 0) return c1;

        if (c1.size() == 0 || c2.size() == 0) 
            return c1.size() == 0 ? c2 : c1;
        
        Points2D c3;

        if (c1.size() == c2.size()){
            c3.sequence_ = new std::array<Object, 2>[c1.size()];
            c3.size_ = c1.size();

            for (size_t i = 0; i < c1.size(); i++){
                c3.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
                c3.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
            }
            
        }
        else if (c1.size() > c2.size()){
            c3.sequence_ = new std::array<Object, 2>[c1.size()];
            c3.size_ = c1.size();

            for (size_t i = 0; i < c2.size(); i++){
                c3.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
                c3.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
            }
            for (size_t  j = c2.size(); j < c1.size(); j++){
                c3.sequence_[j][0] = c1.sequence_[j][0];
                c3.sequence_[j][1] = c1.sequence_[j][1];
            }
        }
        else{
            c3.sequence_ = new std::array<Object, 2>[c2.size()];
            c3.size_ = c2.size();

            for (size_t i = 0; i < c1.size(); i++){
                c3.sequence_[i][0] = c1.sequence_[i][0] + c2.sequence_[i][0];
                c3.sequence_[i][1] = c1.sequence_[i][1] + c2.sequence_[i][1];
            }
            for (size_t  j = c1.size(); j < c2.size(); j++){
                c3.sequence_[j][0] = c2.sequence_[j][0];
                c3.sequence_[j][1] = c2.sequence_[j][1];
            }
        }

        return c3;
    }


    // Overloading the << (extraction) operator.
    /*
        Check if the sequence is either less than or equal to zero or nullptr.
        If true, then print "()" since there is no given sequence.
        If false, then iterate over the referenced sequence and appened 
        it to the ostream.
    */
    friend std::ostream &operator<<(std::ostream &out, const Points2D &some_points) {
        if (some_points.size_ <= 0 || some_points.sequence_ == nullptr) 
            return out << "()" << std::endl;

        for (size_t i = 0; i < some_points.size_; i++){
            out << "(" << some_points.sequence_[i][0] << ",";
            out << " " << some_points.sequence_[i][1] << ") ";
        }
        return out << std::endl;
    }


    // Overloading the >> (insertion) operator.
    // Read a chain from an input stream (e.g., standard input).
    /*
        Sets a double as input value to then check in.fail() and 
        input < 0 for validity. If not aborted, set referenced size 
        and intalize referenced sequence_ to the size of the input's 
        correct pair size. Then continue to add the pair of numbers to
        its respective slot in the sequence.

        Other checks:
        If the input has less than the specified size, determined by the 
        first extracted value, then abort.
    */
    friend std::istream &operator>>(std::istream &in, Points2D &some_points) {
        double value;
        in >> value;
        if (in.fail() || value < 0){
            std::cerr << "ERROR" << std::endl;
            abort();
        }

        some_points.size_ = (int) value;
        some_points.sequence_ = new std::array<Object, 2>[some_points.size_];

        size_t i = 0;
        while (i < some_points.size_
                && in >> some_points.sequence_[i][0]
                && in >> some_points.sequence_[i][1]){
            i++;
        }   
        
        if (i < some_points.size_){
            std::cerr << "ERROR" << std::endl;
            abort();
        }
        std::cout << "\n";


        
        return in;
    }


  private:
    // Sequence of points.
    std::array<Object, 2> *sequence_;
    // Size of sequence.
    size_t size_;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_Points2D_H_



