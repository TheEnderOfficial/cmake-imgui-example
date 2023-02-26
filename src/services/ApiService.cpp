//
// Created by enderoff on 26.02.23.
//
#include "../../inc/services/ApiService.h"
#include "../../inc/app/config.h"
#include <cstdlib>
#include <time.h>
#include <curl/curl.h>
#include <string>
#include <cstring>
#include <memory>
#include <json/json.h>

#define JSON_USE_EXCEPTION 1


namespace ApiService {
    std::size_t callback(
            const char* in,
            std::size_t size,
            std::size_t num,
            std::string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }

    ApiResponse ApiService::get(const char *url) {

        CURL *curl = curl_easy_init();

        // Set remote URL.
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Don't bother trying IPv6, which would increase DNS resolution time.
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

        // Don't wait forever, time out after 10 seconds.
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

        // Follow HTTP redirects if necessary.
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // Response information.
        long httpCode(0);
        std::unique_ptr<std::string> httpData(new std::string());

        // Hook up data handling function.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

        // Hook up data container (will be passed as the last parameter to the
        // callback handling function).  Can be any pointer type, since it will
        // internally be passed as a void pointer.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

        // Run our HTTP GET command, capture the HTTP response code, and clean up.
        int curl_code = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);
        Json::Value val;

        switch (curl_code) {
            case CURLE_OK:
                break;
            case CURLE_FAILED_INIT: 
                val["status"] = "curl failed init";
                val["version"] = "failed to fetch";
                return {val, -100};
            case CURLE_COULDNT_CONNECT:
                val["status"] = "curl couldn`t connect to server";
                val["version"] = "failed to fetch";
                return {val, -100};
            default:
                val["status"] = "unknown error";
                val["version"] = "failed to fetch";
                return {val, -100};
                break;
        }

        try {
            Json::Value jsonData;
            Json::Reader jsonReader;

            if (httpCode < 200 || httpCode > 300) {
                return {NULL, -100};
            }



            if (jsonReader.parse(*httpData.get(), jsonData)) {
                printf("GET %s\n", url);
                printf("HTTP Code %d\n", httpCode);
                printf("JSON %s\n", jsonData.toStyledString().c_str());
                return {jsonData, (int)httpCode};
            }
            else {
                Json::Value val;
                val["status"] = "no connection";
                val["version"] = "failed";
                return {val, -100};
            }
        }

        catch (std::exception* e) {
            Json::Value val;
            val["status"] = "no connection";
            val["version"] = "failed";
            return {val, -100};

        }

    }

    ApiResponse ApiService::post(const char *url, Json::Value body) {
        CURL *curl = curl_easy_init();

        // Set remote URL.
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Don't bother trying IPv6, which would increase DNS resolution time.
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

        // Don't wait forever, time out after 10 seconds.
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

        // Follow HTTP redirects if necessary.
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        char buf[128];
        sprintf(buf, "%s", body.toStyledString().c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, buf);
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Response information.
        long httpCode(0);
        std::unique_ptr<std::string> httpData(new std::string());

        // Hook up data handling function.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

        // Hook up data container (will be passed as the last parameter to the
        // callback handling function).  Can be any pointer type, since it will
        // internally be passed as a void pointer.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

        // Run our HTTP GET command, capture the HTTP response code, and clean up.
        int curl_code = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);
        Json::Value val;

        switch (curl_code) {
            case CURLE_OK:
                break;
            case CURLE_FAILED_INIT:
                val["status"] = "curl failed init";
                val["version"] = "failed to fetch";
                return {val, -100};
            case CURLE_COULDNT_CONNECT:
                val["status"] = "curl couldn`t connect to server";
                val["version"] = "failed to fetch";
                return {val, -100};
            default:
                val["status"] = "unknown error";
                val["version"] = "failed to fetch";
                return {val, -100};
                break;
        }

        try {
            Json::Value jsonData;
            Json::Reader jsonReader;

            if (httpCode < 200 || httpCode > 300) {
                return {NULL, -100};
            }



            if (jsonReader.parse(*httpData.get(), jsonData)) {
                printf("GET %s\n", url);
                printf("HTTP Code %d\n", httpCode);
                printf("JSON %s\n", jsonData.toStyledString().c_str());
                return {jsonData, (int)httpCode};
            }
            else {
                Json::Value val;
                val["status"] = "no connection";
                val["version"] = "failed";
                return {val, -100};
            }
        }

        catch (std::exception* e) {
            Json::Value val;
            val["status"] = "no connection";
            val["version"] = "failed";
            return {val, -100};

        }
    }
}
