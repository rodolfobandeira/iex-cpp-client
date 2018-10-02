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

int main(int argc, char* argv[]) {
    if (argc == 2) {
        std::string symbol = argv[1];
        print_company(symbol);
        print_price(symbol);
        return 0;
    } else {
        cout << "Error! Usage: " << argv[0] << " [stock symbol]" << endl;
        return 1;
    }
}

