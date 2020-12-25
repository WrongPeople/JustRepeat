#include "JustRepeat.h"

AudioEffect *createEffectInstance(audioMasterCallback audioMaster) {
    return new JustRepeat(audioMaster);
}

