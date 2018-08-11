#ifdef __APPLE__
#include <json/json.h> // My MacOS looks for this path. Maybe a new version when installed via HomeBrew?
#else
#include <jsoncpp/json/json.h> // My Linux looks for this path. How about you?
#endif
#include <curl/curl.h>
#include <locale> // std::locale, std::isdigit
#include <string>
#include <iostream>
#include <memory> // std::unique_ptr

#ifndef IEX_H_INCLUDED
#define IEX_H_INCLUDED
#define IEX_API_V1_ENDPOINT "https://api.iextrading.com/1.0"

namespace IEX {
    namespace Resources {
        void sendGetRequest(Json::Value &data, std::string url);

        struct PriceData {
          std::string called_endpoint;
          std::string stock_symbol;
          double latest_price;
        };

        class Price {
        public:
            static std::size_t callback(
            const char* in,
            std::size_t size,
            std::size_t num,
            std::string* out)
            {
                const std::size_t totalBytes(size * num);
                out->append(in, totalBytes);
                return totalBytes;
            }

            static void sendGetRequest(Json::Value &jsonData, const std::string url){
                CURL* curl = curl_easy_init();

                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
                curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
                curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                long int httpCode(0);
                std::unique_ptr<std::string> httpData(new std::string());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
                curl_easy_perform(curl);
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
                curl_easy_cleanup(curl);

                // Json::CharReaderBuilder jsonReader;
                // Json::CharReader* reader;

                Json::Reader jsonReader;
                jsonReader.parse(*httpData, jsonData);
            }

            static PriceData get(const std::string stock_symbol) {
                std::string url = IEX_API_V1_ENDPOINT;
                url += "/stock/" + std::string(stock_symbol) + "/price";

                Json::Value jsonData;
                sendGetRequest(jsonData, url);

                PriceData pd;
                pd.called_endpoint = url;
                pd.stock_symbol = stock_symbol;
                pd.latest_price = jsonData.asDouble();

                return pd;
            }
        };
    }
}

#endif // IEX_H_INCLUDED
