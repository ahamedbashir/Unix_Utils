#include <cstdio>
#include <getopt.h> // to parse long arguments.
#include <string>
using std::string;
#include <cctype>
using std::tolower;
using std::toupper;
#include <algorithm>
using std::remove;
using std::lexicographical_compare;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <set>
using std::set;
using std::multiset;
#include <strings.h>

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Limited clone of sort.  Supported options:\n\n"
"   -r,--reverse        Sort descending.\n"
"   -f,--ignore-case    Ignore case.\n"
"   -u,--unique         Don't output duplicate lines.\n"
"   --help              Show this message and exit.\n";

struct igncaseComp {
	bool operator()(const string& s1, const string& s2) {
		return (strcasecmp(s1.c_str(),s2.c_str()) < 0);
	}
};


struct icompare_char {
	bool operator()(char c1, char c2) {
		return tolower(c1) < tolower(c2);
	}
};

// return true if s1 comes before s2
struct compare {
	bool operator()(string const& s1, string const& s2) {
		string temp1(s1), temp2(s2);
			temp1.erase(remove(temp1.begin(), temp1.end(), '\t'), temp1.end());
			temp2.erase(remove(temp2.begin(), temp2.end(), '\t'), temp2.end());
		return (strcasecmp(temp1.c_str(),temp2.c_str()) < 0);
		}
};


/* NOTE: set<string,igncaseComp> S; would declare a set S which
 * does its sorting in a case-insensitive way! */

int main(int argc, char *argv[]) {
	// define long options
	static int descending=0, ignorecase=0, unique=0;
	static struct option long_opts[] = {
		{"reverse",       no_argument,   0, 'r'},
		{"ignore-case",   no_argument,   0, 'f'},
		{"unique",        no_argument,   0, 'u'},
		{"help",          no_argument,   0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "rfuh", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'r':
				descending = 1;
				break;
			case 'f':
				ignorecase = 1;
				break;
			case 'u':
				unique = 1;
				break;
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}

	/* TODO: write me... */
	
	set<string, igncaseComp> fuline;
	set<string, compare>uline;    //problem when there is leading tab or whitespace
	multiset<string, igncaseComp> fmline;
	multiset<string, compare> mline; //problem when there is leadding tab or white space
	string line;
	while ( getline(cin,line) ) {
		uline.insert(line);
		fuline.insert(line);
		mline.insert(line);
		fmline.insert(line);
	}
	
	if (  descending == 0 && ignorecase == 0 && unique == 0 ) {
		for (multiset<string,compare>::iterator i = mline.begin(); i != mline.end(); ++i )
			cout << *i << endl;
	}
	
	else if (  descending == 1 && ignorecase == 0 && unique == 0 ) {
		for (multiset<string,compare>::reverse_iterator i = mline.rbegin(); i != mline.rend(); ++i )
			cout << *i << endl;
	}

	else if (  descending == 0 && ignorecase == 1 && unique == 0 ) {
		for (multiset<string,igncaseComp>::iterator i = fmline.begin(); i != fmline.end(); ++i )
			cout << *i << endl;
	}
	else if (  descending == 1 && ignorecase == 1 && unique == 0 ) {
		for (multiset<string,igncaseComp>::reverse_iterator i = fmline.rbegin(); i != fmline.rend(); ++i )
			cout << *i << endl;
	}

	else if (  descending == 0 && ignorecase == 0 && unique == 1 ) {
		for (set<string,compare>::iterator i = uline.begin(); i != uline.end(); ++i )
			cout << *i << endl;
	}
	else if (  descending == 1 && ignorecase == 0 && unique == 1 ) {
		for (set<string,compare>::reverse_iterator i = uline.rbegin(); i != uline.rend(); ++i )
			cout << *i << endl;
	}

	else if (  descending == 0 && ignorecase == 1 && unique == 1 ) {
		for (set<string, igncaseComp>::iterator i = fuline.begin(); i != fuline.end(); ++i )
			cout << *i << endl;
	}
	else if (  descending == 1 && ignorecase == 1 && unique == 1 ) {
		for (set<string, igncaseComp>::reverse_iterator i = fuline.rbegin(); i != fuline.rend(); ++i )
			cout << *i << endl;
	}


	return 0;
}
