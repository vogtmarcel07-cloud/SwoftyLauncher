// struct: WeatherTransition
// subsystem: session
// size: 0x50  L2 decomp:re/decomp/14461d300.c;xref:0x14461f801,0x14461f97b (idx*5 << 4 = idx*0x50)
// One transition record of a WeatherDataset (+0x000 + i*0x50, 37 records = 0xb90 bytes, record i is the
// blend from state i to state i+1). Written by Sess_Tod_StitchWeatherScenario 0x14461d300, cleared by
// Sess_Tod_ResetDatasetStates 0x14461d090; read by the TOD update 0x14461f400 (sub-step search, current
// state name) and by Sess_TimeOfDayOwner_EvalRainIntensity 0x14479ca80 (intensity clamp). Levels: 2 for
// intensity 0, else 3 (<= 0.33), 4 (<= 0.66), 5; level - 2 indexes the level names at 0x145bf6300.
// Raised by engine-re (weather to L2).
struct WeatherTransition {
    /* 0x010 */ char *name;             // L2 decomp:re/decomp/14461d300.c;decomp:re/decomp/14461f400.c;xref:0x14461d6b4,0x14461dd09,0x14461f983 transition name buffer, formatted by 0x1401009f0 from the two level names; the update copies the current one into the TOD debug block; the reset writes *name = 0
    /* 0x038 */ uint32_t from_level;    // L2 decomp:re/decomp/14461d300.c;xref:0x14461dd3d,0x14461e21d,0x14461d0db,0x144618a03,0x14461dcb2 weather type index 0..5 of the source state (V9454): when both states have intensity 0.0 the raw engine types states[i].type / states[i+1].type are stored (0x14461d9d5, stores 0x14461e21d/e225, names 0x145bf6320 clear/lightcloud/overcast/lightrain/heavyrain/stormy/invalid); otherwise the intensity class: 2 when its intensity equals the zero constant, else 3 (<= 0.33), 4 (<= 0.66), 5; the same value picks the from-name for weather_%s-%s (0x145bf4620) from the class names 0x145bf6300 [class-2] = overcast/lightrain/heavyrain/stormy in the formatter call 0x14461dcb2 just before the store. Write-only: no reader exists in the exe as far as searched (update, EvalRainIntensity, stitch; V9392)
    /* 0x03c */ uint32_t to_level;      // L2 decomp:re/decomp/14461d300.c;xref:0x14461dd41,0x14461e225,0x14461dcb2 weather type index 0..5 of the target state (same rule as from_level, V9455 and name table as from_level, the to-name of weather_%s-%s). Write-only: no reader found (V9393)
    /* 0x040 */ float from_intensity;   // L2 decomp:re/decomp/14461d300.c;decomp:re/decomp/14479ca80.c;xref:0x14461dd45,0x14461e229,0x14479cc58 rain intensity of the source state; read by the rain-intensity clamp
    /* 0x044 */ float to_intensity;     // L2 decomp:re/decomp/14461d300.c;decomp:re/decomp/14479ca80.c;xref:0x14461dd4b,0x14461e22f,0x14479cc5d rain intensity of the target state
    /* 0x048 */ uint32_t steps;         // L2 decomp:re/decomp/14461d300.c;decomp:re/decomp/14461f400.c;xref:0x14461d9b6,0x14461d98f,0x14461d9d5,0x14461d9e3,0x14461f809 sub-steps of the blend = |states[i+1].type - states[i].type| (engine weather types, 0..5; 0 for two equal types, then the update skips the sub-step split); the update splits the transition length into this many equal steps and stores the step fraction at TimeOfDaySystem+0xb418
};
