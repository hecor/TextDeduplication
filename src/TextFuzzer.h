#ifndef _TEXTFUZZER_H__
#define _TEXTFUZZER_H__

#include <sstream>
#include <algorithm>
#include "StringUtil.h"

class TextFuzzer
{
public:
	std::string fuzz(std::string& text){
		std::vector< std::string > tokenVector = StringUtil::tokenize(StringUtil::tolower(text));
		std::ostringstream fuzzText;
		sort( tokenVector.begin(), tokenVector.end() );
		for( size_t i = 0; i < tokenVector.size(); i++ ){
			if( tokenVector[i].length() >= s_minTokenLen )
				fuzzText << tokenVector[i] << " ";
		}
		
		return fuzzText.str();
	}

private:
	const static size_t s_minTokenLen = 2;

};

#endif /* end of include guard: _TEXTFUZZER_H__ */

