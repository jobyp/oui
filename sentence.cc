#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <cstdlib>

#include "split.h"

using std::vector;
using std::map;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::logic_error;
using std::domain_error;

typedef vector< string > Rule;
typedef vector< Rule > Rule_collection;
typedef map< string, Rule_collection > Grammar;

Grammar read_grammar(istream& in)
{
	Grammar g;
	string line;
	
	while( getline( in, line)) {
		
		Rule words = split( line);

		if ( !words.empty()) {

			Rule r( words.begin() + 1, words.end());
			g[ words[ 0]].push_back( r); 
		}
	}
	
	return g;
}

void print_rule(const Rule& r)
{
	for(const auto& s: r)
		cout << " " << s;
	cout << endl;
	
	return;
}

void print_rule_collection(const string& phrase, const Rule_collection& rc)
{
	for(const auto& r: rc) {
		
		cout << phrase;
		print_rule( r);
	}
	
	return;
}

void print_grammar(const Grammar& g)
{
	for(const auto& rc: g) 
		print_rule_collection( rc.first, rc.second);
	
	return;
}

void print_sentence(const vector< string>& words)
{
	for(const auto& w: words)
		cout << w << " ";
	cout << endl;
	
	return;
}

bool bracketed_word(const string& word)
{
	if ( word.empty())
		return false;
	
	if ( word[ 0] == '<' && word[ word.size() - 1] == '>')
		return true;

	return false;
}

Rule_collection::size_type random_index(const Rule_collection& v)
{
	if ( v.empty())
		throw domain_error("random_index of empty Rule_collection");
	
	cout << random() << ":" << v.size() << endl;

	return (random() % v.size());
}

void gen_sentence_aux(const Grammar& g, const string& phrase, vector< string >& ret)
{
	if ( !bracketed_word( phrase))  {

		ret.push_back( phrase);
		return;
	}

	Grammar::const_iterator it = g.find( phrase);
	
	if ( it ==  g.end())
		throw logic_error("empty grammar rule");

	const Rule_collection& rc = it->second;
	
	// cout << rc.size() << "{" << random_index( rc) << "}" << endl;
	const Rule& r = rc[ random_index( rc)];
	
	for(const auto& s: r)
		gen_sentence_aux( g, s, ret);
	
	return;
}

vector< string> gen_sentence(const Grammar& g)
{
	vector< string> ret;

	gen_sentence_aux( g, "<sentence>", ret);

	return ret;
}


int main() 
{
	Grammar g = read_grammar( cin);
	
	print_sentence( gen_sentence( g));

	return 0;
}

// Local Variables:
// c-basic-offset: 8
// mode: c++
// End:
