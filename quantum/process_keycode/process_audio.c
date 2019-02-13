#include "audio.h"
#include "process_audio.h"

#ifndef VOICE_CHANGE_SONG
    #define VOICE_CHANGE_SONG SONG(VOICE_CHANGE_SOUND)
#endif
float voice_change_song[][2] = VOICE_CHANGE_SONG;

#ifndef PITCH_STANDARD_A
    #define PITCH_STANDARD_A 440.0f
#endif

static float compute_freq_for_midi_note(uint8_t note)
{
    // https://en.wikipedia.org/wiki/MIDI_tuning_standard
    return pow(2.0, (note - 69) / 12.0) * PITCH_STANDARD_A;
}

bool process_audio(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void process_audio_noteon(uint8_t note) {
    play_note(compute_freq_for_midi_note(note), 0xF);
}

void process_audio_noteoff(uint8_t note) {
    stop_note(compute_freq_for_midi_note(note));
}

void process_audio_all_notes_off(void) {
    stop_all_notes();
}

__attribute__ ((weak))
void audio_on_user() {}