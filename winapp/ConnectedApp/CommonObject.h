#pragma once
#include <atomic>
#include <string>
#include <vector>
#include <mutex>

/**
 * @struct CurrencyConversion
 * @brief Structure to store currency conversion data.
 */
struct CurrencyConversion
{
    std::string from_currency; /**< Source currency */
    std::string to_currency; /**< Target currency */
    double conversion_rate; /**< Conversion rate from source to target currency */
};

/**
 * @struct CommonObjects
 * @brief Structure to store common objects shared between threads.
 */
struct CommonObjects
{
    std::atomic_bool exit_flag = false; /**< Flag to indicate when to exit */
    std::atomic_bool start_download = false; /**< Flag to start download */
    std::atomic_bool data_ready = false; /**< Flag to indicate data is ready */
    std::string url; /**< URL for downloading data */
    std::vector<CurrencyConversion> conversions; /**< List of currency conversions */
    std::mutex mutex; /**< Mutex to protect shared data */
};
