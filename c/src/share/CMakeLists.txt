# 将.目录所有源文件名保存至变量
aux_source_directory(. SHARE_FILES)

# STATIC, SHARED, or MODULE may be given to specify the type of library to be created.
# STATIC libraries are archives of object files for use when linking other targets.
# SHARED libraries are linked dynamically and loaded at runtime.
# MODULE libraries are plugins that are not linked into other targets but may be loaded dynamically at runtime using dlopen-like functionality.
add_library(share STATIC ${SHARE_FILES})
