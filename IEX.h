#ifdef __APPLE__
#include <json/json.h>  // My MacOS looks for this path. Maybe a new version when installed via HomeBrew?
#else
#include <jsoncpp/json/json.h>  // My Linux looks for this path. How about you?
#endif
#include <curl/curl.h>
#include <cstdint>  // uint64_t, etc.
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
        static std::string getString(const Json::Value& v) {
            if (!v) {
                return "";
            } else {
                return v.asString();
            }
        }

        static uint64_t getUInt64(const Json::Value& v) {
            if (!v) {
                return 0;
            } else {
                return v.asUInt64();
            }
        }

        static int getInt(const Json::Value& v) {
            if (!v) {
                return 0;
            } else {
                return v.asInt();
            }
        }

        static double getDouble(const Json::Value& v) {
            if (!v) {
                return 0;
            } else {
                return v.asDouble();
            }
        }

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

        struct KeyStatsData {
            std::string called_endpoint;
            std::string stock_symbol;
            std::string company_name;
            uint64_t marketcap;
            double beta;
            double week52high;
            double week52low;
            double week52change;
            double shortInterest;
            std::string shortDate;
            double dividendRate;
            double dividendYield;
            std::string exDividendDate;
            double latestEPS;
            std::string latestEPSDate;
            uint64_t sharesOutstanding;
            uint64_t _float;
            double returnOnEquity;
            double consensusEPS;
            int numberOfEstimates;
            uint64_t EBITDA;
            uint64_t revenue;
            uint64_t grossProfit;
            uint64_t cash;
            uint64_t debt;
            double ttmEPS;
            double revenuePerShare;
            double revenuePerEmployee;
            double peRatioHigh;
            double peRatioLow;
            double EPSSurpriseDollar;
            double EPSSurprisePercent;
            double returnOnAssets;
            double returnOnCapital;
            double profitMargin;
            double priceToSales;
            double priceToBook;
            double day200MovingAvg;
            double day50MovingAvg;
            double institutionPercent;
            double insiderPercent;
            double shortRatio;
            double year5ChangePercent;
            double year2ChangePercent;
            double year1ChangePercent;
            double ytdChangePercent;
            double month6ChangePercent;
            double month3ChangePercent;
            double month1ChangePercent;
            double day5ChangePercent;
        };

        class KeyStats {
        public:
            static std::size_t callback(const char* in,
                                        std::size_t size,
                                        std::size_t num,
                                        std::string* out) {
                const std::size_t totalBytes(size * num);
                out->append(in, totalBytes);
                return totalBytes;
            }

            static KeyStatsData get(const std::string stock_symbol) {
                std::string url = IEX_API_V1_ENDPOINT;
                url += "/stock/" + std::string(stock_symbol) + "/stats";

                Json::Value jsonData;
                sendGetRequest(jsonData, url, callback);

                KeyStatsData ksd;

                // clang-format off
                ksd.called_endpoint     = url;
                ksd.stock_symbol        = stock_symbol;
                ksd.company_name        = getString(jsonData["companyName"]);
                ksd.marketcap           = getUInt64(jsonData["marketcap"]);
                ksd.beta                = getDouble(jsonData["beta"]);
                ksd.week52high          = getDouble(jsonData["week52high"]);
                ksd.week52low           = getDouble(jsonData["week52low"]);
                ksd.week52change        = getDouble(jsonData["week52change"]);
                ksd.shortInterest       = getDouble(jsonData["shortInterest"]);
                ksd.shortDate           = getString(jsonData["shortDate"]);
                ksd.dividendRate        = getDouble(jsonData["dividendRate"]);
                ksd.dividendYield       = getDouble(jsonData["dividendYield"]);
                ksd.exDividendDate      = getString(jsonData["exDividentDate"]);
                ksd.latestEPS           = getDouble(jsonData["latestEPS"]);
                ksd.latestEPSDate       = getString(jsonData["latestEPSDate"]);
                ksd.sharesOutstanding   = getUInt64(jsonData["sharedOutstanding"]);
                ksd._float              = getUInt64(jsonData["float"]);
                ksd.returnOnEquity      = getDouble(jsonData["returnOnEquity"]);
                ksd.consensusEPS        = getDouble(jsonData["consensusEPS"]);
                ksd.numberOfEstimates   = getInt(jsonData["numberOfEstimates"]);
                ksd.EBITDA              = getUInt64(jsonData["EBITDA"]);
                ksd.revenue             = getUInt64(jsonData["revenue"]);
                ksd.grossProfit         = getUInt64(jsonData["grossProfit"]);
                ksd.cash                = getUInt64(jsonData["cash"]);
                ksd.debt                = getUInt64(jsonData["debut"]);
                ksd.ttmEPS              = getDouble(jsonData["ttmEPS"]);
                ksd.revenuePerShare     = getDouble(jsonData["revenuePerShare"]);
                ksd.revenuePerEmployee  = getDouble(jsonData["revenuePerEmployee"]);
                ksd.peRatioHigh         = getDouble(jsonData["peRatioHigh"]);
                ksd.peRatioLow          = getDouble(jsonData["peRatioLow"]);
                ksd.EPSSurpriseDollar   = getDouble(jsonData["EPSSurpriseDollar"]);
                ksd.EPSSurprisePercent  = getDouble(jsonData["EPSSurprisePercent"]);
                ksd.returnOnAssets      = getDouble(jsonData["returnOnAssets"]);
                ksd.returnOnCapital     = getDouble(jsonData["returnOnCapital"]);
                ksd.profitMargin        = getDouble(jsonData["profitMargin"]);
                ksd.priceToSales        = getDouble(jsonData["priceToSales"]);
                ksd.priceToBook         = getDouble(jsonData["priceToBook"]);
                ksd.day200MovingAvg     = getDouble(jsonData["day200MovingAvg"]);
                ksd.day50MovingAvg      = getDouble(jsonData["day50MovingAvg"]);
                ksd.institutionPercent  = getDouble(jsonData["institutionPercent"]);
                ksd.insiderPercent      = getDouble(jsonData["insiderPercent"]);
                ksd.shortRatio          = getDouble(jsonData["shortRatio"]);
                ksd.year5ChangePercent  = getDouble(jsonData["year5ChangePercent"]);
                ksd.year2ChangePercent  = getDouble(jsonData["year2ChangePercent"]);
                ksd.year1ChangePercent  = getDouble(jsonData["year1ChangePercent"]);
                ksd.ytdChangePercent    = getDouble(jsonData["ytdChangePercent"]);
                ksd.month6ChangePercent = getDouble(jsonData["month6ChangePercent"]);
                ksd.month3ChangePercent = getDouble(jsonData["month3ChangePercent"]);
                ksd.month1ChangePercent = getDouble(jsonData["month1ChangePercent"]);
                ksd.day5ChangePercent   = getDouble(jsonData["day5ChangePercent"]);
                // clang-format on

                return ksd;
            }
        };

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
