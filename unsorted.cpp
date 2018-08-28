//Katherine Hecht, Julia Hughes, Richard Stefanik
// unsorted.cpp: Unsorted Map

#include "map.h"
#include <vector>

// Methods --------------------------------------------------------------------

void UnsortedMap::insert(const std::string &key, const std::string &value) {
    // If key is not in the set, add it to the set
    if (search(key) == NONE)
    {
        Entry a (key, value);
        entries.push_back(a);
    }

    //Key is in the set, so update its value
    else 
    {
        for (unsigned int i = 0; i < entries.size(); i++)
        {
            if (entries[i].first == key)
            {
                entries[i].second = value;
                return;
            }   
        }
    }
}


// Keys are not sorted, use linear search
const Entry UnsortedMap::search(const std::string &key) {
    for (unsigned int i = 0; i < entries.size(); i++)
    {
        if (entries[i].first == key)
        {
            return entries[i];
        }   
    }
    return NONE;
}

void UnsortedMap::dump(std::ostream &os, DumpFlag flag) {
   for (auto it = entries.begin(); it != entries.end(); it++) {
        switch (flag) {
            case DUMP_KEY:          os << it->first  << std::endl; break;
            case DUMP_VALUE:        os << it->second << std::endl; break;
            case DUMP_KEY_VALUE:    os << it->first  << "\t" << it->second << std::endl; break;
            case DUMP_VALUE_KEY:    os << it->second << "\t" << it->first  << std::endl; break;
        }
    }
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
