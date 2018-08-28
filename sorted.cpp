//Katherine Hecht, Julia Hughes, Richard Stefanik
// sorted.cpp: Sorted Map

#include "map.h"

#include <algorithm>
#include <vector>

// Type Definitions ------------------------------------------------------------

typedef std::vector<Entry>::iterator IT;

// Prototypes ------------------------------------------------------------------

const Entry binary_search(const IT &start, const IT &end, const std::string &key);


//Compare function used by std sort
bool sortKeys(Entry &a, Entry &b)
{
    return (a.first < b.first);
}

// Methods ---------------------------------------------------------------------

void SortedMap::insert(const std::string &key, const std::string &value) {
    //Key is not in set, so add it
    if (search(key) == NONE)
    {
        Entry a(key, value);
        entries.push_back(a);
        //Just added a new value to the list, so must sort the map
        std::sort(entries.begin(), entries.end(), sortKeys);
    }

    //Key is in set, so update its value
    else
    {
        //Binary search to find entry
        IT start = entries.begin();
        IT end = entries.end();
        auto target = key;
        while (start < end) {
            auto length   = end - start;
            auto middle   = length / 2;
            auto midpoint = (start + middle)->first;

            //Search left half
            if (target < midpoint)
                end = start + middle;
            //Search right half
            else if (target > midpoint) 
                start = start + middle + 1;
            //Target found, so update its value and break out of loop
            else {
                (start + middle)->second = value;
                break;
            }                                    
        } 
    }
}

const Entry SortedMap::search(const std::string &key) {
    //If entries.size() is 0, the key is not in the map
    if (entries.size() == 0)
        return NONE;
    return binary_search(entries.begin(), entries.end()-1, key);
}

void SortedMap::dump(std::ostream &os, DumpFlag flag) {
    for (auto it = entries.begin(); it != entries.end(); it++) {
        switch (flag) {
            case DUMP_KEY:          os << it->first  << std::endl; break;
            case DUMP_VALUE:        os << it->second << std::endl; break;
            case DUMP_KEY_VALUE:    os << it->first  << "\t" << it->second << std::endl; break;
            case DUMP_VALUE_KEY:    os << it->second << "\t" << it->first  << std::endl; break;
        }
    }
}

// Internal Functions ----------------------------------------------------------

const Entry binary_search(const IT &start, const IT &end, const std::string &target) {
    auto length   = end - start;
    auto middle   = length / 2;
    auto midpoint = *(start + middle);

    //Found the entry
    if (start->first == target)
        return *start;

    //Nothing left to search, so target is not in entries.
    if (start == end)
        return NONE;                

    //Target found, so return it
    if (target == midpoint.first)
        return midpoint;                    

    //Search the left half 
    if (target < midpoint.first)
        return binary_search(start, start + middle, target);                
    //Search the right half
    else
        return binary_search(start + middle + 1, end, target);
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
