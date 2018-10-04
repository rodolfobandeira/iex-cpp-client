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

void print_company_logo(const std::string& symbol) {
    IEX::Resources::CompanyLogoData cld =
        IEX::Resources::CompanyLogo::get(symbol);

    cout << "Called Endpoint: " << cld.called_endpoint << endl;
    cout << "Stock Symbol: " << cld.stock_symbol << endl;
    cout << "Company Logo URL: " << cld.logo_url << endl;
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

void print_financials(const std::string& symbol,
                      const IEX::Resources::Financials::Period period) {
    auto financials = IEX::Resources::Financials::get(symbol, period);
    for (const auto& f : financials) {
        cout << "called_endpoint: " << f.called_endpoint << endl;
        cout << "stock_symbol: " << f.stock_symbol << endl;
        cout << "report_date: " << f.report_date << endl;
        cout << "gross_profit: " << f.gross_profit << endl;
        cout << "operating_revenue: " << f.operating_revenue << endl;
        cout << "total_revenue: " << f.total_revenue << endl;
        cout << "operating_income: " << f.operating_income << endl;
        cout << "net_income: " << f.net_income << endl;
        cout << "research_and_development: " << f.research_and_development
             << endl;
        cout << "operating_expense: " << f.operating_expense << endl;
        cout << "current_assets: " << f.current_assets << endl;
        cout << "total_assets: " << f.total_assets << endl;
        cout << "total_liabilities: " << f.total_liabilities << endl;
        cout << "current_cash: " << f.current_cash << endl;
        cout << "current_debt: " << f.current_debt << endl;
        cout << "total_cash: " << f.total_cash << endl;
        cout << "total_debt: " << f.total_debt << endl;
        cout << "shareholder_equity: " << f.shareholder_equity << endl;
        cout << "cash_change: " << f.cash_change << endl;
        cout << "cash_flow: " << f.cash_flow << endl;
        cout << "operating_gains_losses: " << f.operating_gains_losses << endl;
    }
}

void menu_options(const std::string& symbol) {
    cout << "\n--------------------------------------------------" << endl;
    cout << "OPTIONS for [" + symbol + "]" << endl;
    cout << " 1. Company Information" << endl;
    cout << " 2. Stock/Company Logo" << endl;
    cout << " 3. Stock/Company Latest Price" << endl;
    cout << " 4. Stock/Company Statistics" << endl;
    cout << " 5. Stock/Company Financial Reports" << endl;
    cout << " 0. Quit\n\n" << endl;
}

void print_menu(const std::string& symbol) {
    int choice;
    menu_options(symbol);
    std::cin >> choice;

    while (choice != 0) {
        switch (choice) {
            case 1:
                print_company(symbol);
                break;
            case 2:
                print_company_logo(symbol);
                break;
            case 3:
                print_price(symbol);
                break;
            case 4:
                print_stats(symbol);
                break;
            case 5:
                print_financials(symbol,
                                 IEX::Resources::Financials::Period::annual);
                break;
            case 0:
                std::cout << "Bye!" << endl;
                break;
            default:
                std::cout << "Invalid Option" << endl;
                break;
        }
        cin.clear();
        menu_options(symbol);
        std::cin >> choice;
    }
}

void run_all_methods(const std::string& symbol) {
    print_company(symbol);
    print_company_logo(symbol);
    print_price(symbol);
    print_stats(symbol);
    print_financials(symbol, IEX::Resources::Financials::Period::annual);
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        std::string symbol = argv[1];

        if (symbol == "TRAVIS_CI") {
            run_all_methods("AMZN");
        } else {
            print_menu(symbol);
            return 0;
        }

    } else {
        cout << "Error! Usage: " << argv[0] << " [stock symbol]" << endl;
        return 1;
    }
}
