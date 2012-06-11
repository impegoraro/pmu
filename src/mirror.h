#ifndef PMU_MIRRORS_H
#define PMU_MIRRORS_H

#include <string>

class Mirror
{

private:
	std::string mUrl;
	std::string mCountry;
	int mScore;
	
	
public:
	Mirror(const std::string& url, const std::string& country, int score=0);
	
	const std::string& getUrl(void) const;
	const std::string& getCountry(void) const;
	int getScore(void) const;
};


#endif
