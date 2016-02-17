import qbs 1.0
Product
{
   type: "dynamiclibrary"
   name : "ummservicelib"
   targetName : "ummservice"
   Depends { 
      name: "Qt"; 
      submodules: ["core", "network","websockets"]
   }
   Depends { name:"corelib"}
   Depends { name:"ummlib"}
   Depends { name:"cpp"}
   destinationDirectory: "lib"
   cpp.defines: {
      var defines = [];
      if(product.type == "staticlibrary"){
         defines.push("UMM_SERVICE_STATIC_LIB");
      }else{
         defines.push("UMM_SERVICE_LIBRARY");
      }
      defines = defines.concat([
                                  'UMM_SERVICE_LIB_VERSION="'+ version+'"',
                                  'UMM_MASTER_VERSION="' + project.upgrademgrMasterversion+'"'
                               ]);
      return defines;
   }
   cpp.visibility: "minimal"
   cpp.cxxLanguageVersion: "c++14"
   cpp.includePaths:[".","../ummlib/", "../ummservicelib/", "../"]
   Export {
      Depends { name: "cpp" }
      Depends { name: "Qt"; submodules: ["core"] }
      cpp.rpaths: ["$ORIGIN/../lib"]
      cpp.includePaths: [product.sourceDirectory+"../"]
   }
   Group {
      fileTagsFilter: product.type.concat("dynamiclibrary_symlink")
      qbs.install: true
      qbs.installDir: "lib"
   }
   files:[
        "global_defs.h",
        "service_error_code.h",
        "service_repo.h",
        "common/uploader.cpp",
        "common/uploader.h",
        "macros.h",
        "repo/repo_info.cpp",
        "repo/repo_info.h",
        "serverstatus/server_info.cpp",
        "serverstatus/server_info.h",
        "upgrader/upgrade_upgrademgr_master.cpp",
        "upgrader/upgrade_upgrademgr_master.h",
    ]
}