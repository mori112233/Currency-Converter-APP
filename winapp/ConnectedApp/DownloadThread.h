#pragma once
#include "CommonObject.h"

/**
 * @class DownloadThread
 * @brief Class representing the thread responsible for downloading currency conversion data.
 */
class DownloadThread
{
public:
    /**
     * @brief Operator function to run the download thread.
     * @param common Reference to the common objects shared between threads.
     */
    void operator()(CommonObjects& common);

    /**
     * @brief Sets the URL for downloading the data.
     * @param new_url New URL for downloading data.
     */
    void SetUrl(std::string_view new_url);

private:
    std::string _download_url; /**< URL for downloading data */
};
