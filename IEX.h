#ifdef __APPLE__
#include <json/json.h>  // My MacOS looks for this path. Maybe a new version when installed via HomeBrew?
#else
#include <jsoncpp/json/json.h>  // My Linux looks for this path. How about you?
#endif
#include <curl/curl.h>
#include <cstdint>  // uint64_t, etc.
#include <iostream>
#include <sstream>
#include <locale>  // std::locale, std::isdigit
#include <memory>  // std::unique_ptr
#include <string>
#include <vector>

#ifndef IEX_H_INCLUDED
#define IEX_H_INCLUDED
#define IEX_API_V1_ENDPOINT "https://api.iextrading.com/1.0"

namespace IEX {

    namespace {
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

            std::unique_ptr<std::string> httpData(new std::string);

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());
            curl_easy_perform(curl);
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
            curl_easy_cleanup(curl);

            std::stringstream ss;
            ss.str(*httpData);
            ss >> jsonData;
        }

        static std::size_t httpRequestToStringCallback(const char* in,
                                    std::size_t size,
                                    std::size_t num,
                                    std::string* out) {
            const std::size_t totalBytes(size * num);
            out->append(in, totalBytes);
            return totalBytes;
        }
    }   

    enum class Period { annual, quarter };

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

    struct KeyStatsData {
        std::string called_endpoint;
        std::string stock_symbol;
        std::string company_name;
        uint64_t market_cap;
        double beta;
        double week_52_high;
        double week_52_low;
        double week_52_change;
        double short_interest;
        std::string short_date;
        double dividend_rate;
        double dividend_yield;
        std::string ex_dividend_date;
        double latest_EPS;
        std::string latest_EPS_date;
        uint64_t shares_outstanding;
        uint64_t _float;
        double return_on_equity;
        double consensus_EPS;
        int number_of_estimates;
        uint64_t EBITDA;
        uint64_t revenue;
        uint64_t gross_profit;
        uint64_t cash;
        uint64_t debt;
        double ttm_EPS;
        double revenue_per_share;
        double revenue_per_employee;
        double pe_ratio_high;
        double pe_ratio_low;
        double EPS_surprise_dollar;
        double EPS_surprise_percent;
        double return_on_assets;
        double return_on_capital;
        double profit_margin;
        double price_to_sales;
        double price_to_book;
        double day_200_moving_avg;
        double day_50_moving_avg;
        double institution_percent;
        double insider_percent;
        double short_ratio;
        double year_5_change_percent;
        double year_2_change_percent;
        double year_1_change_percent;
        double ytd_change_percent;
        double month_6_change_percent;
        double month_3_change_percent;
        double month_1_change_percent;
        double day_5_change_percent;
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

    struct PriceData {
        std::string called_endpoint;
        std::string stock_symbol;
        double latest_price;
    };

    struct Dividend {
        std::string ex_date;
        std::string payment_date;
        std::string record_date;
        std::string declared_date;
        double amount;
        std::string flag;
        std::string type;
        std::string qualified;
        float indicated;
    };

    struct DividendsData {
        std::string called_endpoint;
        int number_of_dividends;
        std::vector<Dividend> dividends;
    };

    struct CompanyLogoData {
        std::string called_endpoint;
        std::string stock_symbol;
        std::string logo_url;
    };

    class Stock {
    public:

        static std::vector<FinancialsData> getFinancials(
            const std::string stock_symbol,
            const Period period) {
            std::string url = IEX_API_V1_ENDPOINT;
            url += "/stock/" + std::string(stock_symbol) +
                   "/financials?period=" +
                   (Period::annual == period ? "annual" : "quarter");

            Json::Value jsonData;
            sendGetRequest(jsonData, url, httpRequestToStringCallback);

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

        static KeyStatsData getKeyStats(const std::string stock_symbol) {
            std::string url = IEX_API_V1_ENDPOINT;
            url += "/stock/" + std::string(stock_symbol) + "/stats";

            Json::Value jsonData;
            sendGetRequest(jsonData, url, httpRequestToStringCallback);

            KeyStatsData ksd;

            // clang-format off
            ksd.called_endpoint        = url;
            ksd.stock_symbol           = stock_symbol;
            ksd.company_name           = getString(jsonData["companyName"]);
            ksd.market_cap             = getUInt64(jsonData["marketcap"]);
            ksd.beta                   = getDouble(jsonData["beta"]);
            ksd.week_52_high           = getDouble(jsonData["week52high"]);
            ksd.week_52_low            = getDouble(jsonData["week52low"]);
            ksd.week_52_change         = getDouble(jsonData["week52change"]);
            ksd.short_interest         = getDouble(jsonData["shortInterest"]);
            ksd.short_date             = getString(jsonData["shortDate"]);
            ksd.dividend_rate          = getDouble(jsonData["dividendRate"]);
            ksd.dividend_yield         = getDouble(jsonData["dividendYield"]);
            ksd.ex_dividend_date       = getString(jsonData["exDividentDate"]);
            ksd.latest_EPS             = getDouble(jsonData["latestEPS"]);
            ksd.latest_EPS_date        = getString(jsonData["latestEPSDate"]);
            ksd.shares_outstanding     = getUInt64(jsonData["sharedOutstanding"]);
            ksd._float                 = getUInt64(jsonData["float"]);
            ksd.return_on_equity       = getDouble(jsonData["returnOnEquity"]);
            ksd.consensus_EPS          = getDouble(jsonData["consensusEPS"]);
            ksd.number_of_estimates    = getInt(jsonData["numberOfEstimates"]);
            ksd.EBITDA                 = getUInt64(jsonData["EBITDA"]);
            ksd.revenue                = getUInt64(jsonData["revenue"]);
            ksd.gross_profit           = getUInt64(jsonData["grossProfit"]);
            ksd.cash                   = getUInt64(jsonData["cash"]);
            ksd.debt                   = getUInt64(jsonData["debut"]);
            ksd.ttm_EPS                = getDouble(jsonData["ttmEPS"]);
            ksd.revenue_per_share      = getDouble(jsonData["revenuePerShare"]);
            ksd.revenue_per_employee   = getDouble(jsonData["revenuePerEmployee"]);
            ksd.pe_ratio_high          = getDouble(jsonData["peRatioHigh"]);
            ksd.pe_ratio_low           = getDouble(jsonData["peRatioLow"]);
            ksd.EPS_surprise_dollar    = getDouble(jsonData["EPSSurpriseDollar"]);
            ksd.EPS_surprise_percent   = getDouble(jsonData["EPSSurprisePercent"]);
            ksd.return_on_assets       = getDouble(jsonData["returnOnAssets"]);
            ksd.return_on_capital      = getDouble(jsonData["returnOnCapital"]);
            ksd.profit_margin          = getDouble(jsonData["profitMargin"]);
            ksd.price_to_sales         = getDouble(jsonData["priceToSales"]);
            ksd.price_to_book          = getDouble(jsonData["priceToBook"]);
            ksd.day_200_moving_avg     = getDouble(jsonData["day200MovingAvg"]);
            ksd.day_50_moving_avg      = getDouble(jsonData["day50MovingAvg"]);
            ksd.institution_percent    = getDouble(jsonData["institutionPercent"]);
            ksd.insider_percent        = getDouble(jsonData["insiderPercent"]);
            ksd.short_ratio            = getDouble(jsonData["shortRatio"]);
            ksd.year_5_change_percent  = getDouble(jsonData["year5ChangePercent"]);
            ksd.year_2_change_percent  = getDouble(jsonData["year2ChangePercent"]);
            ksd.year_1_change_percent  = getDouble(jsonData["year1ChangePercent"]);
            ksd.ytd_change_percent     = getDouble(jsonData["ytdChangePercent"]);
            ksd.month_6_change_percent = getDouble(jsonData["month6ChangePercent"]);
            ksd.month_3_change_percent = getDouble(jsonData["month3ChangePercent"]);
            ksd.month_1_change_percent = getDouble(jsonData["month1ChangePercent"]);
            ksd.day_5_change_percent   = getDouble(jsonData["day5ChangePercent"]);
            // clang-format on

            return ksd;
        }

        static CompanyData getCompany(const std::string stock_symbol) {
            std::string url = IEX_API_V1_ENDPOINT;
            url += "/stock/" + std::string(stock_symbol) + "/company";

            Json::Value jsonData;
            sendGetRequest(jsonData, url, httpRequestToStringCallback);

            CompanyData cd;

            // clang-format off
            cd.called_endpoint = url;
            cd.stock_symbol    = stock_symbol;
            cd.company_name    = getString(jsonData["companyName"]);
            cd.exchange        = getString(jsonData["exchange"]);
            cd.industry        = getString(jsonData["industry"]);
            cd.website         = getString(jsonData["website"]);
            cd.description     = getString(jsonData["description"]);
            cd.CEO             = getString(jsonData["CEO"]);
            cd.issue_type      = getString(jsonData["issue_type"]);
            cd.sector          = getString(jsonData["sector"]);
            // clang-format on

            // Iterate over all tags and add to vector
            auto tags = jsonData["tags"];
            for (const auto& t : tags) {
                cd.tags.push_back(t.asString());
            }

            return cd;
        }

        static PriceData getPrice(const std::string stock_symbol) {
            std::string url = IEX_API_V1_ENDPOINT;
            url += "/stock/" + std::string(stock_symbol) + "/price";

            Json::Value jsonData;
            sendGetRequest(jsonData, url, httpRequestToStringCallback);

            PriceData pd;
            pd.called_endpoint = url;
            pd.stock_symbol = stock_symbol;
            pd.latest_price = jsonData.asDouble();

            return pd;
        }

        // Input:
        //  stock_symbol - the stock symbol you want to query
        //  time_period - the time period you want to look in.  Allowed
        //  values are: 5y, 2y, 1y, ytd, 6m, 3m, and 1m
        //
        // Output:
        //  Will returns a DividendsData struct with the relevant info
        //  on success or an empty struct with the success field set to
        //  false
        static DividendsData getDividends(const std::string stock_symbol,
                                         const std::string time_period) {
            std::string url = std::string(IEX_API_V1_ENDPOINT) +
                              "/stock/" +
                              std::string(stock_symbol) +
                              "/dividends/" +
                              std::string(time_period);

            Json::Value json_data;
            sendGetRequest(json_data, url, httpRequestToStringCallback);

            DividendsData dividends_data;

            dividends_data.called_endpoint = url;
            dividends_data.number_of_dividends = json_data.size();
            std::vector<Dividend> dividends;
            auto beginning = dividends.begin();

            for (const auto& dividend_json : json_data) {
                Dividend dividend;
                dividend.ex_date = getString(dividend_json["exDate"]);

                dividend.payment_date = getString(dividend_json["paymentDate"]);
                dividend.record_date = getString(dividend_json["recordDate"]);
                dividend.declared_date = getString(dividend_json["declaredDate"]);
                dividend.amount = getDouble(dividend_json["amount"]);
                dividend.flag = getString(dividend_json["flag"]);
                dividend.type = getString(dividend_json["type"]);
                dividend.qualified = getString(dividend_json["qualified"]);
                std::string indicated = getString(dividend_json["indicated"]);

                if (indicated.length() == 0) {
                    dividend.indicated = 0.0;
                } else {
                    dividend.indicated = std::stof(indicated);
                }

                beginning = dividends.insert(beginning, dividend);
            }

            dividends_data.dividends = dividends;
            return dividends_data;
        }

        static CompanyLogoData getCompanyLogo(const std::string& stock_symbol) {
                std::string url = IEX_API_V1_ENDPOINT;
                url += "/stock/" + stock_symbol + "/logo";

                Json::Value json_data;
                sendGetRequest(json_data, url, httpRequestToStringCallback);

                CompanyLogoData data;
                data.called_endpoint = url;
                data.stock_symbol = stock_symbol;
                data.logo_url = getString(json_data["url"]);

                return data;
            }
    };
}  // namespace IEX

#endif  // IEX_H_INCLUDED
