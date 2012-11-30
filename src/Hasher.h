#include "lookup3.h"
#include "TextFuzzer.h"
#include <bitset>
#include <iostream>
#include <fstream>
#include <cstring>

class FileLineHasher
{
public:
	void hash(const std::string ifilename, const std::string ofilename)
	{
		std::ifstream input(ifilename.c_str(), std::ifstream::in);
		if(!input.good()){
			std::cout << "Can't read file " << ifilename << std::endl;
			return;
		}
		std::ofstream output(ofilename.c_str(), std::ofstream::out);
		if(!output.good()){
			std::cout << "Can't write file " << ofilename << std::endl;
			return;
		}
		char buffer[1024];
		input.getline(buffer, 1024);
		while(!input.eof()){
			uint32_t hashvalue = hashlittle(buffer, strlen(buffer), 0);
			output << hashvalue << '\t' << buffer << std::endl;
			input.getline(buffer, 1024);
		}

		input.close();
		output.close();

		return;
	}
};

class OnlineHasher
{
public:
	OnlineHasher(){
	}

	/*
	 * if hashvalue already exists, return false, else return true
	 */
	virtual bool hash(const char* str, uint32_t len){
		uint32_t hashvalue = hashlittle(str, len, 0);
//		std::cout << hashvalue << std::endl;
		if( hashtable.test(hashvalue) )
			return false;
		else{
			hashtable.set(hashvalue);
			return true;
		}
	}

private:
	const static uint32_t MAX_HASH_SIZE = 0xffffffff;
	std::bitset< MAX_HASH_SIZE > hashtable;
};


class OnlineFuzzyHasher : public OnlineHasher
{
public:
	OnlineFuzzyHasher() : OnlineHasher() { }
	
	/*
	 * if hashvalue already exists, return false, else return true
	 */
	virtual bool hash(const char* str, uint32_t len){
		std::string originalText(str, len);
//		std::cout << "original: " << originalText << std::endl;
		std::string fuzzText = fuzzer.fuzz(originalText);
//		std::cout << "fuzztext: " << fuzzText << std::endl;
		return OnlineHasher::hash(fuzzText.c_str(), fuzzText.length());
	}

private:
	TextFuzzer	fuzzer;
};




