config_setting(
    name = "x86_64_build",
    values = {"define":"plat=laptop"}
)

config_setting(
    name = "arm_build",
    #values = {"cpu":"aarch64"}
    values = {"define":"plat=nano"}
)

cc_library(
    name = "all",
    srcs = select({
        ":x86_64_build" : glob(["local/lib/*.so"]),
        ":arm_build" : glob(["local/lib/libopencv*"]),
    }),
    hdrs = select({
        ":x86_64_build" : glob(["local/include/opencv4/**/*"]),
        ":arm_build" : glob(["local/include/opencv4/**/*"]),
    }),
    includes = select({
        ":x86_64_build" : ["local/include/opencv4"],
        ":arm_build" : ["local/include/opencv4"],
    }),
    visibility = ["//visibility:public"], 
    linkstatic = 1,

)
