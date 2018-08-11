#include "IEX.h"

using namespace std;

int main(int argc, char *argv[]) {
    IEX::Resources::PriceData stock;
    stock = IEX::Resources::Price::get(string(argv[1]));

    cout << "Called Endpoint: " << stock.called_endpoint << endl;
    cout << "Stock Symbol: " << stock.stock_symbol << endl;
    cout << "Latest Price: $" << stock.latest_price << endl;

    return 0;
}

