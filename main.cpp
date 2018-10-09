#include "IEX.h"

using namespace std;

void print_price(const std::string& symbol) {
    IEX::PriceData stock;
    stock = IEX::Stock::getPrice(symbol);

    cout << "Called Endpoint: " << stock.called_endpoint << endl;
    cout << "Stock Symbol: " << stock.stock_symbol << endl;
    cout << "Latest Price: $" << stock.latest_price << endl;
}

void print_company(const std::string& symbol) {
    IEX::CompanyData cd = IEX::Stock::getCompany(symbol);
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
    IEX::CompanyLogoData cld = IEX::Stock::getCompanyLogo(symbol);

    cout << "Called Endpoint: " << cld.called_endpoint << endl;
    cout << "Stock Symbol: " << cld.stock_symbol << endl;
    cout << "Company Logo URL: " << cld.logo_url << endl;
}

void print_stats(const std::string& symbol) {
    IEX::KeyStatsData ksd = IEX::Stock::getKeyStats(symbol);
    cout << "Called Endpoint: " << ksd.called_endpoint << endl;
    cout << "Company Name: " << ksd.company_name << endl;
    cout << "marketcap: " << ksd.market_cap << endl;
    cout << "beta: " << ksd.beta << endl;
    cout << "week52high: " << ksd.week_52_high << endl;
    cout << "week52low: " << ksd.week_52_low << endl;
    cout << "week52change: " << ksd.week_52_change << endl;
    cout << "shortInterest: " << ksd.short_interest << endl;
    cout << "shortDate: " << ksd.short_date << endl;
    cout << "dividendRate: " << ksd.dividend_rate << endl;
    cout << "dividendYield: " << ksd.dividend_yield << endl;
    cout << "exDividendDate: " << ksd.ex_dividend_date << endl;
    cout << "latestEPS: " << ksd.latest_EPS << endl;
    cout << "latestEPSDate: " << ksd.latest_EPS_date << endl;
    cout << "sharesOutstanding: " << ksd.shares_outstanding << endl;
    cout << "_float: " << ksd._float << endl;
    cout << "returnOnEquity: " << ksd.return_on_equity << endl;
    cout << "consensusEPS: " << ksd.consensus_EPS << endl;
    cout << "numberOfEstimates: " << ksd.number_of_estimates << endl;
    cout << "EBITDA: " << ksd.EBITDA << endl;
    cout << "revenue: " << ksd.revenue << endl;
    cout << "grossProfit: " << ksd.gross_profit << endl;
    cout << "cash: " << ksd.cash << endl;
    cout << "debt: " << ksd.debt << endl;
    cout << "ttmEPS: " << ksd.ttm_EPS << endl;
    cout << "revenuePerShare: " << ksd.revenue_per_share << endl;
    cout << "revenuePerEmployee: " << ksd.revenue_per_employee << endl;
    cout << "peRatioHigh: " << ksd.pe_ratio_high << endl;
    cout << "peRatioLow: " << ksd.pe_ratio_low << endl;
    cout << "EPSSurpriseDollar: " << ksd.EPS_surprise_dollar << endl;
    cout << "EPSSurprisePercent: " << ksd.EPS_surprise_percent << endl;
    cout << "returnOnAssets: " << ksd.return_on_assets << endl;
    cout << "returnOnCapital: " << ksd.return_on_capital << endl;
    cout << "profitMargin: " << ksd.profit_margin << endl;
    cout << "priceToSales: " << ksd.price_to_sales << endl;
    cout << "priceToBook: " << ksd.price_to_book << endl;
    cout << "day200MovingAvg: " << ksd.day_200_moving_avg << endl;
    cout << "day50MovingAvg: " << ksd.day_50_moving_avg << endl;
    cout << "institutionPercent: " << ksd.institution_percent << endl;
    cout << "insiderPercent: " << ksd.insider_percent << endl;
    cout << "shortRatio: " << ksd.short_ratio << endl;
    cout << "year5ChangePercent: " << ksd.year_5_change_percent << endl;
    cout << "year2ChangePercent: " << ksd.year_2_change_percent << endl;
    cout << "year1ChangePercent: " << ksd.year_1_change_percent << endl;
    cout << "ytdChangePercent: " << ksd.ytd_change_percent << endl;
    cout << "month6ChangePercent: " << ksd.month_6_change_percent << endl;
    cout << "month3ChangePercent: " << ksd.month_3_change_percent << endl;
    cout << "month1ChangePercent: " << ksd.month_1_change_percent << endl;
    cout << "day5ChangePercent: " << ksd.day_5_change_percent << endl;
}

void print_financials(const std::string& symbol,
                      const IEX::Period period) {
    auto financials = IEX::Stock::getFinancials(symbol, period);
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
void print_dividends(const std::string& symbol, const std::string& range) {
    IEX::DividendsData data = IEX::Stock::getDividends(symbol, range);
    cout << "Called Endpoint: " << data.called_endpoint << endl;
    cout << "Number of dividends: " << data.number_of_dividends << endl;
    int i = 1;
    for (const IEX::Dividend& dividend : data.dividends) {
        cout << "Dividend #" << i << endl;
        i = i + 1;
        cout << "\texDate: " << dividend.ex_date << endl;
        cout << "\tPayment Date: " << dividend.payment_date << endl;
        cout << "\tRecord Date: " << dividend.record_date << endl;
        cout << "\tDeclared Date: " << dividend.declared_date << endl;
        cout << "\tAmount: " << dividend.amount << endl;
        cout << "\tFlag: " << dividend.flag << endl;
        cout << "\tType: " << dividend.type << endl;
        cout << "\tQualified: " << dividend.qualified << endl;
        cout << "\tIndicated: " << dividend.indicated << endl;
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
    cout << " 6. Stock/Company Dividends" << endl;
    cout << " 0. Quit\n\n" << endl;
}


void print_menu(const std::string& symbol) {
    int choice;
    menu_options(symbol);
    std::cin >> choice;

    while (choice != 0) {
        switch(choice) {
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
           print_financials(symbol, IEX::Period::annual);
           break;
        case 6:
           print_dividends(symbol,"3m");
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
   print_financials(symbol, IEX::Period::annual);
   print_dividends(symbol, "3m");
}

int main(int argc, char* argv[]) {
    if (argc == 3) {
        std::string symbol = argv[1];
        std::string argument = argv[2];

        if (argument == "-c") {
            print_company(symbol);
        } else if (argument == "-l") {
            print_company_logo(symbol);
        } else if (argument == "-p") {
            print_price(symbol);
        } else if (argument == "-s") {
            print_stats(symbol);
        } else if (argument == "-r") {
            print_financials(symbol,
                             IEX::Period::annual);
        } else if (argument == "-a") {
            run_all_methods("AMZN");
        } else {
            std::cout << "Option Invalid" << endl;
        }
        return 0;
    } else {
        print_menu(argv[1]);
        return 1;
    }
}
