/*
 * CSc103 Project 3: unix utilities
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 *
 * Finally, please indicate approximately how many hours you spent on this:
 * #hours: 
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <algorithm>
using std::sort;
#include <string.h> // for c-string functions.
#include <getopt.h> // to parse long arguments.
#include <map>
using std::map;
static const char* usage =
"Usage: %s [OPTIONS] SET1 [SET2]\n"
"Limited clone of tr.  Supported options:\n\n"
"   -c,--complement     Use the complement of SET1.\n"
"   -d,--delete         Delete characters in SET1 rather than translate.\n"
"   --help          show this message and exit.\n";

void escape(string& s) {
	/* NOTE: the normal tr command seems to handle invalid escape
	 * sequences by simply removing the backslash (silently) and
	 * continuing with the translation as if it never appeared. */
	/* TODO: write me... */
	string temp;
	unsigned int octal, octint;
	unsigned char c;
	for ( size_t i =0; i != s.size(); i++ ) {
		if ( s[i] == '\\' && (i+1)!=s.size() ) {				//use a char c and string temp; then temp+=c; to fix the empty char problem
			switch(s[i+1]) {
				case '\\':
					c = '\\';
					i++;
					break;
				case 'a':
					c = '\a';
					i++;
					break;
				case 'b':
					c = '\b';
					i++;
					break;
				case 'f':
					c = '\f';
					i++;
					break;
				case 'n':
					c = '\n';
					i++;
					break;
				case 'r':
					c = '\r';
					i++;
					break;
				case 't':
					c = '\t';
					i++;
					break;
				case 'v':
					c = '\v';
					i++;
					break;
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
					i++;
					octal = s[i]-'0';
					octint = s[i+1]-'0';
					if ( octint >=0 && octint <= 7) {   // if range is
						octal = 8*octal + octint;
						i++;
						octint = s[i+1]-'0';
						if ( octint >=0 && octint <= 7) {
							octal = 8*octal + octint;
							i++;
						}

					}
					if ( octal >127) 		// to fix problem with my current linux kernel
						octal =127;
					c = (unsigned char)octal;		
					break;
				default: 
					i++;
					c = s[i];
					break;

				}
			temp+=c;
			}

		else if ( s[i] != '\\' || (i+1)!= s.size() )
			 temp+= s[i];
	}
	s = temp;				
}





// Function to covert valid range of the string into complete string;
void range( string& s ) {
	string temp;
	for ( size_t i =0; i < s.length(); i++ ) {			
		if ( s[i] == '-') {
			if ( i >0 && i < (s.length()-1) && s[i-1] < s[i+1] ) {
				char c = s[i-1]+1;
				while ( c != s[i+1] ) {
					temp+=c++;
					}
				}
			}
		else
			temp+= s[i];
		}
	s = temp;
}


void complementMap( map< unsigned char, unsigned char>& charmap, const string& s1, const string& s2) {
		
	unsigned char cur_char;
	for ( size_t i =0; i <256; i++) {		//initialize all the chars into the map key
		cur_char = (unsigned char)i;
		charmap[cur_char];
		}

	for ( size_t i =0; i < s1.length(); i++ )		// removes all the char keys from string s1
		charmap.erase(s1[i]);
	
	map<unsigned char, unsigned char>::iterator it;
	size_t j =0;
	for( it = charmap.begin(); it!=charmap.end(); it++) {
		if(j<s2.length() )
			it->second = s2[j];
		else
			it->second = s2[s2.length()-1];
		j++;
	
		}
}

int main(int argc, char *argv[])
{
	// define long options
	static int comp=0, del=0;
	static struct option long_opts[] = {
		{"complement",      no_argument,   0, 'c'},
		{"delete",          no_argument,   0, 'd'},
		{"help",            no_argument,   0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "cdh", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'c':
				comp = 1;
				break;
			case 'd':
				del = 1;
				break;
			case 'h':
				printf(usage,argv[0]);
				return 0;
			case '?':
				printf(usage,argv[0]);
				return 1;
		}
	}
	if (del) {
		if (optind != argc-1) {
			fprintf(stderr, "wrong number of arguments.\n");
			return 1;
		}
	} else if (optind != argc-2) {
		fprintf(stderr,
				"Exactly two strings must be given when translating.\n");
		return 1;
	}
	string s1 = argv[optind++];
	string s2 = (optind < argc)?argv[optind]:"";
	/* process any escape characters: */
	escape(s1);
	escape(s2);
	/* TODO: finish this... */

	range(s1);
	range(s2);
	size_t n2 = s2.size(), found; // n2 to map all the char out of boundaries from string s2 to s1
	char newc;
	while(fread(&newc,1,1,stdin) ) {
		if ( comp  == 0 && del == 0 ) {
			found = s1.find(newc);
			if ( found != string::npos)
				if ( found < n2 )
					cout << s2[found];
				else
					cout << s2[n2-1];
			else 
				cout << newc;
			}
		else if ( comp == 0 && del == 1 ) {
			found = s1.find(newc);
			if ( found == string::npos)
				cout << newc;	
			}
		else if ( comp == 1 && del == 0 ) {
			/*found = s1.find(newc);
			if ( found != string::npos)
				cout << newc;
			else
				cout << s2[n2-1];*/
			map< unsigned char, unsigned char>CompMap;
			complementMap(CompMap, s1, s2);
			map< unsigned char, unsigned char>::iterator it;
			it = CompMap.find(newc);
			if(it!=CompMap.end() )
				cout << it->second;
			else
				cout << newc;
			}
		else if ( comp == 1 && del ==1 ) {
			found = s1.find(newc);
			if ( found != string::npos )
				cout << newc;
			}
			
	} 
	return 0;
}


