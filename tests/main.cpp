/*
#include "gtest/gtest.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
*/






#include "gtest/gtest.h"


#include <string>
#include <httpmockserver/mock_server.h>
#include <httpmockserver/test_environment.h>


class HTTPMock: public httpmock::MockServer {
public:
    /// Create HTTP server on port 9200
    explicit HTTPMock(int port = 9200): MockServer(port) {}
private:

    /// Handler called by MockServer on HTTP request.
    Response responseHandler(
            const std::string &url,
            const std::string &method,
            const std::string &data,
            const std::vector<UrlArg> &urlArguments,
            const std::vector<Header> &headers)
    {
        if (method == "POST" && matchesPrefix(url, "/example")) {
            // Do something and return response
            return Response(500, "Fake HTTP response");
        }

        if (method == "GET" && matchesPrefix(url, "/bla")) {
            // Do something and return response
            return Response(200, "Fake HTTP response");
        }


        // Return "URI not found" for the undefined methods
        return Response(404, "Not Found");
    }

    /// Return true if \p url starts with \p str.
    bool matchesPrefix(const std::string &url, const std::string &str) const {
        return url.substr(0, str.size()) == str;
    }
};



int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
 //   ::testing::AddGlobalTestEnvironment(new httpmock::TestEnvironment<HTTPMock>());
    return RUN_ALL_TESTS();
}