#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::string tolower(std::string& str)
{
	for( int i = 0; i < str.length(); i++ )
		str[i] = tolower(str[i]);
	return str;
}


class TextFuzzer
{
public:

	std::string fuzz(std::string& text){
		std::vector< std::string > tokenVector = tokenize(tolower(text));
		std::ostringstream fuzzText;
		sort( tokenVector.begin(), tokenVector.end() );
		for( size_t i = 0; i < tokenVector.size(); i++ ){
			if( tokenVector[i].length() >= s_minTokenLen )
				fuzzText << tokenVector[i] << " ";
		}
		
		return fuzzText.str();
	}

private:
	std::vector< std::string > tokenize( const std::string& message )
	{
		std::vector< std::string > tokenVector;
		std::ostringstream  token;
		for( size_t i = 0; i < message.length(); i++ ){
			if(isalnum((unsigned char)message[i]) || message[i] == '\'' ){
				token << message[i];
				continue;
			}else if( token.str() != "" ){
				tokenVector.push_back(token.str());
				token.str("");
			}
			token << message[i];
			tokenVector.push_back(token.str());
			token.str("");
		}
		if(token.str() != "")
			tokenVector.push_back(token.str());

		return tokenVector;
	}

private:
	const static size_t s_minTokenLen = 2;

};



