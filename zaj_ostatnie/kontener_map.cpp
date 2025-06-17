#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype> // isspace(), isalpha(), isdigit(), ...
#include <algorithm>// find_if()
#include <cstdlib> // rand()
#include <stdexcept>// domain_error(), logic_error, ...
using std::istream;
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::isspace;
using std::find_if;
using std::rand;
//using std::RAND_MAX;
using std::domain_error;
using std::logic_error;
typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;
// 'true' if the argument is whitespace, 'false' otherwise
bool space(char c){
 return isspace(c);
}
// 'false' if the argument is whitespace, 'true' otherwise
bool not_space(char c){
    return !isspace(c);
}
vector<string> split(const string& str){
    typedef string::const_iterator iter;
    vector<string> ret;
    iter i = str.begin();
    while (i != str.end()){
        // ignore leading blanks
        i = find_if(i, str.end(), not_space);
        // find end of next word
        iter j = find_if(i, str.end(), space);
        // copy the characters in [i, j)
        if (i != str.end())
        ret.push_back(string(i, j));
        i = j;
 }
 return ret;
}
// read a grammar from a given input stream
Grammar read_grammar(istream& in){
    Grammar ret;
    string line;
    // read the input
    while (getline(in, line)){
        // 'split' the input into words
        vector<string> entry = split(line);
        if (!entry.empty())
        // use the category to store the associated rule
        // " 'map' from 'string' to 'Rule_collection' "
        ret[entry[0]].push_back(Rule(entry.begin()+1, entry.end()));
    }
    return ret;
}
    // predicate to checking whether the word is bracketed
    bool bracketed(const string& s){
        return s.size() > 1 && s[0] == '<' && s[s.size() -1] == '>';
    }
    // return a random integer in the range [0, n)
int nrand(int n){
    if ( n <= 0 || n > RAND_MAX)
    throw domain_error("Argument to nrand is out of range");
    const int bucket_size = RAND_MAX / n; //bucket - komory
    int r;
    do r = rand() / bucket_size;
    while (r >= n);
        return r;
}
// auxiliary function
void gen_aux(const Grammar& g, const string& word, vector<string>& ret){
    if (!bracketed(word)){
    ret.push_back(word);
    }
    else{
        // locate the rule that corresponds to 'word'
        Grammar::const_iterator it = g.find(word);
        if (it == g.end())
        throw logic_error("empty rule");
        // fetch the set of possible rules | fetch - pobrac
        const Rule_collection& c = it->second;
        //  from which we select one at random
        const Rule& r = c[nrand(c.size())];
        // recursively expand the second rule
        for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
        gen_aux(g, *i, ret);
 }
}
// sentence generator
vector<string> gen_sentence(const Grammar& g){
    vector<string> ret;
    gen_aux(g, "<sentence>", ret);
    return ret;
}
int main(){
    // generate the sentence
    vector<string> sentence = gen_sentence(read_grammar(cin));
    // write the first word, if any
    vector<string>::const_iterator it = sentence.begin();
     if (!sentence.empty()){
        cout << *it;
        ++it;
    }
 // write the rest of the words, each preceded by a space
    while (it != sentence.end()){
        cout << " " << *it;
        ++it;
    }
    cout << endl;
    system("pause");
    return 0;
}
