#include "initializers/initializer_cleanup_funcs.h"
#include "api/api_repo.h"

#include "corelib/network/rpc/api_provider.h"
#include "corelib/network/rpc/abstract_api.h"

namespace upgrademgr{
namespace master{

using sn::corelib::network::ApiProvider;
using sn::corelib::network::AbstractApi;

void init_api_provider()
{
   ApiProvider& provider = ApiProvider::instance();
   provider.addApiToPool("Repo/Info", [](ApiProvider& provider)-> AbstractApi*{
                            return new upgrademgr::master::api::repo::Info(provider);
                         });
}

}//master
}//upgrademgr