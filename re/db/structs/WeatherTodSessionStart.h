// struct: WeatherTodSessionStart
// subsystem: session
// size: 0x8  L2 decomp:re/decomp/1438b7350.c;xref:0x1438b7d05,0x1438b7e7c (rax*8 indexing by dataset)
// notes: per-dataset time-of-day start entry of WeatherSessionSettings (+0xb28 + d*8, d = 0..7 = P1 P2 P3 Q SS
// R R2 R3). Written by Sess_WeatherComponent_FillSessionSettings 0x140bde510 from the component's time-of-day
// choices (case on comp+0x2c8: 2 = one choice comp+0x2c9 for all, 3 = per session comp+0x2ca+d, factor index
// comp+0x2d2+d); read by Sess_GameWeatherSystem_SetupSession in its per-dataset start-time loop when tod_flag_a
// and tod_flag_b are clear. Raised by engine-re (weather to L2, round 3).
struct WeatherTodSessionStart {
    /* 0x000 */ uint8_t preset;         // L2 decomp:re/decomp/1438b7350.c;decomp:re/decomp/140bde510.c;xref:0x1438b7d05,0x140bde633,0x140bde809 start-time preset 0..7 = byte (choice & 7) of 0x0007060504030201 (choice 0..6 -> 1..7, 7 -> 0, above 7 -> 1); setupSession switches on it over the solar times (gws+0x1e8c..+0x1eac, from Game_TimeOfDay_ComputeSolarAngles): 7 = 0 h, default 12 h
    /* 0x004 */ float factor;           // L1 decomp:re/decomp/1438b7350.c;decomp:re/decomp/140bde510.c;xref:0x1438b7e7c,0x140bde63a,0x140bde82d hub writes 1.0 or 0x14568e894[i] = (float)i for i = comp+0x2d2+d (< 6); setupSession loads it into the start-time loop, its consumer was not traced (stays L1)
};
