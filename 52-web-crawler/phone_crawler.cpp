#include <iostream>
#include <cstdlib>
#include <curl/curl.h>
#include <regex>
#include <string>
#include <queue>
#include <set>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main (int argc, char * argv[]) {
	if (argc != 3) {
		std::cout << "Usage:"<< std::endl;
		std::cout << "    ./phone_crawler [website name] [depth]" << std::endl;
		std::cout << std::endl;
		std::cout << "    eg.: ./phone_crawler www.codeforces.com 2" << std::endl;
		return 1;
	}

	const int depth = strtol(argv[2], NULL, 10);

	if (depth < 1) {
		std::cout << "Depth value should be higher than 0." << std::endl;
		return 1;
	}

	std::queue<std::pair<std::string, int> > websites;
	websites.push({argv[1], 1});

	std::set<std::string> visited;
	visited.insert(argv[1]);

	std::set<std::string> visited_phones;

	while (!websites.empty()) {
		std::string website = websites.front().first;
		int act_depth = websites.front().second;
		websites.pop();

		//std::cout << "NOW: " << website << std::endl;

		CURL * curl;
		CURLcode rest;
		std::string res;

		curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, website.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
   			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);
   			curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
			curl_easy_setopt(curl, CURLOPT_UNRESTRICTED_AUTH, 1L);
			curl_easy_setopt(curl, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1); 
			
			rest = curl_easy_perform(curl);

			//std::cout << res.size() << std::endl;
			//std::cout << res << std::endl;

			std::regex phone_regex("(\\+48\\ )?[\\d]{3}(\\ )[\\d]{3}(\\ )[\\d]{3}"); // IMPORTANT! - weak regex

			auto phone_begin = std::sregex_iterator(res.begin(), res.end(), phone_regex);
			auto phone_end = std::sregex_iterator();

			for (std::sregex_iterator i = phone_begin; i != phone_end; ++i) {
				std::smatch match = *i;
				std::string match_str = match.str();
				if (visited_phones.find(match_str) == visited_phones.end()) {
					std::cout << match_str << " - " << website << std::endl;
					visited_phones.insert(match_str);
				}
			}

			std::regex url_regex("(http|ftp|https)://([\\w_-]+(?:(?:\\.[\\w_-]+)+))([\\w.,@?^=%&:/~+#-]*[\\w@?^=%&/~+#-])?");

			auto url_begin = std::sregex_iterator(res.begin(), res.end(), url_regex);
			auto url_end = std::sregex_iterator();

			for (std::sregex_iterator i = url_begin; i != url_end; ++i) {
				std::smatch match = *i;
				std::string match_str = match.str();
				if (act_depth < depth && visited.find(match_str) == visited.end()) {
					websites.push({match_str, act_depth + 1});
					visited.insert(match_str);
				}
			}

			curl_easy_cleanup(curl);
		}
	}

	return 0;
}