# Psy-Cross (Psy-X)
![](https://i.ibb.co/PFNnw4G/PsyCross.jpg)

Framework aiming to build and run originally targeted **Playstation** applications on other platforms based on Psy-Q SDK.

### Implementation details
- high-level *Playstation API* reimplementation which translates it's calls into modern/compatible APIs
- Psy-Q compatible headers
- Implements Geometry Transformation Engine (GTE) in software and adapts it's macros and calls
- **PGXP-Z** - PGXP support with optimized vertex cache lookup and extended with *modern 3D hardware perspective transform* and *Z-buffer* support **PGXP-Z**
- *LibSPU* with ADPCM decoding on OpenAL (SPU-AL)
- *LibGPU* with Playstation-style polygon and image handling
- Already proven to be *95% compatible* with the Psy-Q Playstation SDK - Psy-X game look identical to the Playstation game

## TODO
- Add some missing LibGTE functions
- Add support for MDEC, CDXA decoding and playback
- Extend BIN/CUE image support
- SPU ADSR

### Credits
- SoapyMan - more GTE functions, SPU-AL, PGXP-Z
- Gh0stBlade - original source/base [(link)](https://github.com/TOMB5/TOMB5/tree/master/EMULATOR)