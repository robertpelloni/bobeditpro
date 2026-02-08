# Audacity 4 Vision

## Ultimate Goal: Adobe Audition (Cool Edit Pro) Feature Parity

The goal of Audacity 4 is to evolve the world's most popular open-source audio editor into a professional-grade Digital Audio Workstation (DAW) that rivals industry standards like Adobe Audition, while maintaining its accessibility and open-source nature.

## Key Pillars

### 1. Professional Mixing & Routing (The "Mixer" Project)
*   **Bus Tracks:** Group tracks for sub-mixing and shared processing.
*   **Aux Sends/Returns:** Flexible signal routing for parallel processing (reverb, delay).
*   **Master Fader:** Dedicated master bus with post-fader effects.
*   **Real-time Effects Rack:** Non-destructive VST3/AU/LV2 plugin support on clips, tracks, and master.

### 2. Spectral Editing & Restoration
*   **Spectral View:** High-resolution frequency analysis and editing.
*   **Spot Healing Brush:** Intelligent removal of clicks and pops in frequency domain.
*   **Noise Reduction:** Adaptive background noise removal.

### 3. Non-Destructive Workflow
*   **Clip-Based Editing:** Trimming, fading, and moving clips without altering source files.
*   **Automation:** Real-time recording and editing of volume, pan, and effect parameters.

### 4. Modern UI/UX (Muse Framework)
*   **Themable Interface:** Dark/Light modes and custom themes.
*   **Docking System:** Flexible panel layout (Spectral, Mixer, Multitrack views).
*   **High-DPI Support:** Crisp rendering on 4K/Retina displays.

## Architectural Shift
*   **au3 Libraries:** Modular, testable C++ core libraries (`au3-mixer`, `au3-track`, `au3-effects`).
*   **Muse Framework:** QML-based UI layer separating presentation from logic.
*   **Scripting:** Python/Nyquist integration for automation and batch processing.
