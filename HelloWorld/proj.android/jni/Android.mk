LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/TitleScene.cpp \
		   ../../Classes/VisibleRect.cpp\
		   ../../Classes/Score.cpp \
		   ../../Classes/Props.cpp \
		   ../../Classes/CheckerPiece.cpp \
		   ../../Classes/CheckerPreview.cpp \
		   ../../Classes/Energy.cpp \
		   ../../Classes/GameLayer.cpp \
		   ../../Classes/GameScene.cpp \
		   ../../Classes/Jackpot.cpp \
		   ../../Classes/MenuLayers.cpp \
		   ../../Classes/PropLayer.cpp \
		   ../../Classes/CheckerBoard.cpp \
		   ../../Classes/GameSettingData.cpp		   
		   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
