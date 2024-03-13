QT += quick quickcontrols2

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    MalamuteCore/Casing.h \
    MalamuteCore/CasingBackend.h \
    MalamuteCore/CasingState.h \
    MalamuteCore/Commands/AddCasingCommand.h \
    MalamuteCore/Commands/AddDefaultDisplayCommand.h \
    MalamuteCore/Commands/AddDefaultSourceCommand.h \
    MalamuteCore/Commands/AddSelectionCommand.h \
    MalamuteCore/Commands/AddWireCommand.h \
    MalamuteCore/Commands/ChangeParamsCommand.h \
    MalamuteCore/Commands/DeleteCasingCommand.h \
    MalamuteCore/Commands/DeleteSelectionCommand.h \
    MalamuteCore/Commands/DeleteWireCommand.h \
    MalamuteCore/Commands/MinimizeCasingCommand.h \
    MalamuteCore/Commands/MoveSelectionCommand.h \
    MalamuteCore/Commands/ResizeCasingCommand.h \
    MalamuteCore/Commands/ShiftWireCommand.h \
    MalamuteCore/Commands/UndoCommand.h \
    MalamuteCore/Commands/UndoStack.h \
    MalamuteCore/Corkboard.h \
    MalamuteCore/CorkboardBackend.h \
    MalamuteCore/CorkboardHandler.h \
    MalamuteCore/InheritedClasses/DataType.h \
    MalamuteCore/InheritedClasses/DataTypeAttributes.h \
    MalamuteCore/InheritedClasses/Idea.h \
    MalamuteCore/InheritedClasses/IdeaAttributes.h \
    MalamuteCore/InheritedClasses/Magic.h \
    MalamuteCore/InheritedClasses/MalamutePlugin.h \
    MalamuteCore/Plug.h \
    MalamuteCore/QMLRegisterHelper.h \
    MalamuteCore/Registries/DataTypeRegistry.h \
    MalamuteCore/Registries/IdeaRegistry.h \
    MalamuteCore/Styling/CasingStyle.h \
    MalamuteCore/Styling/CorkboardStyle.h \
    MalamuteCore/Styling/GearStyle.h \
    MalamuteCore/Styling/LabelStyle.h \
    MalamuteCore/Styling/WireStyle.h \
    MalamuteCore/SurfaceAndStyleSetup.h \
    MalamuteCore/Wire.h \
    MalamuteCore/WireBackend.h \
    MalamuteCore/WireCasingInteraction.h \
    MalamuteCore/WireState.h \
    Plugin/BlackBoxHundred.h \
    Plugin/CoinArrayDataType.h \
    Plugin/CoinArrayModel.h \
    Plugin/CoinFlipperIdea.h \
    Plugin/DecompressionAlgorithm.h \
    Plugin/HalfSuccessFive.h \
    Plugin/HalfSuccessHundred.h \
    Plugin/IntermediateWayIdea.h \
    Plugin/MostEfficient1to100.h \
    Plugin/MostEfficient1to3.h \
    Plugin/MostEfficient1to5.h \
    Plugin/Plugin.h \
    Plugin/RedunantRemoval.h \
    Plugin/RedunantRemovalFive.h \
    Plugin/RejectionSampling.h \
    Plugin/RejectionSamplingFive.h \
    Plugin/RejectionSamplingHundred.h \
    Plugin/SlickWayIdea.h \
    Plugin/TakeAllot1to3.h \
    Plugin/TakeTwo.h \
    Plugin/TakeTwoInefficient.h \
    Plugin/TileArrayDataType.h \
    Plugin/TileArrayModel.h \
    Plugin/TileFloorIdea.h

SOURCES += \
    MalamuteCore/Casing.cpp \
    MalamuteCore/CasingBackend.cpp \
    MalamuteCore/CasingState.cpp \
    MalamuteCore/Commands/AddCasingCommand.cpp \
    MalamuteCore/Commands/AddDefaultDisplayCommand.cpp \
    MalamuteCore/Commands/AddDefaultSourceCommand.cpp \
    MalamuteCore/Commands/AddSelectionCommand.cpp \
    MalamuteCore/Commands/AddWireCommand.cpp \
    MalamuteCore/Commands/ChangeParamsCommand.cpp \
    MalamuteCore/Commands/DeleteCasingCommand.cpp \
    MalamuteCore/Commands/DeleteSelectionCommand.cpp \
    MalamuteCore/Commands/DeleteWireCommand.cpp \
    MalamuteCore/Commands/MinimizeCasingCommand.cpp \
    MalamuteCore/Commands/MoveSelectionCommand.cpp \
    MalamuteCore/Commands/ResizeCasingCommand.cpp \
    MalamuteCore/Commands/ShiftWireCommand.cpp \
    MalamuteCore/Commands/UndoStack.cpp \
    MalamuteCore/Corkboard.cpp \
    MalamuteCore/CorkboardBackend.cpp \
    MalamuteCore/CorkboardHandler.cpp \
    MalamuteCore/InheritedClasses/DataType.cpp \
    MalamuteCore/InheritedClasses/DataTypeAttributes.cpp \
    MalamuteCore/InheritedClasses/Idea.cpp \
    MalamuteCore/InheritedClasses/IdeaAttributes.cpp \
    MalamuteCore/Registries/DataTypeRegistry.cpp \
    MalamuteCore/Registries/IdeaRegistry.cpp \
    MalamuteCore/Styling/CasingStyle.cpp \
    MalamuteCore/Styling/CorkboardStyle.cpp \
    MalamuteCore/Styling/GearStyle.cpp \
    MalamuteCore/Styling/LabelStyle.cpp \
    MalamuteCore/Styling/WireStyle.cpp \
    MalamuteCore/Wire.cpp \
    MalamuteCore/WireBackend.cpp \
    MalamuteCore/WireCasingInteraction.cpp \
    MalamuteCore/WireState.cpp \
    MalamuteCore/main.cpp \
    Plugin/BlackBoxHundred.cpp \
    Plugin/CoinArrayDataType.cpp \
    Plugin/CoinArrayModel.cpp \
    Plugin/CoinFlipperIdea.cpp \
    Plugin/DecompressionAlgorithm.cpp \
    Plugin/HalfSuccessFive.cpp \
    Plugin/HalfSuccessHundred.cpp \
    Plugin/IntermediateWayIdea.cpp \
    Plugin/MostEfficient1to100.cpp \
    Plugin/MostEfficient1to3.cpp \
    Plugin/MostEfficient1to5.cpp \
    Plugin/Plugin.cpp \
    Plugin/RedunantRemoval.cpp \
    Plugin/RedunantRemovalFive.cpp \
    Plugin/RejectionSampling.cpp \
    Plugin/RejectionSamplingFive.cpp \
    Plugin/RejectionSamplingHundred.cpp \
    Plugin/SlickWayIdea.cpp \
    Plugin/TakeAllot1to3.cpp \
    Plugin/TakeTwo.cpp \
    Plugin/TakeTwoInefficient.cpp \
    Plugin/TileArrayDataType.cpp \
    Plugin/TileArrayModel.cpp \
    Plugin/TileFloorIdea.cpp

RESOURCES += \
    MalamuteCore/MalamuteCoreResources.qrc \
    Plugin/PluginResources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

QMAKE_LFLAGS_RELEASE += -s TOTAL_MEMORY=33554432

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
