# Mixer UI Implementation Plan
The modern 'Mixer Board UI' does not exist in the current project structure, only legacy wxWidgets code in 'au3/src/MixerBoard.cpp'. The memory referring to 'MixerBoardModel' and 'MixerChannelStrip' indicates an intent to implement a new QML-based mixer using BobUI.
I need to scaffold out the QML frontend and C++ backend for this.
