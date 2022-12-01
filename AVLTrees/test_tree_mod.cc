// Evan Huang
// Main file for Part2(c) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree_p2c.h"
#include "sequence_map.h"

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

namespace
{
	// Helper function to break down the raw inputs.
	string get_partial_seq(string &seq)
	{
		string tmp_seq;
		for (char c : seq)
		{
			if (c == '/')
				break;
			tmp_seq += c;
		}
		seq = seq.substr(tmp_seq.length() + 1);
		return tmp_seq;
	}
	// @db_filename: an input database filename.
	// @seq_filename: an input sequences filename.
	// @a_tree: an input tree of the type TreeType. It is assumed to be
	//  empty.
	template <typename TreeType>
	void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree)
	{
		// Code for running Part2(b)

		// parase "data base" file
		ifstream db_file(db_filename);
		if (db_file.fail())
		{
			cerr << "ERROR" << endl;
			abort();
		}
		string db_line;

		// skipping the header since "//" denotes a enzyme
		while (db_file.good() && (db_line.size() < 2 || db_line.substr(db_line.length() - 2) != "//"))
			getline(db_file, db_line);

		// inserting the database into the tree
		while (db_file.good())
		{
			string an_enz_acro = get_partial_seq(db_line);

			while (db_line.length() > 1 && db_line != "/")
			{
				string a_reco_seq = get_partial_seq(db_line);
				SequenceMap new_seq_map(a_reco_seq, an_enz_acro);
				a_tree.insert(new_seq_map);
			}
			getline(db_file, db_line);
		}
		cout << "2: " << a_tree.get_size() << "\n";

		db_file.clear();
		db_file.close();

		// test #3
		double avg_depth = a_tree.get_avg_depth();
		cout << "3a: " << avg_depth << "\n";
		cout << "3b: " << avg_depth / a_tree.get_size() << "\n";

		// test #4
		db_file.open(seq_filename);
		auto file_top = db_file.tellg(); // saves the position from the top.
		double queries = 0, calls = 0, avg_calls = 0;

		while (getline(db_file, db_line))
		{
			calls = a_tree.find(db_line);
			if (calls < 0)
				queries--;
				
			avg_calls += abs(calls);
			queries++;
		}
		cout << "4a: " << queries << "\n";
		cout << "4b: " << avg_calls / queries << "\n";
		db_file.clear();

		// test #5
		// reset variables for re-counting
		db_file.seekg(file_top);
		avg_calls = 0, queries = 0;

		while (getline(db_file, db_line))
		{
			SequenceMap tmp_map(db_line, "");
			avg_calls += a_tree.remove(db_line);

			++queries;

			getline(db_file, db_line);
		}

		// cout << "avg: " << avg_calls << " | qs: " << queries <<  "\n";
		cout << "5a: " << a_tree.get_rev_calls() << "\n";
		cout << "5b: " << avg_calls / queries << "\n";
		db_file.clear();
		db_file.close();

		// Test 6
		avg_depth = a_tree.get_avg_depth();
		cout << "6a: " << a_tree.get_size() << "\n";
		cout << "6b: " << avg_depth << "\n";
		cout << "6c: " << avg_depth / a_tree.get_size() << "\n";
	}

} // namespace

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
		return 0;
	}
	const string db_filename(argv[1]);
	const string seq_filename(argv[2]);
	cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
	AvlTree<SequenceMap> a_tree;
	TestTree(db_filename, seq_filename, a_tree);

	return 0;
}
