#include "mirror.h"

Mirror::Mirror(const std::string& protocol, const std::string& url, double completion, const std::string& country, double score) :
	mProtocol(protocol), mUrl(url), mCountry(country), mScore(score), mCompletion(completion)
{

}

const std::string& Mirror::getUrl(void) const
{
	return mUrl;
}

const std::string& Mirror::getCountry(void) const
{
	return mCountry;
}

double Mirror::getScore(void) const
{
	return mScore;
}

const std::string& Mirror::getCountryCode(void) const
{
	return mCountryCode;
}

const std::string& Mirror::getProtocol(void) const
{
	return mProtocol;
}

int Mirror::getDelay(void) const
{
	return mDelay;
}

double Mirror::getCompletion(void) const
{
	return mCompletion;
}

double Mirror::getDurationStddev(void) const
{
	return mDuration_stddev;
}

double Mirror::getDurationAverage(void) const
{
	return mDuration_avg;
}
