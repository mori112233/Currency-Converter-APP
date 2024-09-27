#include "DownloadThread.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "nlohmann/json.hpp"
#include <chrono>
#include <thread>

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CurrencyConversion, from_currency, to_currency, conversion_rate)

/**
 * @brief Operator function to run the download thread.
 * Fetches currency conversion data periodically and updates the common objects.
 * @param common Reference to the common objects shared between threads.
 */
    void DownloadThread::operator()(CommonObjects& common)
{
    httplib::Client cli("https://open.er-api.com");

    while (!common.exit_flag)
    {
        auto res = cli.Get("/v6/latest/USD"); // Use the provided endpoint
        if (res && res->status == 200)
        {
            auto json_result = nlohmann::json::parse(res->body);
            std::vector<CurrencyConversion> new_conversions;
            for (auto& [key, value] : json_result["rates"].items())
            {
                new_conversions.push_back({ "USD", key, value });
            }
            {
                std::lock_guard<std::mutex> lock(common.mutex);
                common.conversions = std::move(new_conversions);
                common.data_ready = true;
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(60)); // Fetch data every 60 seconds
    }
}

/**
 * @brief Sets the URL for downloading the data.
 * @param new_url New URL for downloading data.
 */
void DownloadThread::SetUrl(std::string_view new_url)
{
    _download_url = new_url;
}
