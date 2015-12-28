import qbs 1.0
Product
{
   type: "dynamiclibrary"
   name : "ummlib"
   targetName : "umm"
   Depends { 
      name: "Qt"; 
      submodules: ["core", "network"]
   }
   Depends { name:"corelib"}
   Depends { name:"cpp"}
   destinationDirectory: "lib"
   cpp.defines: {
      var defines = [];
      if(product.type == "staticlibrary"){
         defines.push("UM_MASTER_STATIC_LIB");
      }else{
         defines.push("UM_MASTER_LIBRARY");
      }
      defines = defines.concat([
                                  'UMM_LIB_VERSION="'+ version+'"'
                               ]);
      return defines;
   }
   cpp.visibility: "minimal"
   cpp.cxxLanguageVersion: "c++14"
   cpp.includePaths:[".","../"]
   version : "0.1.1"
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
   
   Group {
      name: "global"
      prefix: name+"/"
      files: [
           "global.h",
       ]
   }
   
   Group {
      name:"network"
      prefix: name+"/"
      files:[
           "multi_thread_server.cpp",
           "multi_thread_server.h",
       ]
   }
   
}