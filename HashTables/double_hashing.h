#ifndef DOUBLE_HASHING_H
#define DOUBLE_HASHING_H

#include <vector>
#include <algorithm>
#include <functional>

// Double Hashing Implementation.
template <typename HashedObj>
class HashTableDouble
{
public:
    enum EntryType
    {
        ACTIVE,
        EMPTY,
        DELETED
    };

    /**
     *  Double HashTable constructor
     * @param  {int} r, {default} size = 101 :
     *
     * Details:
     *  - Intializes R with the value of r.
     *  - Intalizes table's size with the next prime of size.
     *  - Check if R > table size, if yes, abort operation
     */
    explicit HashTableDouble(int r, size_t size = 101) : array_(NextPrime(size)), R(r)
    {
        if (R > array_.size()){
            std::cerr << "ERROR";
            abort();
        }
        MakeEmpty();
    }

    /**
     *  Contains function
     * @param  {HashedObj} x :
     * @return {int}         :
     *
     * Details:
     *  - Returns the number of probes per query
     *  - if return is negative, it is inactive, else active.
     */
    int Contains(const HashedObj &x)
    {
        probe_count_ = 1;
        if (!IsActive(FindPos(x)))
            probe_count_ *= -1; // if it's negative, then it's not active
        return probe_count_;
    }

    /**
     *  Emptying function
     *
     * Details:
     *  - Clears the values of all entries in the table.
     */
    void MakeEmpty()
    {
        current_size_ = 0;
        collision_count_ = 0;
        for (auto &entry : array_)
            entry.info_ = EMPTY;
    }

    /**
     *  Insertion function (l-value)
     * @param  {HashedObj} x :
     * @return {bool}        :
     * 
     * Details:
     *  - Checks active, if not, then insert x, set active.
     *  - if active, finds new position to add.
     *  - manages table size given, elements exceed critera, double.
     */
    bool Insert(const HashedObj &x)
    {
        // Insert x as active
        size_t current_pos = FindPos(x);

        if (IsActive(current_pos))
            return false;

        array_[current_pos].element_ = x;
        array_[current_pos].info_ = ACTIVE;

        // Rehash; see Section 5.5
        if (++current_size_ > array_.size() / 2)
            Rehash();

        return true;
    }

    /**
     * Insertion function (r-value)
     * @param  {HashedObj} &x :
     * @return {bool}         :
     *
     * Details:
     *  - Checks active, if not, then insert x, set active.
     *  - if active, finds new position to add.
     *  - manages table size given, elements exceed critera, double.
     */
    bool Insert(HashedObj &&x)
    {
        // Insert x as active
        size_t current_pos = FindPos(x);
        if (IsActive(current_pos))
            return false;

        array_[current_pos] = std::move(x);
        array_[current_pos].info_ = ACTIVE;

        // Rehash; see Section 5.5
        if (++current_size_ > array_.size() / 2)
            Rehash();

        return true;
    }

    /**
     * Remove function for HashTable
     * @param  {HashedObj} x :
     * @return {bool}        :
     *
     * Details:
     *  - Checks if Hashed Object is active or not.
     *  - If Hashed Object is active, remove
     *  - If Hashed Object is not active, return false
     */
    bool Remove(const HashedObj &x)
    {
        size_t current_pos = FindPos(x);
        if (!IsActive(current_pos))
            return false;

        array_[current_pos].info_ = DELETED;
        return true;
    }

    /**
     *  Table Data Acessor
     * @return {size_t get_table_data()*}  :
     *
     * Details:
     *  - Returns private members of the class as a static array.
     */
    size_t *get_table_data()
    {
        static size_t data[4] = {current_size_, array_.size(), collision_count_, R};
        return data;
    }

private:
    struct HashEntry
    {
        HashedObj element_;
        EntryType info_;

        HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY)
            : element_{e}, info_{i} {}

        HashEntry(HashedObj &&e, EntryType i = EMPTY)
            : element_{std::move(e)}, info_{i} {}
    };

    // private members
    std::vector<HashEntry> array_;
    size_t current_size_;
    size_t collision_count_;
    int probe_count_;
    size_t R;

    /**
     *  Active function
     * @param  {size_t} current_pos :
     * @return {bool}               :
     *
     * Details:
     *  - Checks if the current position of the object is ultized.
     *  - Returns true if, yes, returns false otherwise
     */
    bool IsActive(size_t current_pos) const
    {
        return array_[current_pos].info_ == ACTIVE;
    }

    /**
     *  Find Position Function
     * @param  {HashedObj} x :
     * @return {size_t}      :
     *
     * Details:
     *  - Searches the table with the hash functions, given key.
     *  - Increments collisions and number of probes (per query)
     *  - Returns an index regardless of whether the key is active or not.
     *  - (Double only) offset is set to the second hash function, hence double
     */
    size_t FindPos(const HashedObj &x)
    {
        size_t offset = InternalHash2(x);
        size_t current_pos = InternalHash(x);

        while (array_[current_pos].info_ != EMPTY &&
               array_[current_pos].element_ != x)
        {
            current_pos += offset; // Compute ith probe.
            if (current_pos >= array_.size())
                current_pos -= array_.size();

            collision_count_++;
            probe_count_++;
        }
        return current_pos;
    }

    /**
     *  Rehashing function
     *  Makes sure the function is not too full for iterations.
     *  In regards to the speed performance.
     *
     * Details:
     *  - Double size and copy information.
     */
    void Rehash()
    {
        std::vector<HashEntry> old_array = array_;
        // Create new double-sized, empty table.
        array_.resize(NextPrime(2 * old_array.size()));
        for (auto &entry : array_)
            entry.info_ = EMPTY;

        // Copy table over.
        current_size_ = 0;
        for (auto &entry : old_array)
            if (entry.info_ == ACTIVE)
                Insert(std::move(entry.element_));
    }

    /**
     *   Simple Hash Function
     * @param  {HashedObj} x :
     * @return {size_t}      :
     */
    size_t InternalHash(const HashedObj &x) const
    {
        static std::hash<HashedObj> hf;
        return hf(x) % array_.size();
    }

    /**
     *  Second Hash Function with respect to R
     * @param  {HashedObj} x :
     * @return {size_t}      :
     */
    size_t InternalHash2(const HashedObj &x) const
    {
        static std::hash<HashedObj> hf;
        return R - (hf(x) % R);
    }
};

#endif // QUADRATIC_PROBING_H