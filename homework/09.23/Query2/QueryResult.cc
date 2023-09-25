#include "QueryResult.hh"

using std::endl;

QueryResult::QueryResult(string word, shared_ptr<vector<string>> spFileVector, shared_ptr<set<size_t>> spWordNoSet) 
: _word(word)
, _spFileVector(spFileVector)
, _spWordNoSet(spWordNoSet) {

}


void QueryResult::printToFile(ofstream& ofs) {

    ofs << _word << " occur " << _spWordNoSet->size() << " times" << endl;

    for (auto& elem : *_spWordNoSet) {
        ofs << "    (line " << elem << ")" << (*_spFileVector)[elem-1] << endl;
    }
}