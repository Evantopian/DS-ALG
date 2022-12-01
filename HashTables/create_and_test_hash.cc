// Evan Huang
#include <fstream>
#include <iostream>
#include <string>

#include "quadratic_probing.h"
#include "linear_probing.h"
#include "double_hashing.h"

using namespace std;

// @hash_table: a hash table (can be linear, quadratic, or double)
// @words_filename: a filename of input words to construct the hash table
// @query_filename: a filename of input words to test the hash table
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table,
                              const string &words_filename,
                              const string &query_filename)
{
    // empty table, parse data, insert to hash table
    hash_table.MakeEmpty();
    ifstream db_file(words_filename);
    if (db_file.fail())
    {
        cerr << "ERROR";
        abort();
    }

    string db_line;
    while (db_file.good() && getline(db_file, db_line))
    {
        hash_table.Insert(db_line);
    }
    db_file.close();

    // add queries into a vector
    db_file.open(query_filename);
    vector<string> queries;
    while (db_file.good() && getline(db_file, db_line))
    {
        queries.push_back(db_line);
    }
    db_file.close();

    // displaying table data using a static array
    size_t *data = hash_table.get_table_data();
    cout << "number_of_elements: " << data[0] << endl;
    cout << "size_of_table: " << data[1] << endl;
    cout << "load_factor: " << data[0] / (data[1] * 1.0) << endl;
    cout << "collisions: " << data[2] << endl;
    cout << "avg_collisions: " << data[2] / (data[0] * 1.0) << endl;
    cout << endl;

    // displaying the number of probes per word in queries
    // indicate if the queries are found or not
    for (string word : queries)
    {
        int probes = hash_table.Contains(word);
        cout << word << (probes > 0 ? " Found " : " Not_Found ") << abs(probes) << endl;
    }
}

// @argument_count: argc as provided in main
// @argument_list: argv as provided in imain
// Calls the specific testing function for hash table (linear, quadratic, or double).
int testHashingWrapper(int argument_count, char **argument_list)
{
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    int R = 89;

    // if user inputs r value, check if it is prime
    // otherwise, find next prime
    if (argument_count == 5)
    {
        const string rvalue(argument_list[4]);
        R = stoi(rvalue);
        if (!IsPrime(R)) R = NextPrime(R);
    }

    // if linear, quadratic, or double, intalize table respectively.
    if (param_flag == "linear")
    {
        HashTableLinear<string> linear_probing_table;
        TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
    }
    else if (param_flag == "quadratic")
    {
        HashTable<string> quadratic_probing_table;
        TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
    }
    else if (param_flag == "double")
    {
        cout << "r_value: " << R << endl;
        HashTableDouble<string> double_probing_table(R);
        TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
    }
    else
    {
        cout << "Unknown tree type " << param_flag
             << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash. DO NOT CHANGE IT.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv)
{

    if (argc != 4 and argc != 5)
    {
        cout << "Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag>" << endl;
        cout << "or Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
        return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}
