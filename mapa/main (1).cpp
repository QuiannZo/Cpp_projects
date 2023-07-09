#include <algorithm>
#include <iostream>
#include <string>

#include "map.hxx"
#include "../Lista/list.hpp"

typedef ecci::List<std::string> StringList;
typedef ecci::Map<std::string, size_t> OcurrencesType;
typedef ecci::Map<size_t, StringList, ecci::Greater<size_t>> WordsByFrecuency;

int main()
{
    OcurrencesType occurrences;
    std::string word;

    while(std::cin >> word)
    {
        auto it = std::remove_if(word.begin(), word.end(), ::ispunct);
        word.erase(it, word.end());
        ++occurrences[word];
    }
    WordsByFrecuency wordsByFrecuency;
    for(typename OcurrencesType::Iterator itr = occurrences.begin();
     itr !=  occurrences.end();  ++itr)
    {
        const std::string& currentWord = itr.getKey();
        const size_t frequency = itr.getValue();
        std::cout << currentWord << "\t" << frequency << std::endl;
        wordsByFrecuency[frequency].append(currentWord);
    }
    std::cout << "----------------------"<< std::endl;

    for(typename WordsByFrecuency::Iterator itr = wordsByFrecuency.begin();
        itr != wordsByFrecuency.end(); ++itr)
    {
        const size_t frequency = itr.getKey();
        const StringList& words = itr.getValue();
        std::cout <<frequency << "\t";
        for(const std::string& currentWord : words)
        {
            std::cout << currentWord << ", ";
        }
        std::cout << std::endl;
    }

}