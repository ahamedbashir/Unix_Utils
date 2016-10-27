#include <cstdio>   // printf
#include <cstdlib>  // rand
#include <time.h>   // time
#include <getopt.h> // to parse long arguments.
#include <stdlib.h>
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <algorithm>
using std::swap;
using std::min;
using std::random_shuffle;  // from algorithm library



size_t myrandom ( size_t i) {
	return rand()%i;
	}

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Limited clone of shuf.  Supported options:\n\n"
"   -e,--echo              treat each argument as an input line.\n"
"   -i,--input-range=LO-HI treat each number in [LO..HI] as an input line.\n"
"   -n,--head-count=N      output at most N lines.\n"
"   --help                 show this message and exit.\n";

int main(int argc, char *argv[]) {
	// define long options
	static int echo=0, rlow=0, rhigh=0;
	static size_t count=-1;
	bool userange = false;
	static struct option long_opts[] = {
		{"echo",        no_argument,       0, 'e'},
		{"input-range", required_argument, 0, 'i'},
		{"head-count",  required_argument, 0, 'n'},
		{"help",        no_argument,       0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "ei:n:h", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'e':
				echo = 1;
				break;
			case 'i':
				if (sscanf(optarg,"%i-%i",&rlow,&rhigh) != 2) {
					fprintf(stderr, "Format for --input-range is N-M\n");
					rlow=0; rhigh=-1;
				} else {
					userange = true;
				}
				break;
			case 'n':
				count = atol(optarg);
				break;
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}
	/* NOTE: the system's shuf does not read stdin *and* use -i or -e.
	 * Even -i and -e are mutally exclusive... */

	/* TODO: write me... */


	srand(time(0)); //random initialization to use for permuation

	if ( echo == 0 && !userange ) { 
		string newline;
		vector<string> lineinput;
		while( getline(cin, newline) )
			lineinput.push_back(newline);

		random_shuffle ( lineinput.begin(), lineinput.end(), myrandom);
	
		if ( count >= 0 )
			for ( size_t i =0; i < lineinput.size()&& i< count; i++ )
				cout << lineinput[i] << endl;
		else 
			for ( vector<string>::iterator i = lineinput.begin(); i != lineinput.end(); ++i)
				cout << *i << endl;

		
	}
	
	else if (echo ==0 && userange ) {
		vector<size_t> rangeinput;
		for (long i = rlow; i <= rhigh; i++ )
			rangeinput.push_back(i);

		random_shuffle ( rangeinput.begin(), rangeinput.end(), myrandom);
	
		if ( count >= 0 )
			for ( size_t i =0; i < rangeinput.size()&& i< count; i++ )
				cout << rangeinput[i] << endl;
		else 
			for ( vector<size_t>::iterator i = rangeinput.begin(); i != rangeinput.end(); ++i)
				cout << *i << endl;



	}


	else if ( echo == 1 && !userange ) {
		vector<string> arginput;
		while ( optind < argc )
			arginput.push_back(argv[optind++]);
	
		random_shuffle ( arginput.begin(), arginput.end(), myrandom);
	
		if ( count >= 0 )
			for ( size_t i =0; i < arginput.size()&& i< count; i++ )
				cout << arginput[i] << endl;
		else 
			for ( vector<string>::iterator i = arginput.begin(); i != arginput.end(); ++i)
				cout << *i << endl;

	}



	return 0;
}
