# Process Monitor

A lightweight Linux process monitoring tool that displays running processes with their PID, name, and state.

## Features
- Lists all running processes
- Shows PID, process name, and process state
- Reads data from /proc filesystem

## Build
```bash
make
```
## Usage 
```bash
./runtime
```
## Process States
R: Running
S: Sleeping
D: Disk Sleep
T: Stopped
I: Idle
