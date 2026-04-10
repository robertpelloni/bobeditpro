/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

#include "itrackspectrogramconfiguration.h"

#include "framework/global/modularity/imoduleinterface.h"
#include "framework/global/async/channel.h"

namespace au::spectrogram {
class ITrackSpectrogramConfigurationProvider : MODULE_EXPORT_INTERFACE
{
    INTERFACE_ID(ITrackSpectrogramConfigurationProvider)

public:
    virtual ~ITrackSpectrogramConfigurationProvider() = default;

    virtual ITrackSpectrogramConfigurationPtr trackSpectrogramConfiguration(int trackId) const = 0;
<<<<<<< HEAD:src/spectrogram/itrackspectrogramconfigurationprovider.h
    virtual void copyConfiguration(const ISpectrogramConfiguration& source, ISpectrogramConfiguration& destination) const = 0;
=======
    virtual muse::async::Channel<int /*track id*/> trackSpectrogramConfigurationChanged() const = 0;
    virtual void notifyAboutTrackSpectrogramConfigurationChanged(int trackId) = 0;

    virtual void copyConfiguration(ISpectrogramConfiguration& source, ISpectrogramConfiguration& destination) const = 0;
    virtual double frequencyHardMaximum(int trackId) const = 0;
    virtual double yToFrequency(int trackId, double spectrogramY, double spectrogramHeight) const = 0;
    virtual double frequencyToY(int trackId, double frequency, double spectrogramHeight) const = 0;
>>>>>>> upstream/master:src/spectrogram/ispectrogramservice.h
};
}
