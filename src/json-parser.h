#ifndef PMU_JSON_PARSER_H
#define PMU_JSON_PARSER_H

#include <vector>
#include <string>

#include "mirror.h"

class JsonParser
{
private:
	std::string version;
	std::string lastCheck;
	std::vector<Mirror> urls;
	
public:
	bool parse(const std::string& path);
	
	const std::string& getVersion(void) const;
	const std::string& getLastCheck(void) const;
	const std::vector<Mirror>& getUrls(void) const;
};

#endif
