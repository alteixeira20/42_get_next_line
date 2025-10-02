<p align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C badge">
  <img src="https://img.shields.io/badge/Make-427819?style=for-the-badge&logo=cmake&logoColor=white" alt="Make badge">
  <img src="https://img.shields.io/badge/Shell-4EAA25?style=for-the-badge&logo=gnu-bash&logoColor=white" alt="Shell badge">
  <img src="https://img.shields.io/badge/Valgrind-773344?style=for-the-badge&logo=gnu&logoColor=white" alt="Valgrind badge">
  <img src="https://img.shields.io/badge/GDB-800000?style=for-the-badge&logo=gnu&logoColor=white" alt="GDB badge">
</p>

<h1 align="center">get_next_line</h1>
<p align="center"><em>Line-by-line streaming for 42 with static-control and self-hosted validation.</em></p>

<p align="center"><img src="docs/images/make_bonus.png" alt="Building library to test upon" width="85%"></p>

## Table of Contents
1. [At a Glance](#at-a-glance)
2. [Subject Compliance](#subject-compliance)
3. [Custom Tester](#custom-tester)
4. [Repository Layout](#repository-layout)
5. [Build & Integration](#build--integration)
6. [Usage Guidelines](#usage-guidelines)
7. [Feature Deep Dive](#feature-deep-dive)
8. [Input & Buffer Flow](#input--buffer-flow)
9. [Output Handling & HUD](#output-handling--hud)
10. [Internal Architecture](#internal-architecture)
11. [Tester Workflow](#tester-workflow)

## <a id="at-a-glance"></a>At a Glance
> **Highlights:** Single-responsibility C modules that return the next line from any descriptor with minimal reads.
- Leverages a static stash per descriptor to stitch partial buffers without global state or libft dependencies.
- Mandatory path focuses on correctness for a single file descriptor; bonus broadens coverage to concurrent descriptors and opt-in cleanup.
- Ships with a `.tester` harness so evaluators can observe behaviour live without external tooling.
- Implements `get_next_line` exactly as described in `docs/subject_gnl.pdf`, returning either the next newline-terminated slice or the final tail.
- Helper routines (`ft_strlen_gnl`, `ft_strjoin_gnl`, `ft_strdup_gnl`, `ft_substr_gnl`, `ft_strchr_gnl`) replicate the bare essentials usually sourced from libft, keeping the repository portable.
- Bonus build introduces `leftover[FD_SETSIZE]`, enabling alternating reads across descriptors and a sentinel cleanup call for leak-free sessions.

## <a id="subject-compliance"></a>Subject Compliance
> **Highlights:** Norm-aligned, static-only state, no forbidden calls.
- Restricts heap ownership to the reader helpers, freeing buffers on read failures or after lines are extracted so Deepthought detects no leaks.
- Avoids `lseek`, global variables, and libft usage; compiles cleanly with `-Wall -Wextra -Werror` and any `-D BUFFER_SIZE=n` override.
- Mandatory header `get_next_line.h` defaults to `BUFFER_SIZE 1`, bonus header escalates to 42, and both allow overrides during compilation as required by the subject.

## <a id="custom-tester"></a>Custom Tester
> **Highlights:** One-step build and run cycle for both mandatory and bonus expectations.
- `.tester/Makefile` exports `libgnl.a`, toggling sources via `make` (mandatory) or `make bonus`; every build echoes the active `BUFFER_SIZE` for traceability.
- C harnesses under `.tester/tests` exercise single-descriptor reads, large lines, invalid descriptors, and multi-descriptor interleaving scenarios.
- `run_test.sh` sweeps every compiled harness across the `test_cases/` corpus, regenerating deterministic outputs inside `tests/expected/`.

<p align="center"><img src="docs/images/running_test.png" alt="Running custom Tester" width="85%"></p>

## <a id="repository-layout"></a>Repository Layout
> **Highlights:** Minimal surface area; each directory earns its place.
- `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`: mandatory entry point and helpers kept under the 42 Norm length requirements.
- `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_utils2_bonus.c`, `get_next_line_bonus.h`: bonus equivalents with multi-descriptor support and shared helper logic.
- `.tester/Makefile`, `.tester/tests/`: local tester that compiles against the sources in-place and records expectations for regression checks.
- `docs/images/`: supporting visuals captured from actual tester runs for quick presentation moments.

## <a id="build--integration"></a>Build & Integration
> **Highlights:** Build in isolation, review artefacts, rinse, repeat.
- Invoke the tester from inside `.tester` to build the static library with your preferred `BUFFER_SIZE` override.
- Rebuild and relink automatically when sources change; `ar` and `ranlib` ensure evaluators get a clean archive for linking into defence harnesses.
- Bonus rule swaps the object set before generating `libgnl.a`, mirroring Moulinette's mandatory-then-bonus flow.

```sh
cd .tester
make BUFFER_SIZE=32       # build mandatory library with custom buffer
make bonus BUFFER_SIZE=64  # rebuild library with bonus sources
make run                   # compile harnesses and execute the full suite
```

## <a id="usage-guidelines"></a>Usage Guidelines
> **Highlights:** Treat the reader as a streaming API; free on every turn.
- Include `get_next_line.h` for the mandatory build or `get_next_line_bonus.h` when linking the bonus archive.
- Loop until `get_next_line(fd)` returns `NULL`, freeing each line immediately to avoid leaks in longer sessions.
- Adjust `BUFFER_SIZE` to explore stress cases (`1`, `42`, `1024`, etc.); the implementation trims reads to the minimal necessary chunk size.
- Call `get_next_line(-1)` after bonus use to trigger `cleanup_gnl` and release any cached leftovers held in the static array.

## <a id="feature-deep-dive"></a>Feature Deep Dive
> **Highlights:** Controlled memory joins, early exits, and defensive guardrails.
- `read_to_buffer` loops on `read`, concatenating buffers via `ft_strjoin_gnl` until a newline appears or EOF zeroes out the read count.
- `extract_line` slices the accumulated stash, duplicates the remainder, and rewires the static pointer, so ownership is always clear.
- Error handling is centralized: failed allocations or read errors funnel through `handle_read_error` to avoid dangling pointers.

<details>
  <summary>Memory discipline and helper interplay</summary>
  <p>
    <strong>ft_strjoin_gnl</strong> frees the left-hand side after merging, guaranteeing single ownership of each allocation. <strong>ft_substr_gnl</strong> clamps the requested length to the actual tail and returns an empty string when the starting index exceeds the source length. In the bonus build, <strong>cleanup_gnl</strong> walks the entire <code>leftover[FD_SETSIZE]</code> array, freeing each cell so long-running shells do not leak memory between tests.
  </p>
</details>

## <a id="input--buffer-flow"></a>Input & Buffer Flow
> **Highlights:** Designed for text streams with predictable chunking.
- Test fixtures in `.tester/tests/test_cases/` cover short, long, empty, and newline-toggled inputs to validate the buffer merge logic.
- Every `read` call uses the active `BUFFER_SIZE`, letting evaluators simulate single-byte dribbles or jumbo bursts to probe edge behaviour.
- Alternating descriptor reads (bonus) demonstrate that storing leftovers per descriptor prevents cross-contamination even in interleaved scenarios.

## <a id="output-handling--hud"></a>Output Handling & HUD
> **Highlights:** Console-friendly feedback on both library and tester sides.
- Library returns include the trailing newline when present, matching the subject's expectation and keeping downstream printing consistent.
- Tester binaries print deterministic prefixes (`FD1:`, `FD2:`) when exercising multiple descriptors so logs stay legible during evaluations.
- Status messages from the Makefile use basic ANSI colouring for readability while remaining optional (they collapse harmlessly when `tput` is unavailable).

## <a id="internal-architecture"></a>Internal Architecture
> **Highlights:** Small files, deliberate separation of concerns.
- Mandatory build uses a single static pointer scoped to `get_next_line`, keeping state minimal while still surviving successive calls.
- Bonus build expands to a static array indexed by file descriptor and introduces a sentinel branch (`fd == -1`) to trigger cleanup.
- Utility functions are shared between builds; the bonus headers are included in the mandatory utilities to avoid duplication and stay Norm-compliant.

## <a id="tester-workflow"></a>Tester Workflow
> **Highlights:** Deterministic pipelines and reproducible artefacts.
- `make run` compiles each `test_*.c` harness, links against `libgnl.a`, and executes them over every fixture in `test_cases/`.
- `run_test.sh` regenerates the `expected/` directory from scratch on every run, so diffs show only behavioural changes between commits.
- Status markers (`[PASS]`/`[FAIL]`) surface directly in the console log, allowing quick pass/fail scanning during peer evaluations.
alongside the regenerated artefacts.
- Focus remains on actionable outcomes (which fixture failed and why); incidental debug noise is excluded so bugs be fixed faster.
