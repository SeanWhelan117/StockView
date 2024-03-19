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


void getIntradayData(std::string t_APIKey, std::string t_symbol, std::string t_interval)
{
    const string_t APIKey = conversions::to_string_t(t_APIKey);
    const string_t symbol = conversions::to_string_t(t_symbol);
    const string_t interval = conversions::to_string_t(t_interval);


    uri_builder builder(U("https://www.alphavantage.co/query"));
    builder.append_query(U("function"), U("TIME_SERIES_INTRADAY"));
    builder.append_query(U("symbol"), symbol);
    builder.append_query(U("interval"), interval);
    builder.append_query(U("datatype"), U("json"));
    builder.append_query(U("apikey"), APIKey);

    std::wcout << "Final URI: " << builder.to_uri().to_string() << std::endl;

    http_client client(builder.to_uri());
    client.request(methods::GET).then([](http_response t_response) 
    {
        if (t_response.status_code() == status_codes::OK)//if 200 / okay
        {
            std::cout << "OK!" << std::endl;

            auto json_body = t_response.extract_json().get(); //Parse JSON Response

            //std::wcout << L"JSON response:\n" << json_body.serialize() << std::endl;

            try {
                auto series = json_body.at(U("Time Series (5min)")).as_object();
                for (const auto& entry : series)
                {
                    std::wcout << L"Timestamp: " << entry.first << std::endl;

                    std::wcout << L"Open: " << entry.second.at(U("1. open")).as_string() << std::endl;

                    std::wcout << L"High: " << entry.second.at(U("2. high")).as_string() << std::endl;
                    std::wcout << L"Low: " << entry.second.at(U("3. low")).as_string() << std::endl;

                    std::wcout << L"Close: " << entry.second.at(U("4. close")).as_string() << std::endl;

                    std::wcout << L"Volume: " << entry.second.at(U("5. volume")).as_string() << std::endl;
                    std::wcout << std::endl;
                 }
            }
            catch (const json::json_exception& e) {
                std::cerr << "Error accessing JSON key: " << e.what() << std::endl;
            }

        }
        else 
        {
            std::cerr << "Failed to fetch the data from the API, status code: " << t_response.status_code() << std::endl;
        }

    }).wait();


}

int main()
{
    char answer;
    std::string symbol, interval;

    LoadFromFile loader;

    std::string currentAPIKey = loader.LoadAPIKey();
    std::cout << "Your API Key is: " << currentAPIKey << std::endl;

    std::cout << "Would you like intraday data" << std::endl;
    std::cout << "Y/N" << std::endl;

    std::cin >> answer;

    if (answer == 'Y' || answer == 'y')
    {
        std::cout << "Please enter a symbol from the API list that matches the stock / ETF you want data on" << std::endl;
        std::cin >> symbol;

        std::cout << "Please enter an approved interval between the data points 1min, 5min, 15min, 30min, 60min" << std::endl;
        std::cin >> interval;

        getIntradayData(currentAPIKey,symbol , interval);
    }
    
    return 0;
}