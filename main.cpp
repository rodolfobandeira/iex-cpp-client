#include "IEX.h"

using namespace std;

void print_price(const std::string& symbol) {
    IEX::Resources::PriceData stock;
    stock = IEX::Resources::Price::get(symbol);

    cout << "Called Endpoint: " << stock.called_endpoint << endl;
    cout << "Stock Symbol: " << stock.stock_symbol << endl;
    cout << "Latest Price: $" << stock.latest_price << endl;
}

void print_company(const std::string& symbol) {
    IEX::Resources::CompanyData cd = IEX::Resources::Company::get(symbol);
    cout << "Called Endpoint: " << cd.called_endpoint << endl;
    cout << "Company Name: " << cd.company_name << endl;
    cout << "Exchange: " << cd.exchange << endl;
    cout << "Industry: " << cd.industry << endl;
    cout << "Website: " << cd.website << endl;
    cout << "Description: " << cd.description << endl;
    cout << "CEO: " << cd.CEO << endl;
    cout << "Issue type: " << cd.issue_type << endl;
    cout << "Sector: " << cd.sector << endl;
    cout << "Tags:" << endl;
    for (const auto& t : cd.tags) {
        cout << "  " << t << endl;
    }
}
void print_stats(const std::string& symbol) {
    IEX::Resources::KeyStatsData ksd = IEX::Resources::KeyStats::get(symbol);
    cout << "Called Endpoint: " << ksd.called_endpoint << endl;
    cout << "Company Name: " << ksd.company_name << endl;
    cout << "marketcap: " << ksd.marketcap << endl;
    cout << "beta: " << ksd.beta << endl;
    cout << "week52high: " << ksd.week52high << endl;
    cout << "week52low: " << ksd.week52low << endl;
    cout << "week52change: " << ksd.week52change << endl;
    cout << "shortInterest: " << ksd.shortInterest << endl;
    cout << "shortDate: " << ksd.shortDate << endl;
    cout << "dividendRate: " << ksd.dividendRate << endl;
    cout << "dividendYield: " << ksd.dividendYield << endl;
    cout << "exDividendDate: " << ksd.exDividendDate << endl;
    cout << "latestEPS: " << ksd.latestEPS << endl;
    cout << "latestEPSDate: " << ksd.latestEPSDate << endl;
    cout << "sharesOutstanding: " << ksd.sharesOutstanding << endl;
    cout << "_float: " << ksd._float << endl;
    cout << "returnOnEquity: " << ksd.returnOnEquity << endl;
    cout << "consensusEPS: " << ksd.consensusEPS << endl;
    cout << "numberOfEstimates: " << ksd.numberOfEstimates << endl;
    cout << "EBITDA: " << ksd.EBITDA << endl;
    cout << "revenue: " << ksd.revenue << endl;
    cout << "grossProfit: " << ksd.grossProfit << endl;
    cout << "cash: " << ksd.cash << endl;
    cout << "debt: " << ksd.debt << endl;
    cout << "ttmEPS: " << ksd.ttmEPS << endl;
    cout << "revenuePerShare: " << ksd.revenuePerShare << endl;
    cout << "revenuePerEmployee: " << ksd.revenuePerEmployee << endl;
    cout << "peRatioHigh: " << ksd.peRatioHigh << endl;
    cout << "peRatioLow: " << ksd.peRatioLow << endl;
    cout << "EPSSurpriseDollar: " << ksd.EPSSurpriseDollar << endl;
    cout << "EPSSurprisePercent: " << ksd.EPSSurprisePercent << endl;
    cout << "returnOnAssets: " << ksd.returnOnAssets << endl;
    cout << "returnOnCapital: " << ksd.returnOnCapital << endl;
    cout << "profitMargin: " << ksd.profitMargin << endl;
    cout << "priceToSales: " << ksd.priceToSales << endl;
    cout << "priceToBook: " << ksd.priceToBook << endl;
    cout << "day200MovingAvg: " << ksd.day200MovingAvg << endl;
    cout << "day50MovingAvg: " << ksd.day50MovingAvg << endl;
    cout << "institutionPercent: " << ksd.institutionPercent << endl;
    cout << "insiderPercent: " << ksd.insiderPercent << endl;
    cout << "shortRatio: " << ksd.shortRatio << endl;
    cout << "year5ChangePercent: " << ksd.year5ChangePercent << endl;
    cout << "year2ChangePercent: " << ksd.year2ChangePercent << endl;
    cout << "year1ChangePercent: " << ksd.year1ChangePercent << endl;
    cout << "ytdChangePercent: " << ksd.ytdChangePercent << endl;
    cout << "month6ChangePercent: " << ksd.month6ChangePercent << endl;
    cout << "month3ChangePercent: " << ksd.month3ChangePercent << endl;
    cout << "month1ChangePercent: " << ksd.month1ChangePercent << endl;
    cout << "day5ChangePercent: " << ksd.day5ChangePercent << endl;
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        std::string symbol = argv[1];
        print_company(symbol);
        print_price(symbol);
        print_stats(symbol);
        return 0;
    } else {
        cout << "Error! Usage: " << argv[0] << " [stock symbol]" << endl;
        return 1;
    }
}

