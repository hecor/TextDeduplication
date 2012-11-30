#ifndef _STRINGUTIL_H__
#define _STRINGUTIL_H__

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class StringUtil
{
public:
	static string tolower(const string& str)
	{
		string str2(str);
		for( int i = 0; i < str.length(); i++ )
			str2[i] = ::tolower(str[i]);
		return str2;
	}

	static vector<string> tokenize( const string& message, const size_t minTokenLen = 2 )
	{
		vector<string> tokenVector;
		ostringstream  token;
		for( size_t i = 0; i < message.length(); i++ ){
			if(isalnum((unsigned char)message[i]) || message[i] == '\'' || message[i] == '.'){
				token << message[i];
				continue;
			}else if( token.str().length() >= minTokenLen  ){
				tokenVector.push_back(token.str());
			}
			// add the punctuations?
//			token << message[i];
//			tokenVector.push_back(token.str());
			token.str("");
		}
		if(token.str().length() > minTokenLen) 
			tokenVector.push_back(token.str());

		return tokenVector;
	}

//	static int32_t editDistanceByToken( const string &s1, const string &s2)
//	{
//		const vector<string> v1 = tokenize(s1);
//		const vector<string> v2 = tokenize(s2);
//		size_t len1 = v1.size();
//		size_t len2 = v2.size();
//
//		int32_t memo[len1+1][len2+1];
//		for( size_t i = 0; i < len1; i++ )
//			memo[i][0] = i;
//		for( size_t i = 0; i < len2; i++ )
//			memo[0][i] = i;
//
//		for( size_t k1 = 1; k1 <= len1; k1++ )
//			for( size_t k2 = 1; k2 <= len2; k2++ ){
//				int cost = (v1[k1-1] != v2[k2-1]);
//				memo[k1][k2] = min( memo[k1-1][k2-1]+cost, min(memo[k1-1][k2]+1, memo[k1][k2-1]+1) );
//			}
//
//		int result = memo[len1-1][len2-1];
//
//		return result;
//	}


	static int32_t editDistanceByToken(const vector<string> &v1, const vector<string> &v2)
	{
		size_t len1 = v1.size();
		size_t len2 = v2.size();
		int32_t delete_cost = 1, insert_cost = 1, replace_cost = 1;

		vector<int32_t> M0(len2+1), M1(len2+1);
		// fix length of v1, and calculate the distance from v2 to v1
		// a == 0
		for( int b = 0; b <= len2; b++ )
			M0[b] = b * delete_cost;
		
		for( int a = 1; a <= len1; a++ ){
			// b == 0
			M1[0] = a * insert_cost;

			for( int b = 1; b <= len2; b++ ){
				int32_t x = M0[b] + insert_cost;
				int32_t y = M1[b-1] + delete_cost;
				int32_t z = M0[b-1] + (v1[a-1] == v2[b-1]? 0:replace_cost);
				M1[b] = min(x, min(y,z));
			}
			swap(M0, M1);
		}

		return M0[len2];
	}

};

#endif /* end of include guard: _STRINGUTIL_H__ */
