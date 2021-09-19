### How Linux Words Summary



##### Chapter 2: Basic Commands

---



- **terminal** = text input/output environment

- **console** = physical terminal

- **shell** = command line interpreter

  

<u>**Shell Keystrokes**</u>:

| Keystoke | Action                                       |
| -------- | -------------------------------------------- |
| ctrl -B  | Move the cursor left                         |
| ctrl -F  | Move the cursor right                        |
| ctrl -P  | View the previous command                    |
| ctrl -N  | View the next command                        |
| ctrl -A  | Move the cursor to the beginning of the line |
| ctrl -E  | Move the cursor to the end of the line       |
| ctrl-W   | Erase the preceding word                     |
| ctrl -U  | Erase from cursor to beginning of line       |
| ctrl -K  | Erase from cursor to end of line             |
| ctrl -Y  | Paste erased text                            |



<u>**Stream ID**</u>

Default Dtream ID is 1, for stdout.

For example, the next command will result with an empty backup.

```bash
ls /made_up_file > ./backup
```

Instead, we should use:

```bash
ls /made_up_file > ./backup 2>&1		# Direct stderr to stdout target
ls /made_up_file > ./backup 2> ./error	# Direct stderr to ./err
```



<u>**Listing Processes**</u>

```bash
ps uax

USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root           1  0.0  0.0 167716 11616 ?        Ss   Sep12   0:06 /sbin/init splash
```

u - Format Option

a - Remove "only user" restriction

x - Remove "must have tty" restiction

| Field | Desc                |
| ----- | ------------------- |
| %CPU  | CPU usage           |
| %MEM  | RAM usage           |
| VZS   | virtual memory size |
| RSS   |                     |
| STAT  | Process State Code  |



<u>**Process State Code**</u>

| Field | Desc                                                         |
| ----- | ------------------------------------------------------------ |
| D     | uninterruptible sleep (usually IO)                           |
| I     | Idle kernel thread                                           |
| R     | running or runnable (on run queue)                           |
| S     | interruptible sleep (waiting for an event to complete)       |
| T     | stopped by job control signal t    stopped by debugger during the tracing |
| W     | paging (not valid since the 2.6.xx kernel)                   |
| X     | dead (should never be seen)                                  |
| Z     | defunct ("zombie") process, terminated but not reaped by its parent |



<u>**kill command**</u>

```
kill -STOP pid	# stop process
kill -CONT pid	# continue process
```





#### Devices

---



- Block device
  - Programs access data from a block device in fixed chunks. The sda1 in
    the preceding example is a disk device, a type of block device. Disks can
    be easily split up into blocks of data. Because a block device’s total size
    is fixed and easy to index, processes have random access to any block in
    the device with the help of the kernel.



- Character device
  - Character devices work with data streams. You can only read characters
    from or write characters to character devices, as previously demonstrated
    with /dev/null. Character devices don’t have a size; when you read from or
    write to one, the kernel usually performs a read or write operation on
    46     Chapter 3the device. Printers directly attached to your computer are represented
    by character devices. It’s important to note that during character device
    interaction, the kernel cannot back up and reexamine the data stream
    after it has passed data to a device or process.



- Pipe device
  - Named pipes are like character devices, with another process at the other
    end of the I/O stream instead of a kernel driver.



- Socket device
  - Sockets are special-purpose interfaces that are frequently used for
    interprocess communication. They’re often found outside of the /dev
    directory. Socket files represent Unix domain sockets; you’ll learn more
    about those in Chapter 10.



##### The sysfs Device Path

- /dev directory is a convenient way for user processes
  to reference and interface with devices supported by the kernel.

- To provide a uniform view for attached devices based on their actual
  hardware attributes, the Linux kernel offers the sysfs interface through a
  system of files and directories. The base path for devices is /sys/devices. 

- For example, /sys/block should contain all of the block devices available on a system. However, those
  are just symbolic links; run ls -l /sys/block to reveal the true sysfs paths.

- Look for the device in the /sys directory.

- Guess the name from the output of the dmesg command (which prints the
  last few kernel messages) or the kernel system log file (see Section 7.2).

  This output might contain a description of the devices on your system.
  For a disk device that is already visible to the system, you can check the
  output of the mount command.

- Run cat /proc/devices to see the block and character devices for which
  your system currently has drivers. Each line consists of a number and
  name. The number is the major number of the device as described in
  Section 3.1. If you can guess the device from the name, look in /dev for
  the character or block devices with the corresponding major number,
  and you’ve found the device files.



#### Tracking Processes & FilesTracking Processes & Files

---

- lsof - list open files.
  - lsof -p pid
- uptime - Tell how long the system has been running + Load Average.
- time - run programs and summarize system resource usage.
- ps -o pid,min_flt,maj_flt 20365
- vmstat - Report virtual memory statistics
