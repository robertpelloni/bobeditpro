# Spectral Selection Guide

## Introduction
The Spectral Selection tool allows you to isolate and select specific time-frequency ranges of audio inside the Spectrogram view. This is a foundational step in advanced audio restoration and editing workflows, such as removing isolated noises or applying frequency-specific effects.

## Accessing the Spectrogram View
To see the spectrogram for a track, right-click the track's vertical control panel and change its view mode from **Waveform** to **Spectrogram**.

## Making a Spectral Selection
Once in the Spectrogram view:
1. Ensure the **Spectral Selection Tool** is active.
2. Click and drag within the Spectrogram of the audio clip to form a rectangular selection.
3. The horizontal axis represents Time, and the vertical axis represents Frequency (measured in Hertz or Mel/Bark scales depending on your Spectrogram Preferences).
4. The boundaries of the selected frequencies will be marked by horizontal guidelines that you can further click and drag to refine the selection's top and bottom frequency limits.

## How It Works
The exact selected start and end frequencies are maintained by the `ProjectSelectionManager` and provided to the `Au3SelectionController`. These values are used whenever you run a "Spectral" effect (such as Spot Healing or Adaptive Noise Reduction), guaranteeing that the effect only processes the specific frequency range you highlighted.
