#ifdef __APPLE__
#include <json/json.h>  // My MacOS looks for this path. Maybe a new version when installed via HomeBrew?
#else
#include <jsoncpp/json/json.h>  // My Linux looks for this path. How about you?
#endif
#include <curl/curl.h>
#include <iostream>
#include <locale>  // std::locale, std::isdigit
#include <memory>  // std::unique_ptr
#include <string>
#include <vector>

#ifndef IEX_H_INCLUDED
#define IEX_H_INCLUDED
#define IEX_API_V1_ENDPOINT "https://api.iextrading.com/1.0"

namespace IEX {
    namespace Resources {
        static void sendGetRequest(Json::Value& jsonData,
                                   const std::string url,
                                   std::size_t (*callback)(const char*,
                                                           std::size_t,
                                                           std::size_t,
                                                           std::string*)) {
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

        struct CompanyData {
            std::string called_endpoint;
            std::string stock_symbol;
            std::string company_name;
            std::string exchange;
            std::string industry;
            std::string website;
            std::string description;
            std::string CEO;
            std::string issue_type;
            std::string sector;
            std::vector<std::string> tags;
        };

        class Company {
        public:
            static std::size_t callback(const char* in,
                                        std::size_t size,
                                        std::size_t num,
                                        std::string* out) {
                const std::size_t totalBytes(size * num);
                out->append(in, totalBytes);
                return totalBytes;
            }

            static CompanyData get(const std::string stock_symbol) {
                std::string url = IEX_API_V1_ENDPOINT;
                url += "/stock/" + std::string(stock_symbol) + "/company";

                Json::Value jsonData;
                sendGetRequest(jsonData, url, callback);

                CompanyData cd;

                // clang-format off
                cd.called_endpoint = url;
                cd.stock_symbol    = stock_symbol;
                cd.company_name    = jsonData["companyName"].asString();
                cd.exchange        = jsonData["exchange"].asString();
                cd.industry        = jsonData["industry"].asString();
                cd.website         = jsonData["website"].asString();
                cd.description     = jsonData["description"].asString();
                cd.CEO             = jsonData["CEO"].asString();
                cd.issue_type      = jsonData["issue_type"].asString();
                cd.sector          = jsonData["sector"].asString();
                // clang-format on

                // Iterate over all tags and add to vector
                auto tags = jsonData["tags"];
                for (const auto& t : tags) {
                    cd.tags.push_back(t.asString());
                }

                return cd;
            }
        };

        struct PriceData {
            std::string called_endpoint;
            std::string stock_symbol;
            double latest_price;
        };

        class Price {
        public:
            static std::size_t callback(const char* in,
                                        std::size_t size,
                                        std::size_t num,
                                        std::string* out) {
                const std::size_t totalBytes(size * num);
                out->append(in, totalBytes);
                return totalBytes;
            }

            static PriceData get(const std::string stock_symbol) {
                std::string url = IEX_API_V1_ENDPOINT;
                url += "/stock/" + std::string(stock_symbol) + "/price";

                Json::Value jsonData;
                sendGetRequest(jsonData, url, callback);

                PriceData pd;
                pd.called_endpoint = url;
                pd.stock_symbol = stock_symbol;
                pd.latest_price = jsonData.asDouble();

                return pd;
            }
        };
    }  // namespace Resources
}  // namespace IEX

#endif  // IEX_H_INCLUDED
