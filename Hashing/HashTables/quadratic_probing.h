#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

namespace
{

  // Internal method to test if a positive number is prime.
  bool IsPrime(size_t n)
  {
    if (n == 2 || n == 3)
      return true;

    if (n == 1 || n % 2 == 0)
      return false;

    for (int i = 3; i * i <= n; i += 2)
      if (n % i == 0)
        return false;

    return true;
  }

  // Internal method to return a prime number at least as large as n.
  int NextPrime(size_t n)
  {
    if (n % 2 == 0)
      ++n;
    while (!IsPrime(n))
      n += 2;
    return n;
  }

} // namespace

// Quadratic probing implementation.
template <typename HashedObj>
class HashTable
{
public:
  enum EntryType
  {
    ACTIVE,
    EMPTY,
    DELETED
  };

  /**
   *  Quadratic HashTable constructor
   * @param {default} size = 101 :
   *
   * Details:
   *  - sets table's size with the next prime of size.
   *  - clears the tables's entries
   */
  explicit HashTable(size_t size = 101) : array_(NextPrime(size))
  {
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
      probe_count_ *= -1;
    // std::cout << "[Probes] : " << FindPos(x) << " | ";
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
    static size_t data[3] = {current_size_, array_.size(), collision_count_};
    return data;
  }

  HashedObj get(HashedObj &key)
  {
    int pos = FindPos(key);
    return array_[pos].info_ == ACTIVE ? array_[pos].element_ : "";
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
   *  - (quadratic only) offset is set 1, but increments by 2
   *    with each collision, hence quadratic
   */
  size_t FindPos(const HashedObj &x)
  {
    size_t offset = 1;
    size_t current_pos = InternalHash(x);

    while (array_[current_pos].info_ != EMPTY &&
           array_[current_pos].element_ != x)
    {
      current_pos += offset; // Compute ith probe.
      offset += 2;
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
};

#endif // QUADRATIC_PROBING_H
