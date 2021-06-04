#pragma once
#include <fstream>
#include <sstream>


#include "platform/types.h"

namespace jas {

namespace platform {

/**
 * @brief Reads the feed information from the file 
 */
class FileFeedGetter {
public:
    FileFeedGetter(std::string file_addr) : m_file_in_stream(file_addr) {
    }

    // Gets the feed information and publishes it
    FeedEventInfo parseFeedEventInfo();

    bool getFeedString();


private:
    std::ifstream m_file_in_stream;
    std::string m_feed_str;
};

/**
 * @brief Parses the feed information of the feed getter
 * 
 * @return FeedEventInfo 
 */
FeedEventInfo FileFeedGetter::parseFeedEventInfo() {
    std::stringstream ss(m_feed_str);

    Time timestamp;
    price_t price;
    ss >> timestamp;
    ss.ignore();
    ss >> price;
    return FeedEventInfo{timestamp, price};
}

/**
 * @brief Get the Feed String object
 * When this function returns true, the event loop will automatically close itself
 * 
 * @return true if the feed string has been parsed.
 */
bool FileFeedGetter::getFeedString() {
    return static_cast<bool>(getline(m_file_in_stream, m_feed_str));
}

} // namespace platform
} // namespace jas
