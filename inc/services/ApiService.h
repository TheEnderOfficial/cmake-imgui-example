//
// Created by enderoff on 26.02.23.
//

#ifndef APP_APISERVICE_H
#define APP_APISERVICE_H

#include <string>
#include <memory>
#include <json/json.h>

namespace ApiService {

    struct ApiResponse {
        Json::Value jsonData;
        int httpCode;
    };
    class ApiService {
    public:
        static ApiResponse get(const char* url);
    };
}
#endif //APP_APISERVICE_H
