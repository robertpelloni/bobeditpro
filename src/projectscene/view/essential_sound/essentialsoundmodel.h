#pragma once

#include <QObject>

namespace au::projectscene {
/**
 * @brief The EssentialSoundModel class
 * Provides macro controls (Clarity, Loudness, Reverb Reduction) for the UI.
 * In a fully wired environment, these properties would broadcast to underlying DSP
 * models (like MultibandCompressor, EQ, and DeReverb).
 */
class EssentialSoundModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString audioType READ audioType WRITE setAudioType NOTIFY audioTypeChanged)
    Q_PROPERTY(double clarity READ clarity WRITE setClarity NOTIFY clarityChanged)
    Q_PROPERTY(double dynamics READ dynamics WRITE setDynamics NOTIFY dynamicsChanged)
    Q_PROPERTY(double reverbReduction READ reverbReduction WRITE setReverbReduction NOTIFY reverbReductionChanged)
    Q_PROPERTY(bool isAutoMatched READ isAutoMatched WRITE setIsAutoMatched NOTIFY isAutoMatchedChanged)

public:
    explicit EssentialSoundModel(QObject* parent = nullptr);

    QString audioType() const;
    void setAudioType(const QString& type);

    double clarity() const;
    void setClarity(double value);

    double dynamics() const;
    void setDynamics(double value);

    double reverbReduction() const;
    void setReverbReduction(double value);

    bool isAutoMatched() const;
    void setIsAutoMatched(bool value);

    Q_INVOKABLE void autoMatchLoudness();

signals:
    void audioTypeChanged();
    void clarityChanged();
    void dynamicsChanged();
    void reverbReductionChanged();
    void isAutoMatchedChanged();

private:
    QString m_audioType{ "None" }; // "Dialogue", "Music", "SFX", "Ambience"
    double m_clarity{ 0.0 };
    double m_dynamics{ 0.0 };
    double m_reverbReduction{ 0.0 };
    bool m_isAutoMatched{ false };
};
} // namespace au::projectscene
