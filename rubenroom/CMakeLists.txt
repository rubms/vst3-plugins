
set(plug_sources
    include/plugcontroller.h
    include/plugids.h
    include/plugprocessor.h
    include/version.h
	../common/include/circularaudiobuffer.h
	../common/include/bypasser.h
	../common/include/room.h
	../common/include/damper.h
	../common/include/diffuser.h
	../common/include/delay.h
	../common/include/dampeddelay.h
    source/plugfactory.cpp
    source/plugcontroller.cpp
    source/plugprocessor.cpp
	../common/source/circularaudiobuffer.cpp
	../common/source/bypasser.cpp
	../common/source/room.cpp
	../common/source/damper.cpp
	../common/source/diffuser.cpp
	../common/source/delay.cpp
	../common/source/dampeddelay.cpp
)

#--- HERE change the target Name for your plug-in (for ex. set(target myDelay))-------
set(target rubenroom)

smtg_add_vst3plugin(${target} ${plug_sources})
set_target_properties(${target} PROPERTIES ${SDK_IDE_MYPLUGINS_FOLDER})
target_link_libraries(${target} PRIVATE base sdk)

if(MAC)
    smtg_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS)
elseif(WIN)
    target_sources(${target} PRIVATE resource/plug.rc)
endif()
