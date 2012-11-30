#ifndef _DUPLICATETEXTDETECTOR_H__
#define _DUPLICATETEXTDETECTOR_H__

#include "StringUtil.h"

class DuplicateTextDetector
{
public:
	static bool isDuplicate(const string& s1, const string& s2)
	{
		const vector<string> v1 = StringUtil::tokenize(StringUtil::tolower(s1));
		const vector<string> v2 = StringUtil::tokenize(StringUtil::tolower(s2));

		int32_t editDistance = StringUtil::editDistanceByToken(v1, v2);

		return  editDistance*1.0/max(v1.size(), v2.size()) <= s_minDistanceThreshold;
	}

private:
	const static double s_minDistanceThreshold = 0.3;
};

#endif /* end of include guard: _DUPLICATETEXTDETECTOR_H__ */
