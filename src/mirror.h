#ifndef PMU_MIRRORS_H
#define PMU_MIRRORS_H

#include <string>

class Mirror
{

private:
	std::string mUrl;
	std::string mCountry;
	std::string mCountryCode;
	std::string mProtocol;
	int mDelay;
	double mCompletion;
	double mDuration_stddev;
	double mDuration_avg;
	double mScore;
	
	
public:
	Mirror(const std::string& protocol, const std::string& url, double completion,const std::string& country, double score=0.0);
	
	const std::string& getUrl(void) const;
	const std::string& getCountry(void) const;
	const std::string& getCountryCode(void) const;
	const std::string& getProtocol(void) const;
	int getDelay(void) const;
	double getCompletion(void) const;
	double getDurationStddev(void) const;
	double getDurationAverage(void) const;
	double getScore(void) const;
};


#endif
