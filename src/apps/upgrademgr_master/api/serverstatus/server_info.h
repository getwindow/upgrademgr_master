#ifndef UPGRADEMGR_MASTER_API_SERVER_STATUS_INFO_H
#define UPGRADEMGR_MASTER_API_SERVER_STATUS_INFO_H

#include "api/macros.h"
#include "corelib/network/rpc/abstract_api.h"
#include "corelib/network/rpc/invoke_meta.h"
#include "corelib/network/rpc/api_provider.h"

namespace upgrademgr{
namespace master{
namespace api{
namespace serverstatus{

UMM_USING_API_NAMESPACES

class Info : public AbstractApi
{
   Q_OBJECT
public:
   Info(ApiProvider& provider);
   Q_INVOKABLE ApiInvokeResponse getVersionInfo(const ApiInvokeRequest &request);
};

}//serverstatus
}//api
}//master
}//upgrademgr

#endif // UPGRADEMGR_MASTER_API_SERVER_STATUS_INFO_H
