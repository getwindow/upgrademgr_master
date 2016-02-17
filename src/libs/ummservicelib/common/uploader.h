#ifndef UMM_SERVICE_COMMON_UPLOADER_H
#define UMM_SERVICE_COMMON_UPLOADER_H

#include <QMap>
#include <QString>
#include <QFile>

#include "ummservicelib/global_defs.h"
#include "corelib/network/rpc/abstract_service.h"
#include "corelib/network/rpc/invoke_meta.h"
#include "corelib/network/rpc/service_provider.h"

namespace ummservice{
namespace common{

using sn::corelib::network::ServiceInvokeRequest;
using sn::corelib::network::ServiceInvokeResponse;

UMM_USING_SERVICE_NAMESPACES

class UMM_SERVICE_EXPORT Uploader : public AbstractService
{
   Q_OBJECT
   const static int UPLOAD_STEP_PREPARE = 0;
   const static int UPLOAD_STEP_START = 1;
   const static int UPLOAD_STEP_PROCESS = 2;
   const static int UPLOAD_STEP_NOTIFY_UPLOAD_COMPLETE = 3;
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
      int chunkSize = 2048;
      int currentCycle = 0;
   };
public:
   Uploader(ServiceProvider& provider);
   virtual ~Uploader();
   Q_INVOKABLE ServiceInvokeResponse init(const ServiceInvokeRequest &request);
   Q_INVOKABLE ServiceInvokeResponse receiveData(const ServiceInvokeRequest &request);
   Q_INVOKABLE ServiceInvokeResponse notifyUploadComplete(const ServiceInvokeRequest &request);
protected:
   UploadContext& getContextByRequest(const ServiceInvokeRequest &request);
   Uploader& removeContextByRequestSocketId(int sid);
protected:
   QMap<int, UploadContext> m_context;
   quint64 m_total = 0;
};

}//common
}//ummservice

#endif // UMM_SERVICE_COMMON_UPLOADER_H