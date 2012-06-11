#include "mirror.h"

Mirror::Mirror(const std::string& url, const std::string& country, int score) :
	mUrl(url), mCountry(country), mScore(score)
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

int Mirror::getScore(void) const
{
	return mScore;
}
