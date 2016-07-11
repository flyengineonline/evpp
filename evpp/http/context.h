#pragma once



#include "evpp/inner_pre.h"
#include "evpp/slice.h"

#include <map>

struct evhttp_request;

namespace evpp {
    namespace http {
        class Service;
        struct EVPP_EXPORT Context {
            Context(struct evhttp_request* r);
            ~Context();

            bool Init(Service* hsrv);

            const char* original_uri() const; // Get the original URI with parameters

            void AddResponseHeader(const std::string& key, const std::string& value);

            // ��HTTP�����HEADER�в���ĳ��key��ֵ�����û���ҵ�����һ����ָ�롣
            const char* FindRequestHeader(const char* key);

            std::string uri; // The URI without parameters
            std::string remote_ip; // The client ip. If the HTTP request is forwarded by NGINX we use the 'clientip' parameter in the url.   @see the NGINX conf : proxy_pass       http://127.0.0.1:8080/gasucs/special_kill/?clientip=$remote_addr;
            struct evhttp_request* req;
            Slice body;    //The http body data
        };

        typedef std::shared_ptr<Context> ContextPtr;

        typedef std::function<void(const std::string& response_data)> HTTPSendResponseCallback;

        typedef std::function<
            void(const ContextPtr& ctx,
                 const HTTPSendResponseCallback& respcb)> HTTPRequestCallback;

        typedef std::map<std::string/*The uri*/, HTTPRequestCallback> HTTPRequestCallbackMap;
    }
}