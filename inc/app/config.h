//
// Created by enderoff on 26.02.23.
//

#ifndef APP_CONFIG_H
#define APP_CONFIG_H
namespace MyApp {
    struct {
        int width = 640;
        int height = 480;
        const char* window_title = "Dickometor";
        const char* version = "dev";

        const char* GET_STATUS_URL = "http://localhost:3000/status";
        const char* GET_TOP_URL = "http://localhost:3000/top";
        const char* POST_RESULT_URL = "http://localhost:3000/result";
    } config;
}
#endif //APP_CONFIG_H
