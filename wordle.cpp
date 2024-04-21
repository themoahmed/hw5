#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> answers;
    std::string word = in;
    std::string floatingChars = floating;
    worldHelper(word, floatingChars, dict, answers);
    return answers;
    

}

void worldHelper (
    std::string& in,
    std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& answers
){
  
    size_t firstEmptyChar = in.find('-');
    int emptyCount = 0;
    if(firstEmptyChar == std::string::npos){
        if(dict.find(in) != dict.end()){
            const_cast<std::set<std::string>&>(answers).insert(in);
        }
        return;
    }

    

    for (char c : in){
        if (c == '-'){
            emptyCount++;
        }
    }


    //Floating characters = 0
     if(floating.empty()){
        for (char c = 'a'; c <= 'z'; c++){
            in[firstEmptyChar] = c;
            worldHelper(in, floating, dict, answers);
            in[firstEmptyChar] = '-';
        }
    } else {
        //Floating characters = empty spaces
        if(floating.size() == emptyCount){
            for (char c : floating){
                in[firstEmptyChar] = c;
                std::string newFloating = floating;
                newFloating.erase(floating.find(c), 1);
                worldHelper(in, newFloating, dict, answers);
                in[firstEmptyChar] = '-';
            }
        }

        //More empty spaces than floating characters
        if (floating.size() < emptyCount) {
            for (char c : floating) {
                in[firstEmptyChar] = c;
                std::string newFloating = floating;
                newFloating.erase(floating.find(c), 1);
                worldHelper(in, newFloating, dict, answers);
                in[firstEmptyChar] = '-';
            }

            for (char c = 'a'; c <= 'z'; c++) {
                if (floating.find(c) == std::string::npos) {
                    in[firstEmptyChar] = c;
                    worldHelper(in, floating, dict, answers);
                    in[firstEmptyChar] = '-';
                }
            }
        }
    }

}
