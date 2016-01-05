#ifndef UPGRADEMGR_MASTER_API_COMMON_UPLOADER_H
#define UPGRADEMGR_MASTER_API_COMMON_UPLOADER_H

#include <QMap>
#include <QString>
#include <QFile>

#include "api/macros.h"
#include "corelib/network/rpc/abstract_api.h"
#include "corelib/network/rpc/invoke_meta.h"
#include "corelib/network/rpc/api_provider.h"

namespace upgrademgr{
namespace master{
namespace api{
namespace common{

using sn::corelib::network::ApiInvokeRequest;
using sn::corelib::network::ApiInvokeResponse;

UMM_USING_API_NAMESPACES

class Uploader : public AbstractApi
{
   Q_OBJECT
   const static int UPLOAD_STEP_PREPARE = 0;
   const static int UPLOAD_STEP_START = 1;
   const static int UPLOAD_STEP_PROCESS = 2;
   const static int UPLOAD_STEP_CHECKSUM = 3;
   const static int UPLOAD_STEP_FINISH = 4;
   
   struct UploadContext
   {
      QString baseDir;
      QString filename;
      QString md5;
      quint64 total = 0;
      quint64 uploaded = 0;
      int step = UPLOAD_STEP_PREPARE;
      QFile *targetFile = nullptr;
      int cycleSize = 20;
      int currentCycle = 0;
   };
public:
   Uploader(ApiProvider& provider);
   virtual ~Uploader();
   Q_INVOKABLE ApiInvokeResponse init(const ApiInvokeRequest &request);
   Q_INVOKABLE ApiInvokeResponse receiveData(const ApiInvokeRequest &request);
   Q_INVOKABLE ApiInvokeResponse checkUploadResult(const ApiInvokeRequest &request);
protected:
   UploadContext& getContextByRequest(const ApiInvokeRequest &request);
   Uploader& removeContextByRequestSocketId(int sid);
protected:
   QMap<int, UploadContext> m_context;
   quint64 m_total = 0;
};

}//common
}//api
}//master
}//upgrademgr

#endif // UPGRADEMGR_MASTER_API_COMMON_UPLOADER_H
