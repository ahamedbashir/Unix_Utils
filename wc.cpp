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

#include <string>
using std::string;
#include <set>
using std::set;
#include <getopt.h> // to parse long arguments.
#include <cstdio> // printf

static const char* usage =
"Usage: %s [OPTIONS]...\n"
"Limited clone of wc.  Supported options:\n\n"
"   -c,--bytes            print byte count.\n"
"   -l,--lines            print line count.\n"
"   -w,--words            print word count.\n"
"   -L,--max-line-length  print length of longest line.\n"
"   -u,--uwords           print unique word count.\n"
"   --help          show this message and exit.\n";

int main(int argc, char *argv[])
{
	// define long options
	static int charonly=0, linesonly=0, wordsonly=0, uwordsonly=0, longonly=0;
	static struct option long_opts[] = {
		{"bytes",           no_argument,   0, 'c'},
		{"lines",           no_argument,   0, 'l'},
		{"words",           no_argument,   0, 'w'},
		{"uwords",          no_argument,   0, 'u'},
		{"max-line-length", no_argument,   0, 'L'},
		{"help",            no_argument,   0, 'h'},
		{0,0,0,0}
	};
	// process options:
	char c;
	int opt_index = 0;
	while ((c = getopt_long(argc, argv, "clwuLh", long_opts, &opt_index)) != -1) {
		switch (c) {
			case 'c':
				charonly = 1;
				break;
			case 'l':
				linesonly = 1;
				break;
			case 'w':
				wordsonly = 1;
				break;
			case 'u':
				uwordsonly = 1;
				break;
			case 'L':
				longonly = 1;
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
	
	size_t charcount(0), bytecount (0), wordcount (0), linecount(0),cur_line_length(0), max_line_length(0);
	set<string> uwords;
	string word = "";	
	enum states { WhiteSp, N_Word };
	int state = WhiteSp;
	
	char newc;
	while (fread(&newc,1,1,stdin) ) {
		bytecount++;
		charcount++;

		if ( !isspace(newc) && newc!='\0' )
			word+=newc;
		else if( (isspace(newc) || newc == '\0') && !word.empty() ){
			uwords.insert(word);
			word = "";
		}
		if ( newc == '\t')
			cur_line_length+= 8 - (cur_line_length % 8 );
		else if ( newc != '\n')
			cur_line_length++;

		if ( newc== ' ' || newc == '\t'  )
			state = WhiteSp;
		else if (newc=='\n') {
			linecount++;
			if ( cur_line_length > max_line_length)
				max_line_length = cur_line_length;
			cur_line_length = 0;
			state = WhiteSp;
			}
		else {
			if ( state == WhiteSp ) {
				wordcount++;
				}
			state = N_Word;
			}
		}


		if ( linesonly + wordsonly + charonly +uwordsonly +longonly > 1 )
			printf("\t");
		if( linesonly )
			printf("%lu \t", linecount );
		if( wordsonly )
			printf("%lu \t", wordcount ); 
		if( charonly )
			printf("%lu \t", charcount );
		if ( longonly )
			printf("%lu \t", max_line_length );
		if( uwordsonly )
			printf("%lu \t",uwords.size() );
		if(!(linesonly||wordsonly||charonly||longonly || uwordsonly))
			printf("\t %lu \t %lu \t %lu ",linecount, wordcount, charcount);
		printf("\n");
	return 0;
}
