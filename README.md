# PlatyPus

A faceted, hierarchical, state-based, clustered platform monitoring system.
That was the plan in October 2017, anyway. What is in this repository is the
first evening's scaffolding: a C++11 daemon skeleton with signal handling and
a forking TCP listener, before any monitoring logic was written.

It is published as-is, as a historical snapshot. There is no roadmap.

## What the code does

The program registers handlers for 11 POSIX signals, starts a TCP listener
on a detached thread, prints the thread id, and then spins in an empty loop
forever. That is the whole of `main()`.

The listener (`tcp_listener.cpp`) is the classic Beej's Guide server shape:

1. `getaddrinfo` with `AI_PASSIVE` and `AF_UNSPEC`, so it binds IPv4 or
   IPv6, whichever comes first.
2. Bind to port **3490** with `SO_REUSEADDR`, listen with a backlog of 10.
3. Install a `SIGCHLD` handler that reaps children with `waitpid`.
4. On each accepted connection, `fork()`. The child closes the listening
   socket, starts a detached thread running `connection_handler`, and then
   spins in its own empty loop. The parent closes its copy of the
   connection and goes back to `accept()`.

`connection_handler` is an echo loop: whatever bytes arrive are written back
to the client until the peer disconnects, at which point the child process
exits. So the only observable behavior is that `nc localhost 3490` echoes
what you type.

The signal handler (`sig_handler.cpp`) catches HUP, INT, QUIT, ILL, ABRT,
FPE, KILL, SEGV, PIPE, ALRM and TERM through a single dispatcher that stores
the signal number in a global `sig_caught` and immediately zeroes it again.
Nothing reads it. Ctrl-C therefore does not stop the program; use `kill -9`
or close the terminal.

## Layout

| File | Purpose |
|---|---|
| `main.cpp` | Entry point: register signals, start the listener thread, spin. |
| `sig_handler.cpp` / `.h` | `register_signals()` and the per-signal stubs. |
| `tcp_listener.cpp` / `.h` | Fork-per-connection TCP echo server. Port and backlog are globals in the header. |
| `main.h` | Extern declarations shared across the three translation units. |
| `CMakeLists.txt` | Builds a single executable, links `pthread`. |
| `.idea/` | CLion project files from the day it was written. |

## Building

Requires CMake 3.9 or later and a C++11 compiler on Linux.

```sh
cmake -S . -B build
cmake --build build
./build/PlatyPus
```

**It does not compile on a current glibc.** `sig_handler.cpp` includes
`<bits/signum.h>`, a glibc-internal header that was removed in glibc 2.26
(2017). Replacing that include with `<csignal>` gets it building again on
Ubuntu 24.04 with GCC 13, with one format warning about printing a
`std::thread::id` through `%d`. The code is left exactly as committed in
2017; the fix is noted here rather than applied.

## Known rough edges

These are observations about the 2017 code, recorded so nobody mistakes the
skeleton for a design:

- The `switch` in `sig_handler()` has no `break` statements, so every case
  falls through to all the cases below it. Harmless today, since each stub
  does the same thing, but it is not intentional.
- `SIGKILL` cannot be caught. `register_signals()` asks anyway and will
  return 9 on every run; `main()` prints the failure and carries on.
- `connection_handler` echoes with `strlen()` on a buffer that is never
  NUL-terminated, so binary input or a 2000-byte message reads past what
  was received.
- Each connection costs a forked process *and* a detached thread *and* a
  busy loop that pins a core. Pick one... the fork alone would have done.
- `tcp_listener.h` defines its globals in the header, which works only
  because exactly one translation unit includes it.
- `tcp_listener.h` includes `<zconf.h>` (zlib's config header) for reasons
  that have not survived.

## License

GPL-3.0-or-later. See `LICENSE`.
