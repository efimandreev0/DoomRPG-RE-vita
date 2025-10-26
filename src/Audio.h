#ifndef AUDIO_H__
#define AUDIO_H__

typedef struct FluidSynth_s
{
  fluid_settings_t* settings;
  fluid_synth_t* synth;
} FluidSynth_t;
extern FluidSynth_t* fluidSynth;
typedef struct Audio_s
{
  void* soloud;
  FluidSynth_t fluidSynth;
} Audio_t;

extern Audio_t audio;

void Audio_init(void);
void Audio_close(void);

#endif
