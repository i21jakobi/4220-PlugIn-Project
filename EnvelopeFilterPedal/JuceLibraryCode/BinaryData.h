/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   pedalBody_0001_png;
    const int            pedalBody_0001_pngSize = 2705063;

    extern const char*   filterselector_sprite_png;
    const int            filterselector_sprite_pngSize = 57240;

    extern const char*   bypass_sprite_png;
    const int            bypass_sprite_pngSize = 38440;

    extern const char*   maxfreq_sprite_png;
    const int            maxfreq_sprite_pngSize = 4253174;

    extern const char*   minfreq_sprite_png;
    const int            minfreq_sprite_pngSize = 4288062;

    extern const char*   resonance_sprite_png;
    const int            resonance_sprite_pngSize = 4143523;

    extern const char*   sensitivity_sprite_png;
    const int            sensitivity_sprite_pngSize = 4646991;

    extern const char*   sweepDirection_sprite_png;
    const int            sweepDirection_sprite_pngSize = 38756;

    extern const char*   bypass_switch_0001_png;
    const int            bypass_switch_0001_pngSize = 19625;

    extern const char*   bypass_switch_0002_png;
    const int            bypass_switch_0002_pngSize = 19693;

    extern const char*   filterType_0001_png;
    const int            filterType_0001_pngSize = 19754;

    extern const char*   filterType_0002_png;
    const int            filterType_0002_pngSize = 19635;

    extern const char*   filterType_0003_png;
    const int            filterType_0003_pngSize = 19640;

    extern const char*   sweepDirection_0001_png;
    const int            sweepDirection_0001_pngSize = 19794;

    extern const char*   sweepDirection_0002_png;
    const int            sweepDirection_0002_pngSize = 19848;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 15;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
