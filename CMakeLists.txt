cmake_minimum_required(VERSION 3.5)

project(ClassicCryptography VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS view/)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools Sql REQUIRED)

set(TS_FILES ClassicCryptography_id_ID.ts)

set(PROJECT_SOURCES
        include/mainwindow.h
        include/vigenerestandardwidget.h
        include/vigenererunningkeywidget.h
        include/vigenereautokeywidget.h
        include/vigenerefullwidget.h
        include/vigenerefulltabledialog.h
        include/vigenere256asciiwidget.h
        src/main.cpp
        src/mainwindow.cpp
        src/vigenerestandardwidget.cpp
        src/vigenererunningkeywidget.cpp
        src/vigenereautokeywidget.cpp
        src/vigenerefullwidget.cpp
        src/vigenerefulltabledialog.cpp
        src/vigenere256asciiwidget.cpp
        view/mainwindow.ui
        view/vigenerestandardwidget.ui
        view/vigenererunningkeywidget.ui
        view/vigenereautokeywidget.ui
        view/vigenerefullwidget.ui
        view/vigenerefulltabledialog.ui
        view/vigenere256asciiwidget.ui
        include/cipher/vigenere/Vigenere.h
        include/cipher/vigenere/VigenereStandard.h
        include/cipher/vigenere/VigenereRunningKey.h
        include/cipher/vigenere/VigenereAutoKey.h
        include/cipher/vigenere/VigenereFull.h
        include/cipher/vigenere/Vigenere256ASCII.h
        include/cipher/util.h
        src/cipher/vigenere/VigenereStandard.cpp
        src/cipher/vigenere/Vigenere.cpp
        src/cipher/vigenere/VigenereRunningKey.cpp
        src/cipher/vigenere/VigenereAutoKey.cpp
        src/cipher/vigenere/VigenereFull.cpp
        src/cipher/vigenere/Vigenere256ASCII.cpp
        src/cipher/util.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ClassicCryptography
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ClassicCryptography APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(ClassicCryptography SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ClassicCryptography
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(ClassicCryptography PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(ClassicCryptography PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ClassicCryptography)
endif()
