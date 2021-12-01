#pragma once

struct VisualizerState {
    bool inSignal = true;
    bool outSignal = true;
    bool threshold, avgLevel, compression;
    float windowSeconds = 0.05f;
};
