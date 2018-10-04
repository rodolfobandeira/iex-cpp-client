#ifdef __APPLE__
#include <json/json.h>  // My MacOS looks for this path. Maybe a new version when installed via HomeBrew?
#else
#include <jsoncpp/json/json.h>  // My Linux looks for this path. How about you?
#endif
#include <curl/curl.h>
#include <cstdint>  // uint64_t, etc.
#include <functional>
#include <iostream>
#include <locale>  // std::locale, std::isdigit
#include <memory>  // std::unique_ptr
#include <sstream>
#include <string>
#include <vector>

#ifndef IEX_H_INCLUDED
#define IEX_H_INCLUDED

namespace IEX {
    namespace Resources {
        static std::string getString(const Json::Value& v) {
            if (!v) {
                return "";
            } else {
                return v.asString();
            }
        }

        static int64_t getInt64(const Json::Value& v) {
            if (!v) {
                return 0;
            } else {
                return v.asInt64();
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

        using Callback = std::function<
            std::size_t(const char*, std::size_t, std::size_t, std::string*)>;

        static std::size_t defaultCallback(const char* in,
                                           std::size_t size,
                                           std::size_t num,
                                           std::string* out) {
            const std::size_t totalBytes(size * num);
            out->append(in, totalBytes);
            return totalBytes;
        }

        static const std::string IEX_API_V1_ENDPOINT{
            "https://api.iextrading.com/1.0"};

        static Json::Value sendGetRequest(const std::string& url,
                                          Callback callback = defaultCallback) {
            CURL* curl = curl_easy_init();

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            long int httpCode(0);

            std::unique_ptr<std::string> httpData(new std::string);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
            curl_easy_perform(curl);
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
            curl_easy_cleanup(curl);

            std::stringstream ss;
            ss.str(*httpData);

            Json::Value jsonData;
            ss >> jsonData;
            return jsonData;
        }

        struct FinancialsData {
            std::string called_endpoint;
            std::string stock_symbol;
            std::string report_date;
            int64_t gross_profit;
            int64_t operating_revenue;
            int64_t total_revenue;
            int64_t operating_income;
            int64_t net_income;
            int64_t research_and_development;
            int64_t operating_expense;
            int64_t current_assets;
            int64_t total_assets;
            int64_t total_liabilities;
            int64_t current_cash;
            int64_t current_debt;
            int64_t total_cash;
            int64_t total_debt;
            int64_t shareholder_equity;
            int64_t cash_change;
            int64_t cash_flow;
            std::string operating_gains_losses;
        };

        class Financials {
        public:
            enum class Period { annual, quarter };

            static std::vector<FinancialsData> get(
                const std::string& stock_symbol,
                const Period period) {
                std::string url = IEX_API_V1_ENDPOINT;
                url += "/stock/" + stock_symbol + "/financials?period=" +
                       (Period::annual == period ? "annual" : "quarter");

                Json::Value jsonData = sendGetRequest(url);

                FinancialsData fd;
                fd.called_endpoint = url;
                fd.stock_symbol = stock_symbol;

                std::vector<FinancialsData> results;
                for (const auto& f : jsonData["financials"]) {
                    FinancialsData fd;

                    // clang-format off
                    fd.report_date              = getString(f["reportDate"]);
                    fd.gross_profit             = getInt64(f["grossProfit"]);
                    fd.operating_revenue        = getInt64(f["operatingRevenue"]);
                    fd.total_revenue            = getInt64(f["totalRevenue"]);
                    fd.operating_income         = getInt64(f["operatingIncome"]);
                    fd.net_income               = getInt64(f["netIncome"]);
                    fd.research_and_development = getInt64(f["researchAndDevelopment"]);
                    fd.operating_expense        = getInt64(f["operatingExpense"]);
                    fd.current_assets           = getInt64(f["currentAssets"]);
                    fd.total_assets             = getInt64(f["totalAssets"]);
                    fd.total_liabilities        = getInt64(f["totalLiabilities"]);
                    fd.current_cash             = getInt64(f["currentCash"]);
                    fd.current_debt             = getInt64(f["currentDebt"]);
                    fd.total_cash               = getInt64(f["totalCash"]);
                    fd.total_debt               = getInt64(f["totalDebt"]);
                    fd.shareholder_equity       = getInt64(f["shareholderEquity"]);
                    fd.cash_change              = getInt64(f["cashChange"]);
                    fd.cash_flow                = getInt64(f["cashFlow"]);
                    fd.operating_gains_losses   = getString(f["operatingGainsLosses"]);
                    // clang-format on

                    results.push_back(fd);
                }
                return results;
            }
        };

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
            static KeyStatsData get(const std::string& stock_symbol) {
                std::string url = IEX_API_V1_ENDPOINT;
                url += "/stock/" + stock_symbol + "/stats";

                Json::Value jsonData = sendGetRequest(url);

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
            static CompanyData get(const std::string& stock_symbol) {
                std::string url = IEX_API_V1_ENDPOINT;
                url += "/stock/" + stock_symbol + "/company";

                Json::Value jsonData = sendGetRequest(url);

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
            static PriceData get(const std::string& stock_symbol) {
                std::string url = IEX_API_V1_ENDPOINT;
                url += "/stock/" + stock_symbol + "/price";

                Json::Value jsonData = sendGetRequest(url);

                PriceData pd;
                pd.called_endpoint = url;
                pd.stock_symbol = stock_symbol;
                pd.latest_price = jsonData.asDouble();

                return pd;
            }
        };

        struct CompanyLogoData {
            std::string called_endpoint;
            std::string stock_symbol;
            std::string logo_url;
        };

        class CompanyLogo {
        public:
            static CompanyLogoData get(const std::string& stock_symbol) {
                std::string url = IEX_API_V1_ENDPOINT;
                url += "/stock/" + stock_symbol + "/logo";

                Json::Value jsonData = sendGetRequest(url);

                CompanyLogoData data;
                data.called_endpoint = url;
                data.stock_symbol = stock_symbol;
                data.logo_url = jsonData["url"].asString();

                return data;
            }
        };
    }  // namespace Resources
}  // namespace IEX

#endif  // IEX_H_INCLUDED
