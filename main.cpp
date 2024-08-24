//
//  main.cpp
//  Website refresh
//
//  Created by zuole on 8/24/24.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    return size * nmemb; // 我们不需要处理收到的数据，因此直接返回数据大小
}

void refreshUrl(const std::string& url, int interval) {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        while (true) {
            res = curl_easy_perform(curl);
            if(res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            } else {
                std::cout << "Refreshed: " << url << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(interval));
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

int main() {
    
    std::string url = "http://blog.sc.000708.xyz"; // 将此处替换为你想要刷新的网址
    std::cout<<"Fill in the website to refresh"<<std::endl;
    std::cin>>url;
    std::cout<<"Enter the interval time (Pre Second)"<<std::endl;
    int interval = 10; // 每次刷新之间的间隔时间（以秒为单位）
    std::cin>>interval;
    std::cout << "Starting to refresh " << url << " every " << interval << " seconds." << std::endl;
    refreshUrl(url, interval);

    return 0;
}
