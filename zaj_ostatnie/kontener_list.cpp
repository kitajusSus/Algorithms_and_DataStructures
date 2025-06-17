#include <iostream>
#include <iterator> // ostream_iterator
#include <string>
//#include <cctype>
#include <list>
#include <algorithm>

// SPLIT
// generic function
// version of split function might return a vector<string>
// or list<string> or another kind of container
using std::cin;
using std::cout;
using std::ostream_iterator;
using std::string;
//using std::isspace;
using std::list;
//using std::find_if;
// 'true' if the argument is whitespace, 'false' otherwise
bool space(char c){
    return isspace(c);
}
// 'false' if the argument is whitespace, 'true' otherwise
bool not_space(char c){
    return !isspace(c);
}
// old version: ch07_p126
template <class Out>
void split(const string& str, Out os){
    typedef string::const_iterator iter;
    iter i = str.begin();
    while (i != str.end()){
 // ignore leading blanks
    i = find_if(i, str.end(), not_space);
    // find end of next word
    iter j = find_if(i, str.end(), space);
    // copy the characters in [i, j)
    if (i != str.end())
    *os++ = string(i, j); // changed: ret.push_back(string(i, j));
    i = j;
    }
}
int main()
{
 list<string> word_list;
 string s;
 cout<<"Example nr 1:\nEnter next line of words:\n";
 while (getline(cin, s)&&s!="END"){
    split(s, back_inserter(word_list));
    typedef list<string>::const_iterator iter; //iter aka
    //list<string>::const_iterator

    iter i = word_list.begin();
    iter e = word_list.end();
    while(i!=e){
    cout<<*i<<"\n";
    ++i;
    }
    word_list.clear();
    cout<<"Enter next line of words (or type 'END'):\n";
 }
    cout<<"\nExample nr 2:\n";
    while (getline(cin, s)){
    cout<<"Enter next line of words (or type 'Ctrl+Z'):\n";
    split(s, ostream_iterator<string>(cout, "\n"));
 }
    return 0;
}
