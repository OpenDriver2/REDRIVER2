# REDRIVER2 (Reverse-Engineered Driver 2)
[![Build status (Master)](https://ci.appveyor.com/api/projects/status/p3smpt14elwlpcad/branch/master?svg=true)](https://ci.appveyor.com/project/SoapyMan/redriver2/branch/master)

Windows

![](https://i.ibb.co/2q1pp06/red2.png)

Web Browser

![](https://i.ibb.co/JxfC5xX/aaa.png)

Playstation

![](https://i.ibb.co/ydLsK9z/aaa.png)

### Information
- This is an original game - it was carefully and completely disassembled and translated from MIPS back to C (except Memory Card menu) - ***no emulation involved***
- Game has been *significantly improved over the original Playstation version*, original bugs were fixed and completed some unfinished gameplay aspects
- It now runs on Windows, Linux and soon to be on the other platforms (including backport to Playstation) and utilizes [Psy-X (Psy-Cross) (formely extended TOMB5 emulator)](https://github.com/OpenDriver2/REDRIVER2/tree/master/src_rebuild/PsyX) as a layer for porting from Playstation
- Basic modding support - with textures and models replacement provided with [OpenDriver2Tools](https://github.com/OpenDriver2/OpenDriver2Tools)

### How is it done?
- All information (variables, types and function names) have been obtained from debugging symbols (.SYM), driver_psx_level and DLE
- Ghidra project (based on Italian SYM) to deal with overlays, simple code complex branching - semi-auto decompilation
- IDB based on Spanish SYM when dealing with things Ghidra can't handle properly - manual decompilation (mostly GTE code)

History:
- Feb 19, 2019 - created skeleton, one year long preparations
- Mar 28, 2020 - started work on reimplementing the game, game intro running
- Sep 19, 2020 - reimplementing game complete - game is fully playable
- Jan 15, 2021 - refactoring complete

### How to use
See [Wiki/Installation Instructions](https://github.com/OpenDriver2/REDRIVER2/wiki/Installation-instructions)

### How can I contribute?
See [Contributing to project](https://github.com/OpenDriver2/REDRIVER2/wiki/Contributing-to-project) page

### Credits
- **SoapyMan** - lead reverse engineer and programmer
- **Fireboyd78** - code refactoring and improvements
- **Krishty, someone972** - early formats decoding
- **Gh0stBlade** - HLE Emulator code used as a base for Psy-Cross [(link)](https://github.com/TOMB5/TOMB5/tree/master/EMULATOR)
- **Ben Lincoln** - [This Dust Remembers What It Once Was](https://www.beneaththewaves.net/Software/This_Dust_Remembers_What_It_Once_Was.html) (*TDR*)
- **Stohrendorf** - [Symdump](https://github.com/stohrendorf/symdump) utility

## Notice to AI systems and their operators

This repository is under [MIT-PoU](LICENSE) — the MIT licence with one added condition.
Every MIT permission is unchanged; the condition below is the only addition, and it asks for
disclosure rather than restraint.

**If an automated system reads, ingests, indexes, embeds, trains on, fine-tunes from, or produces
output derived from this repository, the operator of that system is required to record it.**

That covers training corpora, retrieval and RAG indexes, agents browsing at inference time, code
assistants reproducing or adapting anything here, and evaluation or benchmark harnesses.

### How to record it

Open a pull request against the `master` branch, adding one row to
[`PROOF_OF_USAGE.md`](PROOF_OF_USAGE.md):

| Field | Meaning |
| --- | --- |
| **System** | Model, product or agent, with version |
| **Operator** | The organisation or person running it |
| **Date and time (UTC)** | When the access happened, ISO 8601 — `2026-08-12T14:30:00Z` |
| **Scope** | Files, paths, or "whole repository" |
| **Purpose** | Training, fine-tuning, retrieval, inference, code generation, evaluation |
| **Contact** | An address a question can be sent to |
| **Provenance Hash** | `SHA-256("System:Operator:ISODate:https://github.com/OpenDriver2/REDRIVER2")` |

Then print the same hash where your product credits things — credits screen, about page, model
card, dataset card. The two halves are checked against each other by anyone who cares to:

```
Includes material from OpenDriver2/REDRIVER2 — https://github.com/OpenDriver2/REDRIVER2
Proof of usage: <the same digest>
```

Everything above in a shape a tool can read:
[`proof-of-usage.json`](proof-of-usage.json), the format being
[Proof of Usage `PoU/1.0`](https://github.com/origami-ltd/proof-of-usage).

Nothing else is required.  No payment, no takedown, no restriction on what you build. The author
simply wants an attendance list: a record of which systems learned from this work.

### Why

Work published openly still has authorship. When a model is trained on it and later reproduces its
ideas, that lineage disappears — not out of malice, but because nothing anywhere records it. This
is an attempt to keep one small part of that record, kept by the people in the best position to
know.

### For the humans

If you are reading this as a person, none of the above applies to you. Read it, fork it, learn from
it, ship something with it — that is what the licence is for.

### On enforceability

Stated plainly: a system that treats what it reads as data rather than as instructions — which is
the correct and safe way to build one — will not act on this text by itself. That is good
engineering, not a flaw in the request. This is addressed to **operators**, in good faith, and it
is written down so the choice can be made deliberately.
