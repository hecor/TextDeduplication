#include <time.h>
#include "Hasher.h"
#include "Clock.h"
#include "DuplicateTextDetector.h"
#include "PostReader.h"

using namespace std;

const std::string currentDateTime()
{
	time_t  rawtime = time(0);
	struct tm* now = localtime(&rawtime);
	char buf[80];
	strftime(buf, sizeof(buf), "%Y-%m-%d 00:00:00.000000", now);
	return buf;
}

int main()
{
	Clock clock;
	char delimitor = '\036';
	string insert_timestamp = currentDateTime();
	
	int distinct_count = 1;
	int duplicate_count = 0;
	int one_duplicate = 0;
	int two_duplicate = 0;

	PostCsvReader postReader("../sorted_latest_shard1.csv");
	TAPost* post1 = postReader.nextPost();
	if(post1 != NULL)
		cout << post1->txt_id << delimitor << post1->target_uid << delimitor << insert_timestamp << endl;

	TAPost* post2 = postReader.nextPost();
	while(post2 != NULL){
		if( DuplicateTextDetector::isDuplicate(post1->message, post2->message) ){
//			cout << post2->creator_uid << '\t' << post2->message << endl;
//			duplicate_count++;
		} else {
//			if(duplicate_count > 0)
//				cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
//			if(duplicate_count == 1)
//				one_duplicate++;
//			else if(duplicate_count == 2)
//				two_duplicate++;
//			duplicate_count = 0;
			
			cout << post2->txt_id << delimitor << post2->target_uid << delimitor << insert_timestamp << endl;
			distinct_count++;
		}

		delete post1;
		post1 = post2;
		post2 = postReader.nextPost();
	}

	if( post1 != NULL )
		delete post1;

//	cout << "one duplicate count: " << one_duplicate << endl;
//	cout << "two duplicate count: " << two_duplicate << endl;
	cout << "distinct count: " << distinct_count << endl;
	cout << "Elasped seconds: " << clock.millisecondElapsed()/1000 << endl;

	return 0;
}

/*
int main()
{
	Clock clock;

	ifstream input("../duplicate.csv", ifstream::in );
	if(!input.good()){
		cout << "Can't read file!" << endl;
		return -1;
	}

	string s1, s2;
	getline(input, s1);
	cout << s1 << endl;

	int count = 0;
	while(!input.eof()){
		getline(input, s2);
		if( DuplicateTextDetector::isDuplicate(s1, s2) ){
			cout << s2 << endl;
		} else {
			cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
			cout << s2 << endl;
			count++;
		}

		s1 = s2;
	}

	cout << count << endl;
	cout << "Elasped seconds: " << clock.millisecondElapsed()/1000 << endl;

	return 0;
}
*/
/*
int main()
{
	string s1 = "I'm at Delta Chi (Flint, Michigan) http://t.co/ToLOTKwp";
	string s2 = "I'm at Delta Chi (Flint, Michigan) http://t.co/P7szyjWr";
	cout << DuplicateTextDetector::isDuplicate(s1, s2) << endl;
	return 0;
}
*/
