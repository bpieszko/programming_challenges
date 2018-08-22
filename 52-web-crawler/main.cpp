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
		std::cout << "    ./email_crawler [website name] [depth]" << std::endl;
		std::cout << std::endl;
		std::cout << "    eg.: ./email_crawler www.codeforces.com 2" << std::endl;
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

	std::set<std::string> visited_emails;

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

			std::regex email_regex("[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\\.[a-zA-Z0-9-.]+");

			auto email_begin = std::sregex_iterator(res.begin(), res.end(), email_regex);
			auto email_end = std::sregex_iterator();

			for (std::sregex_iterator i = email_begin; i != email_end; ++i) {
				std::smatch match = *i;
				std::string match_str = match.str();
				if (visited_emails.find(match_str) == visited_emails.end()) {
					std::cout << match_str << " - " << website << std::endl;
					visited_emails.insert(match_str);
				}
			}

			std::regex url_regex("(http|ftp|https)://([\\w_-]+(?:(?:\\.[\\w_-]+)+))([\\w.,@?^=%&:/~+#-]*[\\w@?^=%&/~+#-])?");

			auto url_begin = std::sregex_iterator(res.begin(), res.end(), url_regex);
			auto url_end = std::sregex_iterator();

			for (std::sregex_iterator i = url_begin; i != url_end; ++i) {
				std::smatch match = *i;
				std::string match_str = match.str();
				if (match_str.substr(0, 8) == "https://")
					match_str.replace(0, 8, "");
				if (match_str.substr(0, 7) == "http://")
					match_str.replace(0, 7, "");
				if (match_str.substr(0, 4) != "www.")
					match_str = "www." + match_str;
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