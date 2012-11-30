#ifndef __POSTREADER_H_
#define __POSTREADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctype.h>
#include <stdio.h>

typedef struct _tapost
{
	string txt_id;//idpost
	string target_uid;//id_targetuser
	string creator_uid;//id_creatoruid
	string message;
	string created_time;
	int post_type;//status=0,link=1, photo,video, note,checkin
}TAPost;

class PostCsvReader
{
	public:
		PostCsvReader(const ::std::string filename) : m_count(0){
			m_file.open(filename.c_str());
			if( !m_file.good() )
				throw ::std::string("can't open ifstream ") + filename;
		}
		~PostCsvReader(){
			m_file.close();
		}

		TAPost* nextPost(){
			if( !m_file.eof() ){
				::std::string line;
				getline( m_file, line );
				if( line.length() == 0 )
					return nextPost();
				m_count++;
				::std::vector< ::std::string > postinfos;
				while( line.length() > 0 ){
					size_t index = line.find(READ_DELIMITOR);
					if( index == ::std::string::npos ){
						postinfos.push_back(line);
						break;
					}
					postinfos.push_back( line.substr(0, index) );
					line = line.substr(index+1);
				}
				if( postinfos.size() < 6){
					std::cerr << "Not enough delimitor in csv file in line " << m_count << "!!!" << std::endl;
					throw ::std::string("Not enough delimitor in csv file");
				}
				
				TAPost* lpost = new TAPost();
				lpost->txt_id = postinfos[0];
				lpost->target_uid = postinfos[1];
				lpost->creator_uid = postinfos[2];
				lpost->post_type = atoi(postinfos[3].c_str());
				lpost->created_time = postinfos[4];
				lpost->message = postinfos[5];
				return lpost;
			} else {
				return NULL;
			}
		}


	private:
		::std::ifstream	m_file;
		int m_count;
		const static char READ_DELIMITOR = '\t';
};


#endif
