#ifndef __PROJECTS_TGG_UTILITIES_HPP__
#define __PROJECTS_TGG_UTILITIES_HPP__

#include <string>


namespace utilities
{
    //TODO: not robust. Only correctly handles whole positive numbers.
    static inline bool IsInteger(const std::string & s)
    {
	if (s.empty() ||
	    ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) 
	{
	    return false;
	}
	    
	char * p;
	strtol(s.c_str(), &p, 10);
	    
	return (*p == 0);
    }
}
#endif 
