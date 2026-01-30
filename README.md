#Terminal Snake Game (C++ | Linux)

A lightweight **Snake Game** built in **C++** for the Linux terminal using low-level system programming. No graphics libraries, no game engines — just pure C++, terminal rendering, and real-time input handling.

This project focuses on understanding how games work internally: input systems, game loops, logic processing, and rendering — all inside the terminal.

---

##Features

* Real-time keyboard controls (W A S D)
* Non-blocking input system
* Smooth movement using microsecond timing
* Dynamic snake tail growth
* Random food generation
* Wall & self-collision detection
* Score system
* Clean ASCII terminal rendering

---

## Concepts Used

* Game loop architecture
* Linux terminal control (`termios`)
* Non-blocking input (`fcntl`)
* Timing control (`usleep`)
* Enums for direction handling
* Array-based memory management
* Real-time state updates

---

## Controls

| Key | Action |
| --- | ------ |
| W   | Up     |
| A   | Left   |
| S   | Down   |
| D   | Right  |
| X   | Exit   |

---

##Future Improvements

* Speed levels
* High-score saving
* Pause system
* Colored rendering
* Obstacles
* OOP refactor
* Multiplayer support

---

##License

Open-source. Free to use for learning and personal projects.
