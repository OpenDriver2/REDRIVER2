project "jpeg"
    kind "StaticLib"
    language "C"
    targetdir "lib/%{cfg.buildcfg}"
	
	location(JPEG_DIR)

    files { 
		JPEG_DIR.."/jaricom.c",
		JPEG_DIR.."/jcapimin.c",
		JPEG_DIR.."/jcapistd.c",
		JPEG_DIR.."/jcarith.c",
		JPEG_DIR.."/jccoefct.c",
		JPEG_DIR.."/jccolor.c",
		JPEG_DIR.."/jcdctmgr.c",
		JPEG_DIR.."/jchuff.c",
		JPEG_DIR.."/jcinit.c",
		JPEG_DIR.."/jcmainct.c",
		JPEG_DIR.."/jcmarker.c",
		JPEG_DIR.."/jcmaster.c",
		JPEG_DIR.."/jcomapi.c",
		JPEG_DIR.."/jcparam.c",
		JPEG_DIR.."/jcprepct.c",
		JPEG_DIR.."/jcsample.c",
		JPEG_DIR.."/jctrans.c",
		JPEG_DIR.."/jdapimin.c",
		JPEG_DIR.."/jdapistd.c",
		JPEG_DIR.."/jdarith.c",
		JPEG_DIR.."/jdatadst.c",
		JPEG_DIR.."/jdatasrc.c",
		JPEG_DIR.."/jdcoefct.c",
		JPEG_DIR.."/jdcolor.c",
		JPEG_DIR.."/jddctmgr.c",
		JPEG_DIR.."/jdhuff.c",
		JPEG_DIR.."/jdinput.c",
		JPEG_DIR.."/jdmainct.c",
		JPEG_DIR.."/jdmarker.c",
		JPEG_DIR.."/jdmaster.c",
		JPEG_DIR.."/jdmerge.c",
		JPEG_DIR.."/jdpostct.c",
		JPEG_DIR.."/jdsample.c",
		JPEG_DIR.."/jdtrans.c",
		JPEG_DIR.."/jerror.c",
		JPEG_DIR.."/jfdctflt.c",
		JPEG_DIR.."/jfdctfst.c",
		JPEG_DIR.."/jfdctint.c",
		JPEG_DIR.."/jidctflt.c",
		JPEG_DIR.."/jidctfst.c",
		JPEG_DIR.."/jidctint.c",
		JPEG_DIR.."/jmemmgr.c",
		JPEG_DIR.."/jmemnobs.c",
		JPEG_DIR.."/jquant1.c",
		JPEG_DIR.."/jquant2.c",
		JPEG_DIR.."/jutils.c"
    }

    filter "configurations:Release"
        optimize "Full"
