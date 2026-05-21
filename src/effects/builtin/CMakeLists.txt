#
# Audacity: A Digital Audio Editor
#
declare_module(effects_builtin)

set(MODULE_QRC effects_builtin.qrc)

set(MODULE_QML_IMPORT ${CMAKE_CURRENT_LIST_DIR}/qml)

set(MODULE_SRC
    # public
    ${CMAKE_CURRENT_LIST_DIR}/builtineffectsmodule.cpp
    ${CMAKE_CURRENT_LIST_DIR}/builtineffectsmodule.h
    ${CMAKE_CURRENT_LIST_DIR}/ibuiltineffectsviewregister.h

    # internal
    ${CMAKE_CURRENT_LIST_DIR}/internal/builtineffectsloader.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/builtineffectsmetareader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/internal/builtineffectsmetareader.h
    ${CMAKE_CURRENT_LIST_DIR}/internal/builtineffectsscanner.h

    # view
    ${CMAKE_CURRENT_LIST_DIR}/view/builtineffectinstanceaccess.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/builtineffectinstanceaccess.h
    ${CMAKE_CURRENT_LIST_DIR}/view/builtineffectmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/builtineffectmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/builtineffectviewloader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/builtineffectviewloader.h
    ${CMAKE_CURRENT_LIST_DIR}/view/effectsviewregister.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/effectsviewregister.h

    ${CMAKE_CURRENT_LIST_DIR}/general/generalviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/general/generalviewmodel.h

    # built-in effects
    ${CMAKE_CURRENT_LIST_DIR}/amplify/amplifyeffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/amplify/amplifyeffect.h
    ${CMAKE_CURRENT_LIST_DIR}/amplify/amplifyviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/amplify/amplifyviewmodel.h

    ${CMAKE_CURRENT_LIST_DIR}/loudness/normalizeloudnesseffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/loudness/normalizeloudnesseffect.h
    ${CMAKE_CURRENT_LIST_DIR}/loudness/normalizeloudnessviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/loudness/normalizeloudnessviewmodel.h

    ${CMAKE_CURRENT_LIST_DIR}/clickremoval/clickremovaleffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/clickremoval/clickremovaleffect.h
    ${CMAKE_CURRENT_LIST_DIR}/clickremoval/clickremovalviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/clickremoval/clickremovalviewmodel.h

    ${CMAKE_CURRENT_LIST_DIR}/dynamics/compressor/compressoreffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/compressor/compressoreffect.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/compressor/compressorviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/compressor/compressorviewmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/compressor/compressorsettingmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/compressor/compressorsettingmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/limiter/limiterviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/limiter/limiterviewmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/limiter/limitereffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/limiter/limitereffect.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/limiter/limitersettingmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/limiter/limitersettingmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/dynamicseffectsmacros.h

    ${CMAKE_CURRENT_LIST_DIR}/normalize/normalizeeffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/normalize/normalizeeffect.h
    ${CMAKE_CURRENT_LIST_DIR}/normalize/normalizeviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/normalize/normalizeviewmodel.h

    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/meters/abstractdbmetermodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/meters/abstractdbmetermodel.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/meters/compressiondbmetermodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/meters/compressiondbmetermodel.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/meters/outputdbmetermodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/meters/outputdbmetermodel.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/painters/abstractsequencepainter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/painters/abstractsequencepainter.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/painters/areasequencepainter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/painters/areasequencepainter.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/painters/linesequencepainter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/painters/linesequencepainter.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/abstractdynamicseffectinstancemodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/abstractdynamicseffectinstancemodel.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/dynamicscolors.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/dynamicstimeline.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/dynamicstimeline.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/timelinesourcemodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/timelinesourcemodel.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/stopwatch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/stopwatch.h
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/dynamicsplaystatemodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dynamics/timeline/dynamicsplaystatemodel.h

    ${CMAKE_CURRENT_LIST_DIR}/tonegen/chirpeffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tonegen/chirpeffect.h
    ${CMAKE_CURRENT_LIST_DIR}/tonegen/toneeffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tonegen/toneeffect.h

    ${CMAKE_CURRENT_LIST_DIR}/reverb/reverbeffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/reverb/reverbeffect.h
    ${CMAKE_CURRENT_LIST_DIR}/reverb/reverbviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/reverb/reverbviewmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/tonegen/toneviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tonegen/toneviewmodel.h

    ${CMAKE_CURRENT_LIST_DIR}/dtmfgen/dtmfgenerator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dtmfgen/dtmfgenerator.h
    ${CMAKE_CURRENT_LIST_DIR}/dtmfgen/dtmfviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/dtmfgen/dtmfviewmodel.h

    ${CMAKE_CURRENT_LIST_DIR}/silencegen/silencegenerator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/silencegen/silencegenerator.h
    ${CMAKE_CURRENT_LIST_DIR}/silencegen/silenceviewmodel.h

    ${CMAKE_CURRENT_LIST_DIR}/noisegen/noisegenerator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/noisegen/noisegenerator.h
    ${CMAKE_CURRENT_LIST_DIR}/noisegen/noiseviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/noisegen/noiseviewmodel.h

    ${CMAKE_CURRENT_LIST_DIR}/multibandcompressor/MultibandCompressorEffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/multibandcompressor/multibandcompressorviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/multibandcompressor/multibandcompressorviewmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/multibandcompressor/MultibandCompressorEffect.h

    ${CMAKE_CURRENT_LIST_DIR}/spectralheal/SpectralHealEffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/spectralheal/spectralhealviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/spectralheal/spectralhealviewmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/spectralheal/SpectralHealEffect.h

    ${CMAKE_CURRENT_LIST_DIR}/adaptivenoisereduction/AdaptiveNoiseReductionEffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/adaptivenoisereduction/adaptivenoisereductionviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/adaptivenoisereduction/adaptivenoisereductionviewmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/adaptivenoisereduction/AdaptiveNoiseReductionEffect.h

    ${CMAKE_CURRENT_LIST_DIR}/noisereduction/noisereductioneffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/noisereduction/noisereductioneffect.h
    ${CMAKE_CURRENT_LIST_DIR}/noisereduction/noisereductionviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/noisereduction/noisereductionviewmodel.h

    ${CMAKE_CURRENT_LIST_DIR}/fade/fadeeffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/fade/fadeeffect.h

    ${CMAKE_CURRENT_LIST_DIR}/graphiceq/equalizationbandsliders.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphiceq/equalizationbandsliders.h
    ${CMAKE_CURRENT_LIST_DIR}/graphiceq/graphiceq.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphiceq/graphiceq.h
    ${CMAKE_CURRENT_LIST_DIR}/graphiceq/graphiceqbandsmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphiceq/graphiceqbandsmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/graphiceq/graphiceqviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphiceq/graphiceqviewmodel.h

    ${CMAKE_CURRENT_LIST_DIR}/invert/inverteffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/invert/inverteffect.h

    ${CMAKE_CURRENT_LIST_DIR}/reverse/reverseeffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/reverse/reverseeffect.h

    ${CMAKE_CURRENT_LIST_DIR}/repair/repaireffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/repair/repaireffect.h

    ${CMAKE_CURRENT_LIST_DIR}/truncatesilence/truncatesilenceeffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/truncatesilence/truncatesilenceeffect.h
    ${CMAKE_CURRENT_LIST_DIR}/truncatesilence/truncatesilenceviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/truncatesilence/truncatesilenceviewmodel.h

    ${CMAKE_CURRENT_LIST_DIR}/changepitch/changepitcheffect.cpp
    ${CMAKE_CURRENT_LIST_DIR}/changepitch/changepitcheffect.h
    ${CMAKE_CURRENT_LIST_DIR}/changepitch/changepitchviewmodel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/changepitch/changepitchviewmodel.h
    ${CMAKE_CURRENT_LIST_DIR}/view/builtineffectsviewregister.cpp
    ${CMAKE_CURRENT_LIST_DIR}/view/builtineffectsviewregister.h
    )

# AU3
include(${CMAKE_CURRENT_LIST_DIR}/../../au3wrap/au3wrapDefs.cmake)

set(MODULE_INCLUDE ${AU3_INCLUDE})
set(MODULE_DEF ${AU3_DEF})

set(MODULE_LINK au3wrap)

set(MODULE_USE_UNITY OFF)

setup_module()
