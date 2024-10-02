# Minitalk

Minitalk is a client-server communication program designed to demonstrate inter-process communication (IPC) using signals in C. This project is part of the 42 school curriculum, focusing on low-level system programming concepts such as signal handling, bit manipulation, and memory management.

## How It Works

The Minitalk project consists of two parts: a server and a client.

### Server

- The server starts by printing its PID (Process ID) and waits for signals.
- It receives signals from the client and reconstructs the binary data into characters, then prints the message.

### Client

- The client takes a message, converts each character into binary, and sends the binary data bit-by-bit to the server using two signals:
  - SIGUSR1: Represents a binary 0.
  - SIGUSR2: Represents a binary 1.

## Communication Process

- The server listens for SIGUSR1 and SIGUSR2 signals using the sigaction system call.
- The client sends each character of the message to the server as a sequence of signals.
- The server assembles the bits received from the signals into characters and prints the message.

## Code Explanation

### server.c

The server listens for SIGUSR1 and SIGUSR2 signals. Each signal corresponds to a bit (0 for SIGUSR1, 1 for SIGUSR2). The server shifts these bits into position to form characters and prints the result. Once a full character is reconstructed, it is displayed in the terminal.

Key steps in the server:

1. Signal handling: The server uses sigaction to set up handlers for SIGUSR1 and SIGUSR2.
2. Reconstructing characters: For each signal received, the server shifts the bits left and accumulates them into a complete character.
3. Displaying the message: After receiving a full character, it is printed to the terminal.

### client.c

The client takes a string and converts each character to its binary representation. For each bit, it sends SIGUSR1 or SIGUSR2 to the server, depending on whether the bit is 0 or 1. The kill function is used to send the signals to the server’s PID.

Key steps in the client:

1. Binary conversion: The client converts each character into a sequence of bits.
2. Signal transmission: Each bit is sent as either SIGUSR1 (for 0) or SIGUSR2 (for 1).
3. Message delivery: The client sends the message bit-by-bit to the server, waiting briefly between each signal.

## Resources

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
