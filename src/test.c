#include "hasher.h"
#include "clock.h"

int main()
{
//	FileLineHasher hasher;
//	hasher.hash("../duplicate.csv", "../hash.csv");

	Clock clock;

	OnlineHasher *hasher2 = new OnlineFuzzyHasher();
	std::ifstream input("../duplicate.csv", std::ifstream::in );
	if(!input.good()){
		std::cout << "Can't read file!" << std::endl;
		return -1;
	}

	char buffer[1024];
	input.getline(buffer, 1024);
	int count = 0;
	while(!input.eof()){
		if( hasher2->hash(buffer, strlen(buffer))){
			count++;
	//		std::cout << buffer << std::endl;
		}
		input.getline(buffer, 1024);
	}

	std::cout << count << std::endl;
	std::cout << "Elasped seconds: " << clock.millisecondElapsed()/1000 << std::endl;

	return 0;
}


