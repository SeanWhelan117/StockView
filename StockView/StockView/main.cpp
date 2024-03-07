#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <iostream>
#include "LoadFromFile.h"


using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams


int main()
{
    LoadFromFile loader;

    std::string currentAPIKey = loader.LoadAPIKey();
    std::cout << currentAPIKey << std::endl;

    

    return 0;
}