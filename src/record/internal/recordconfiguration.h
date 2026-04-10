/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include "../irecordconfiguration.h"

namespace au::record {
class RecordConfiguration : public IRecordConfiguration
{
public:
    void init();

    muse::draw::Color recordColor() const override;

    bool isMicMeteringOn() const override;
    void setIsMicMeteringOn(bool enable) override;
    muse::async::Notification isMicMeteringOnChanged() const override;

    bool isInputMonitoringOn() const override;
    void setIsInputMonitoringOn(bool enable) override;
    muse::async::Notification isInputMonitoringOnChanged() const override;

    double leadInTimeDuration() const override;
    void setLeadInTimeDuration(double seconds) override;
    muse::async::Notification leadInTimeDurationChanged() const override;

    double crossfadeDuration() const override;
    void setCrossfadeDuration(double milliseconds) override;
    muse::async::Notification crossfadeDurationChanged() const override;

private:
    muse::async::Notification m_isMicMeteringOnChanged;
    muse::async::Notification m_isInputMonitoringOnChanged;
    muse::async::Notification m_leadInTimeDurationChanged;
    muse::async::Notification m_crossfadeDurationChanged;
};
}
