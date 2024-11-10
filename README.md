# Minitalk

A simple client-server program that demonstrates communication between processes using UNIX signals.

## Overview

This project consists of two programs that work together:

#### Server
- Starts first and displays its Process ID (PID)
- Waits for incoming messages
- When it receives a message, displays it immediately
- Can handle messages from multiple clients without needing to restart

#### Client
- Takes two inputs:
  - The server's PID
  - The message to send
- Sends the message to the server
- Waits for confirmation that the message was received

The communication between the client and server is done entirely through UNIX signals.

### Installation
```
git clone https://github.com/42Monkey/42-minitalk.git minitalk
cd minitalk
make					# compiles with -Wall -Wextra -Werror
```

### How to Use
1. Start the server to display its PID:

```
./server
```

2. Send a message using the client:

```
./client [PID] [message]
```

- Example
```
./client 12345 "Hello World!"
./client 56789 "こんにちは"
./client 11235 "🍌🐵"
```

### Explanations

#### Signals
Minitalk uses two UNIX signals for communication:
- `SIGUSR1`: represents binary 0
- `SIGUSR2`: represents binary 1

Example: sending letter 'A'
ASCII 'A' (65) is binary: 01000001

```
1. SIGUSR1 (0)
2. SIGUSR2 (1)
3. SIGUSR1 (0)
4. SIGUSR1 (0)
5. SIGUSR1 (0)
6. SIGUSR1 (0)
7. SIGUSR1 (0)
8. SIGUSR2 (1)
```

Each character of the message is transmitted bit by bit using these signals.

#### Bitwise Operations
- The server reconstructs each character by shifting and combining received bits
- For each bit received:
  - Left shift the current byte
  - Set or clear the rightmost bit based on the signal
  - After 8 bits, display the complete character

#### Global Variable
The project uses one global variable (allowed) in the client: `volatile sig_atomic_t g_status`

This variable ensures reliable communication by:
- Tracking whether the server acknowledged receiving each bit
- Preventing data races in signal handlers
- Synchronizing the client's sending pace with the server's processing
The `volatile` and `sig_atomic_t` type are used to ensure proper behavior when accessing the variable from signal handlers.

### Features
- Server can receive messages from multiple clients
- Uses UNIX signals for communication
- Fast message transmission and display
- Supports text messages in any language
- Full unicode support (emoji, special characters, different alphabets)
- Handle errors

### Articles
- [Bamdeb Ghosh - How To Use Signal Handlers in C Language?](https://linuxhint.com/signal_handlers_c_programming_language/)
- [Mia Combeau - Sending and Intercepting a Signal in C](https://www.codequoi.com/en/sending-and-intercepting-a-signal-in-c/)

### Videos
- [Jacob Sorbier - Sending and Handling Signals in C](https://www.youtube.com/watch?v=83M5-NPDeWs)
- [CodeVault - Introduction to Signals in C](https://youtu.be/5We_HtLlAbs)
- [CodeVault - Handling Signals](https://www.youtube.com/watch?v=jF-1eFhyz1U)
- [CodeVault - Communicating Between Processes Using Signals](https://www.youtube.com/watch?v=PErrlOx3LYE)
- [Indronil Banerjee - Linux Sigaction System Call Programming](https://www.youtube.com/watch?v=_1TuZUbCnX0)

### Testing
- [Francinette](https://github.com/xicodomingues/francinette)
- [Lorem Ipsum](https://www.lipsum.com/)
- [Get Emoji](https://getemoji.com/)
