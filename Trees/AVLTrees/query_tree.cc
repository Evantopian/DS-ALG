// Evan Huang
// Main file for Part2(a) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
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

	// @db_filename: an input filename.
	// @a_tree: an input tree of the type TreeType. It is assumed to be
	//  empty.
	template <typename TreeType>
	void QueryTree(const string &db_filename, TreeType &a_tree)
	{
		// Code for running Part2(a)
		// Parse input file @db_filename and fill tree @a_tree
		// Then prompt the user for exactly three strings (do a loop) and
		// provide the results of find() as described in the assignment.

		// opening the file and checking for errors.
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

		// Test Case for 2A.
		while (cin >> db_line)
		{
			SequenceMap tmp_seq(db_line);
			cout << a_tree.find(tmp_seq);
		}
		db_file.clear();
		db_file.close();
	}
} // namespace

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
		return 0;
	}
	const string db_filename(argv[1]);

	cout << "Input filename is " << db_filename << endl;
	cout << db_filename << endl;
	AvlTree<SequenceMap> a_tree;
	QueryTree(db_filename, a_tree);

	return 0;
}
