#include <sstream>
#include <stdio.h>
#include <jsoncpp/value.h>
#include <jsoncpp/json.h>
#include "json-parser.h"


static std::string readInputTestFile(const char *path)
{
   FILE *file = fopen( path, "rb" );
   if ( !file )
      return std::string("");
   fseek( file, 0, SEEK_END );
   long size = ftell( file );
   fseek( file, 0, SEEK_SET );
   std::string text;
   char *buffer = new char[size+1];
   buffer[size] = 0;
   if ( fread( buffer, 1, size, file ) == (unsigned long)size )
      text = buffer;
   fclose( file );
   delete[] buffer;
   return text;
}

bool JsonParser::parse(const std::string& path)
{
	bool parsing;
	std::string text;
	Json::Value root;
	Json::Value urls;
	Json::Features features;
	Json::Reader reader(features);
	std::stringstream out;
	
	text = readInputTestFile(path.c_str());
	parsing = reader.parse(text, root);
	if(!parsing) {
		std::cout<< "Could not read from json file: '"<< path<< "'." << std::endl<< reader.getFormattedErrorMessages()<< std::endl;
		return false;
	}
	
	out<< root.get("version", -1).asInt();
	version = out.str();
	lastCheck = root.get("last_check", "today").asString();
	urls = root["urls"];
	for(int i = 0; i < urls.size(); ++i) {
		std::string link = urls[i].get("url", "null").asString();
		std::string country = urls[i].get("country", "null").asString();
		int score = urls[i].get("score", 0).asInt();
		
		this->urls.push_back(Mirror(link, country, score));
	}
	return true;
}

const std::string& JsonParser::getVersion(void) const
{
	return version;
}

const std::string& JsonParser::getLastCheck(void) const
{
	return lastCheck;
}

const std::vector<Mirror>& JsonParser::getUrls(void) const
{
	return urls;
}

