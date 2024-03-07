#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <cpprest/containerstream.h>

#include <iostream>
#include "LoadFromFile.h"

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams


void getIntradayData(std::string t_APIKey)
{
    const string_t APIKey = conversions::to_string_t(t_APIKey);

    uri_builder builder(U("https://www.alphavantage.co/query"));
    builder.append_query(U("function"), U("TIME_SERIES_INTRADAY"));
    builder.append_query(U("symbol"), U("LSE")); // London Stock Exchange
    builder.append_query(U("interval"), U("30min"));
    builder.append_query(U("datatype"), U("csv"));
    builder.append_query(U("apikey"), APIKey);

    http_client client(builder.to_uri());
    client.request(methods::GET).then([](http_response t_response) 
    {

    }).wait();


}

int main()
{
    char answer;

    LoadFromFile loader;

    std::string currentAPIKey = loader.LoadAPIKey();
    std::cout << currentAPIKey << std::endl;

    std::cout << "Would you like intraday data" << std::endl;
    std::cin >> answer;

    if (answer == 'Y' || answer == 'y')
    {
        getIntradayData(currentAPIKey);
    }
    
    

    return 0;
}