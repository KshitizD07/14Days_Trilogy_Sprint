# Module 01: Linux Filesystem & File Operations — Comprehensive Master Notes & Interview Guide

---

## 📑 Table of Contents
1. [Core Linux Architecture & Filesystem Philosophy](#1-core-linux-architecture--filesystem-philosophy)
2. [Filesystem Hierarchy Standard (FHS) & Key Directories](#2-filesystem-hierarchy-standard-fhs--key-directories)
3. [Paths & Filesystem Navigation](#3-paths--filesystem-navigation)
4. [File Types in Linux](#4-file-types-in-linux)
5. [File & Directory Management Operations](#5-file--directory-management-operations)
6. [Viewing, Reading & Inspecting Files](#6-viewing-reading--inspecting-files)
7. [Inodes, Hard Links & Symbolic (Soft) Links](#7-inodes-hard-links--symbolic-soft-links)
8. [Linux Permissions & Ownership Model](#8-linux-permissions--ownership-model)
9. [Special Permission Bits (SUID, SGID, Sticky Bit)](#9-special-permission-bits-suid-sgid-sticky-bit)
10. [Searching, Locating & Help Commands (`find`, `which`, `locate`, `man`)](#10-searching-locating--help-commands-find-which-locate-man)
11. [Summary Mapping of Interview Questions](#11-summary-mapping-of-interview-questions)

---

## 1. Core Linux Architecture & Filesystem Philosophy

### 🔍 Core Concepts
* **"Everything is a File" Philosophy:** In Linux, almost all system resources—including text files, directories, physical storage disks (`/dev/sda`), terminal consoles (`/dev/tty`), network sockets, running processes (`/proc`), and kernel runtime settings (`/sys`)—are exposed as files through the Virtual File System (VFS) layer.
* **Single Inverted Tree Structure:** Unlike Windows which uses drive letters (`C:`, `D:`), Linux represents the entire storage layout under a single root directory denoted by `/`. All partitions, remote network shares, and external drives are **mounted** as directories into this unified hierarchy.

---

### 🎯 Interview Q&A: Filesystem Architecture & Recovery

#### ❓ Q14: List any 3 types of filesystems?
* **Answer:** `ext4`, `XFS`, `Btrfs` (Linux native); `NTFS`, `FAT32`/`exFAT` (Windows compatible); `NFS` (Network Filesystem).
* **Detailed Explanation:**
  * **ext4 (Fourth Extended Filesystem):** The traditional default journaling filesystem for many Linux distributions (Debian/Ubuntu). Supports files up to 16 TB and volumes up to 1 EB.
  * **XFS:** High-performance 64-bit journaling filesystem optimized for handling large files and high I/O throughput (default in RHEL/CentOS).
  * **Btrfs (B-tree FS):** Modern copy-on-write (CoW) filesystem supporting snapshots, pooling, and multi-drive spanning.
  * **VFS (Virtual File System):** An abstraction layer in the Linux kernel that allows standard system calls (`open()`, `read()`, `write()`) to work uniformly across diverse underlying filesystem formats.

#### ❓ Q199: Which utility could you use to repair a corrupted filesystem?
* **Answer:** `fsck` (File System Consistency Check).
* **Detailed Explanation:**
  * `fsck` checks and repairs Linux filesystems.
  * **Usage Syntax:** `fsck /dev/sda1` or `fsck -y /dev/sdb1` (`-y` automatically answers yes to repair prompts).
  * **Crucial Sysadmin Rule:** **Never run `fsck` on a mounted, active filesystem** as it can cause catastrophic data corruption. Always unmount the partition first (`umount /dev/sdb1`) or boot into rescue/single-user mode.

---

## 2. Filesystem Hierarchy Standard (FHS) & Key Directories

The Filesystem Hierarchy Standard (FHS) defines the directory structure and directory contents in Linux distributions.

```
/ (Root Directory)
├── bin -> usr/bin          (Essential User Binaries)
├── sbin -> usr/sbin        (System Administration Binaries)
├── etc/                    (Host-specific System Configuration)
│   ├── fstab               (Static filesystem mount table)
│   ├── sudoers             (Sudo privilege configuration)
│   ├── passwd & shadow     (User account and password hashes)
│   ├── hosts & resolv.conf (Local hostname mapping & DNS servers)
│   └── motd                (Message of the Day displayed on login)
├── var/                    (Variable Data)
│   ├── log/                (System & Application Log Files)
│   └── lib/                (State information / Application data)
├── home/                   (Personal User Home Directories)
├── root/                   (Home Directory for the Root User)
├── usr/                    (Secondary hierarchy for read-only user data)
│   ├── bin/                (Standard user binaries)
│   ├── sbin/               (System administrative binaries)
│   └── local/              (Locally compiled / custom software)
├── opt/                    (Add-on third-party software packages)
├── tmp/                    (Temporary files; cleared on reboot)
├── proc/                   (Virtual FS: Kernel & Process runtime metrics)
├── sys/                    (Virtual FS: Device & Kernel hardware parameters)
├── dev/                    (Device nodes: sda, null, zero, random)
├── boot/                   (Static files of the boot loader & Kernel vmlinuz)
├── mnt/                    (Temporary manual mount point for filesystems)
├── media/                  (Mount point for removable media like USBs)
└── srv/                    (Site-specific data served by this system)
```

---

### 📂 Deep-Dive on Specific Directories

#### 1. `/bin` vs `/usr/bin` and `$PATH` Resolution
* **What is a Binary?** A compiled machine-code executable file.
* **`$PATH` Execution:** When you type a command (e.g., `ls`), the shell searches sequentially through the directories in `$PATH` (`/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin`) and executes the first matching binary found.
* **The Symlink Merge:** Historically, `/bin` held essential binaries needed to boot in single-user mode when `/usr` was on a separate disk. Modern Linux distributions merge them: `/bin` is a symbolic link pointing to `/usr/bin`.

#### 2. `/sbin` vs `/usr/sbin`
* Contains system binaries intended for administrators (`root`): `fdisk`, `iptables`, `useradd`, `reboot`, `ip`, `fsck`.

#### 3. `/etc` — The Configuration Capital
* Stores host-specific, plain-text configuration files controlling system and service behavior.

#### 4. `/var` — Variable Runtime Data
* Contains files to which the system writes data during operation:
  * `/var/log`: System logs (`syslog`, `auth.log`, `messages`, `nginx/`, `samba/`).
  * `/var/lib`: Application state data (Docker images/containers in `/var/lib/docker`, MySQL databases in `/var/lib/mysql`).

#### 5. `/proc` & `/sys` — Virtual Pseudo-Filesystems
* They do **not exist on disk**; they are generated dynamically in memory by the kernel.
* `/proc`: Exposes process and kernel information (e.g., `/proc/cpuinfo`, `/proc/meminfo`, `/proc/version`, `/proc/<PID>/`).
* `/sys`: Exposes kernel objects, device drivers, and hardware settings for runtime tuning.

#### 6. `/tmp` vs `/var/tmp`
* `/tmp`: Temporary scratch files, cleared on system reboot (often mounted as a `tmpfs` RAM-disk).
* `/var/tmp`: Temporary files that survive reboots.

#### 7. `/boot` — Kernel & Bootloader
* Contains the Linux Kernel (`vmlinuz`), initial RAM disk (`initramfs`), and GRUB bootloader configuration files.

---

### 🎯 Interview Q&A: FHS & Linux Directories

#### ❓ Q16: What is the `/bin` directory used for?
* **Answer:** `/bin` (User Binaries) contains essential command binaries used by all users (e.g., `ls`, `cp`, `mv`, `rm`, `cat`, `mkdir`, `bash`). On modern Linux distributions, it is symlinked to `/usr/bin`.

#### ❓ Q50: Which directory has all the commands we use, e.g. ls, cd etc.?
* **Answer:** `/usr/bin` (or `/bin`). Note that `cd` is a shell built-in command executed directly by the shell process.

#### ❓ Q26 & Q70: Which directory has all the configuration files and what is it used for?
* **Answer:** `/etc`. It contains system-wide configuration files and startup scripts that govern how the OS and installed applications operate (e.g., `/etc/hosts`, `/etc/fstab`, `/etc/ssh/sshd_config`).

#### ❓ Q38: What is the root user's home directory?
* **Answer:** `/root`. Unlike regular user home directories located in `/home/<username>`, the root superuser's home directory is `/root` so it remains available even if `/home` is on an unmounted separate partition.

#### ❓ Q44: What is `/proc` directory used for?
* **Answer:** `/proc` is a virtual/pseudo filesystem generated in RAM by the kernel. It provides a window into kernel data structures, hardware diagnostics, and running processes (`/proc/cpuinfo`, `/proc/meminfo`, `/proc/sys/net/ipv4/ip_forward`, `/proc/<PID>`).

#### ❓ Q109: List 4 different directories in `/`?
* **Answer:** `/etc`, `/bin`, `/var`, `/home` (also `/tmp`, `/proc`, `/root`, `/dev`, `/boot`).

#### ❓ Q139: What is the location of system logs (e.g. messages / syslog)?
* **Answer:** `/var/log` (e.g., `/var/log/messages` on RHEL/CentOS, `/var/log/syslog` on Ubuntu/Debian).

#### ❓ Q15: When you login you get a message on the screen. What is the name of that file and where is it located?
* **Answer:** `/etc/motd` (Message Of The Day) and `/etc/issue` (pre-login banner).
* **Detailed Explanation:** When a user logs in via SSH or console, PAM (Pluggable Authentication Modules) reads `/etc/motd` and displays its contents to the user.

#### ❓ Q178: What is `/etc/fstab` file and explain each column of this file?
* **Answer:** `/etc/fstab` (Filesystem Table) is a static configuration file listing storage devices, partitions, and remote shares to be automatically mounted at boot time.
* **Detailed Explanation (6 Columns):**
  1. **Device / UUID:** Block device identifier (e.g., `UUID=1234-abcd` or `/dev/sda1`).
  2. **Mount Point:** Directory path where the filesystem will be attached (e.g., `/`, `/home`, `/var`).
  3. **Filesystem Type:** Format type (e.g., `ext4`, `xfs`, `nfs`, `swap`).
  4. **Mount Options:** Mount flags (e.g., `defaults`, `noatime`, `ro`, `rw`, `nofail`).
  5. **Dump:** Backup flag used by the `dump` utility (`0` = ignore, `1` = backup).
  6. **Fsck Pass:** Filesystem check order on boot (`0` = skip, `1` = root filesystem check first, `2` = other filesystems).

#### ❓ Q204: Which file to modify to allow users to run root commands?
* **Answer:** `/etc/sudoers` (always edited using the safety tool `visudo`).
* **Detailed Explanation:** `visudo` locks the `/etc/sudoers` file and performs syntax validation before saving, preventing syntax errors that could lock all administrators out of `sudo` privileges.

#### ❓ Q206: Your system crashed and upon restart displays an error indicating that the operating system cannot be found. What is the most likely cause?
* **Answer:** The `/boot` partition or filesystem is corrupted, GRUB configuration is missing/damaged, or the kernel image (`vmlinuz`) / initramfs is missing.
* **Detailed Explanation:** During the boot sequence, BIOS/UEFI hands control to GRUB, which looks in `/boot` for kernel images. If `/boot` is unreadable or corrupted, boot halts. Repair involves booting via a Live CD/Rescue environment, mounting the root and boot filesystems, and reinstalling GRUB (`grub-install`) and regenerating configs (`update-grub` / `grub2-mkconfig`).

---

## 3. Paths & Filesystem Navigation

### 📍 Paths: Absolute vs. Relative
* **Absolute Path:** Always starts with the root directory `/`. Specifies the complete, unambiguous route from root regardless of your current directory.
  * *Example:* `/var/log/nginx/access.log`
* **Relative Path:** Starts without a leading `/`. Evaluated relative to the Current Working Directory (`PWD`).
  * *Example:* `../configs/app.yaml`, `./run.sh`, `subfolder/file.txt`

| Shortcut | Representation |
| :--- | :--- |
| `.` | Current working directory |
| `..` | Parent directory (one level up) |
| `~` | Current user's home directory (`/home/username` or `/root`) |
| `~username` | Specified user's home directory |
| `-` | Previous working directory (toggled with `cd -`) |

---

### 🧭 Navigation & Listing Commands

```bash
pwd              # Print Working Directory
cd /etc          # Change directory to absolute path
cd ../var/log    # Change directory relative to current
cd ~             # Go to home directory
cd -             # Jump back to previous directory ($OLDPWD)
```

#### Advanced `ls` Options:
* `ls -l`: Long format showing permissions, link count, owner, group, size, modification timestamp, name.
* `ls -a`: Show all files including hidden files (starting with `.`).
* `ls -la` / `ls -al`: Combine long format and hidden files.
* `ls -lh`: Human-readable file sizes (e.g., 4K, 25M, 2G).
* `ls -lt`: Sort by modification time, newest first.
* `ls -ltr`: Sort by modification time in **reverse** order (newest file at the very bottom).
* `ls -lS`: Sort by file size, largest first.
* `ls -lR`: Recursively list all subdirectories.
* `ls -d */`: List only directories in the current location.

---

### 🎯 Interview Q&A: Navigation & Paths

#### ❓ Q11: Explain the difference between relative and absolute path?
* **Answer:** An **absolute path** begins at the root filesystem directory (`/`) and specifies the full path to a file/directory from the top of the tree. A **relative path** starts from the current working directory without a leading `/` (e.g., using `.`, `..`, or subdirectory names).

#### ❓ Q46: List 3 basic commands to navigate the filesystem?
* **Answer:** `pwd` (print working directory), `cd` (change directory), `ls` (list directory contents).

#### ❓ Q71: Which command is used to list files in a directory?
* **Answer:** `ls` (or `ls -l` for detailed list).

#### ❓ Q88: Which command is used to list directory contents sorted by modification time in reverse order (most recently updated at the bottom)?
* **Answer:** `ls -ltr`
* **Detailed Explanation:**
  * `-l`: long listing format.
  * `-t`: sort by modification time (newest first).
  * `-r`: reverse sort order, placing the most recently modified files at the bottom of the terminal output—ideal for locating recent logs quickly.

#### ❓ Q128: How to list hidden files in a directory?
* **Answer:** `ls -a` (or `ls -la`). In Linux, any file starting with a dot (`.`) is hidden by default.

---

## 4. File Types in Linux

In `ls -l`, the very first character of the 10-character permission block indicates the file type:

```
-rw-r--r-- 1 root root 1024 Sep 4 10:00 app.log
▲
└─ File Type Indicator
```

| Character | File Type | Description & Example |
| :---: | :--- | :--- |
| `-` | **Regular file** | Plain text, source code, binary executables, compressed archives |
| `d` | **Directory** | Folder containing references to other files and subdirectories |
| `l` | **Symbolic link** | Soft shortcut pointing to another file path (`/bin -> usr/bin`) |
| `c` | **Character device** | Unbuffered sequential I/O hardware device (`/dev/tty`, `/dev/null`, `/dev/urandom`) |
| `b` | **Block device** | Buffered random-access storage device (`/dev/sda`, `/dev/nvme0n1`) |
| `s` | **Local socket** | Inter-process communication endpoint (`/run/systemd/private`) |
| `p` | **Named pipe (FIFO)** | First-In-First-Out pipe mechanism for IPC |

> 💡 **The `file` command:** Linux ignores Windows-style file extensions for determining binary formats. The command `file <filename>` inspects the magic numbers in the file header to determine its true format (e.g., `file script.sh` outputs `POSIX shell script, ASCII text executable`).

---

## 5. File & Directory Management Operations

### 🔨 Essential Operations & Flags

#### 1. Creating Files & Directories
```bash
touch file1.txt                     # Create empty file or update timestamp
mkdir dir1                          # Create single directory
mkdir -p projects/api/src/controllers # -p creates full parent path without error
mkdir {a..c}{1..3}                  # Brace expansion -> creates a1, a2, a3, b1, b2, b3, c1, c2, c3 (9 dirs)
```

#### 2. Copying (`cp`)
```bash
cp source.txt dest.txt              # Copy file
cp -r src_dir/ dest_dir/            # -r recursive: REQUIRED for directories
cp -p file.txt backup.txt           # -p preserves ownership, timestamps, and permissions
cp -v file.txt /tmp/                # -v verbose output
cp -i file.txt /tmp/                # -i interactive prompt before overwriting
```

#### 3. Moving & Renaming (`mv`)
Linux treats moving and renaming as the identical operation (updating directory entry pointers):
```bash
mv old_name.txt new_name.txt        # Rename
mv file.txt /var/tmp/               # Move
```

#### 4. Deleting (`rm`, `rmdir`)
```bash
rm file.txt                         # Delete file
rm -i file.txt                      # Prompt before delete
rm -r my_folder/                    # Recursive delete for non-empty directory
rm -rf my_folder/                   # Force recursive deletion (no confirmation)
rmdir empty_folder/                 # Only works on strictly EMPTY directories
```

#### 5. Comparing Files (`diff`)
```bash
diff file1.txt file2.txt            # Show line-by-line differences
diff -u file1.txt file2.txt         # Unified diff format (patch standard)
```

#### 6. Writing and Appending via Redirection
```bash
echo "Hello World" > file.txt       # Overwrite (or create) file
echo "New line" >> file.txt         # Append to end of file
cat fileA >> fileB                  # Append contents of fileA to the end of fileB
```

---

### 🎯 Interview Q&A: File & Directory Manipulation

#### ❓ Q5: How many new directories will be created after running `mkdir {a..c}{1..3}`?
* **Answer:** 9 directories.
* **Detailed Explanation:** The shell performs **brace expansion** before invoking `mkdir`. `{a..c}` expands to `a, b, c` and `{1..3}` expands to `1, 2, 3`. The Cartesian product creates: `a1, a2, a3, b1, b2, b3, c1, c2, c3`.

#### ❓ Q23: How to create a directory?
* **Answer:** `mkdir <directory_name>` (use `mkdir -p <path>` to create nested parent directories).

#### ❓ Q54: How to rename a file or directory?
* **Answer:** `mv oldname newname`

#### ❓ Q73: How to delete a file and a directory?
* **Answer:** `rm filename` for files; `rmdir dirname` for empty directories; `rm -r dirname` (or `rm -rf dirname`) for directories containing files.

#### ❓ Q91: How to view differences between two files?
* **Answer:** `diff file1 file2` (or `sdiff`, `vimdiff`, `diff -u`).

#### ❓ Q97: Explain the purpose of the `touch` command?
* **Answer:**
  1. Creates an empty file if the specified target does not already exist.
  2. Updates the access and modification timestamps of an existing file to the current system time without altering its content.

#### ❓ Q201: How to combine 2 files into 1? E.g., 3 lines in file "A" and 5 lines in file "B", combine into 8 lines?
* **Answer:** `cat fileA >> fileB` (appends fileA into fileB) or `cat fileA fileB > fileC` (combines both into a new file).

#### ❓ Q202: What is the `echo` command used for?
* **Answer:** Prints arguments/strings or environment variable values to standard output (terminal) or redirects them into files.

#### ❓ Q203: What does the command `echo This year the summer will be great > file1` do?
* **Answer:** It creates (or overwrites) `file1` with the text `"This year the summer will be great"`.

#### ❓ Q77: What are the different commands or methods to write to a file?
* **Answer:**
  1. **Redirection:** `echo "content" > file` or `echo "content" >> file`.
  2. **Heredoc (`cat << EOF`):** Multi-line block writes in scripts.
  3. **Interactive Text Editors:** `nano`, `vim`, `vi`.
  4. **Command Output Redirection:** `ls -l > inventory.txt`, `tee file.txt`.

---

## 6. Viewing, Reading & Inspecting Files

### 📖 Tools Comparison

| Command | Best Used For | Key Behavior / Features |
| :--- | :--- | :--- |
| `cat` | Short files | Dumps full content directly to stdout |
| `tac` | Reverse reading | Dumps lines in reverse order (bottom to top) |
| `less` | Huge files & logs | Paginated navigation (scroll up/down, `/search`, doesn't load whole file into memory) |
| `more` | Basic paging | Legacy paginated viewer (forward navigation only) |
| `head` | File headers | Shows first 10 lines by default (`head -n 20 file`) |
| `tail` | File footers / logs | Shows last 10 lines by default (`tail -n 50 file`) |
| `tail -f` | Live stream | Follows file growth in real-time as logs append |
| `wc` | File statistics | Counts lines (`wc -l`), words (`wc -w`), bytes (`wc -c`) |

---

### 🎯 Interview Q&A: Viewing & Stream Inspection

#### ❓ Q75: List 4 commands to display or read file contents?
* **Answer:** `cat`, `less`, `more`, `head` (also `tail`, `tac`, `view`).

#### ❓ Q57: Why is `tail -f logfilename` command used most often and what does it do?
* **Answer:** It streams and displays newly appended log entries in real-time.
* **DevOps Use Case:** Monitoring application output, HTTP access logs (`/var/log/nginx/access.log`), and system authentication events (`/var/log/auth.log`) live during deployments or active debugging.

#### ❓ Q74: What is the difference between `tail` and `tail -10`?
* **Answer:** There is **no difference**. By default, `tail` prints the last 10 lines of the file, which is identical to `tail -10` (or `tail -n 10`).

#### ❓ Q76: Which command is used to read the top 5 lines of a file?
* **Answer:** `head -5 filename` or `head -n 5 filename`.

#### ❓ Q99: Which command is used to count words or lines?
* **Answer:** `wc` (`wc -l` for lines, `wc -w` for words, `wc -c` for byte count).

#### ❓ Q110: What is the output of `$ tail -10 filename | head -1`?
* **Answer:** It extracts and displays the **10th line from the bottom** (i.e. the first line of the last 10 lines).
* **Pipeline Breakdown:** `tail -10` takes the last 10 lines of the file, then pipes (`|`) those 10 lines to `head -1`, which prints only the very first line of that subset.

#### ❓ Q180: What is the exact command to list only the first 2 lines of history output?
* **Answer:** `history | head -2` (or `history | head -n 2`).

#### ❓ Q190: Which command syntax can you use to list only the 20th line of a file?
* **Answer:**
  * Using `sed`: `sed -n '20p' filename`
  * Using `head` and `tail`: `head -n 20 filename | tail -n 1`
  * Using `awk`: `awk 'NR==20' filename`

#### ❓ Q194: You open a file with 3000 lines and it scrolls up too fast. Which command will you use to view it one page at a time?
* **Answer:** `less filename` (or `more filename`). `less` is preferred because it supports bidirectional scrolling, forward/backward regex search (`/` and `?`), and memory-efficient viewing.

---

## 7. Inodes, Hard Links & Symbolic (Soft) Links

### 🧱 Understanding Linux Inodes
An **inode (index node)** is a low-level data structure on a filesystem that stores all metadata about a file **except its filename and actual data content**.

* **What an inode contains:** File type, permissions (`rwx`), Owner UID, Group GID, file size, timestamps (atime, mtime, ctime), number of hard links, and disk block pointers.
* **Directory Role:** In Linux, a directory is simply a table mapping human-readable filenames to inode numbers.
* **Finding an inode:** Run `ls -i filename` or `stat filename`.

```
Disk Storage Architecture:
┌───────────────────────────┐
│ Directory Entry           │
│ Name: "app.log" ──┐       │
└───────────────────┼───────┘
                    ▼
┌───────────────────────────┐
│ Inode #10482              │
│ Permissions: -rw-r--r--   │
│ Owner: root | Size: 4096  │
│ Pointers: [Block 98, 99]  │
└─────────────┬─────────────┘
              ▼
┌───────────────────────────┐
│ Data Blocks on Disk       │
│ "2026-09-04 GET /api..."  │
└───────────────────────────┘
```

---

### 🔗 Hard Links vs. Symbolic (Soft) Links

```bash
ln original.txt hardlink.txt        # Create Hard Link
ln -s original.txt symlink.txt      # Create Symbolic Link
```

| Feature | Hard Link (`ln`) | Symbolic Link (`ln -s`) |
| :--- | :--- | :--- |
| **Target** | Points directly to the **inode** number | Points to the **path string** of the target file |
| **Inode Number** | Same inode number as target | Separate unique inode number |
| **Cross-Filesystem** | ❌ Cannot cross filesystem boundaries | ✅ Can point across different filesystems/disks |
| **Directories** | ❌ Cannot link directories (prevents loops) | ✅ Can link directories |
| **If Target is Deleted** | ✅ Data remains fully accessible via hardlink | ❌ Link becomes broken/dangling |
| **Link Count** | Increments hard link count in inode | Link count of original file is unchanged |

---

### 🎯 Interview Q&A: Inodes & Links

#### ❓ Q79: What is an inode and how to find an inode of a file?
* **Answer:**
  * An **inode** is a filesystem data structure containing file metadata (permissions, ownership, size, timestamps, block pointers).
  * To view the inode number: `ls -i filename` or `stat filename`. To check filesystem inode capacity: `df -i`.

#### ❓ Q168: How to create a soft link (symbolic link)?
* **Answer:** `ln -s /path/to/target link_name`

---

## 8. Linux Permissions & Ownership Model

### 🔐 Permission String Breakdown

Running `ls -l` presents a 10-character string:

```
- r w x r - x r - -
│ └──┬──┘ └──┬──┘ └──┬──┘
│    │      │      └── Others (World) Permissions: Read only (4)
│    │      └──────── Group Permissions: Read + Execute (4 + 1 = 5)
│    └─────────────── User (Owner) Permissions: Read + Write + Execute (4 + 2 + 1 = 7)
└──────────────────── File Type (- = regular file)
```

#### Meaning of `r`, `w`, `x` on Files vs. Directories:

| Permission | Effect on a Regular File | Effect on a Directory |
| :---: | :--- | :--- |
| **`r` (Read)** | View file contents (`cat`, `less`) | List directory contents (`ls`) |
| **`w` (Write)** | Modify or truncate file content | Create, rename, or delete files inside directory |
| **`x` (Execute)** | Execute as program/binary/script | `cd` into directory & access file metadata inside |

> ⚠️ **Crucial Rule:** To create or delete a file inside a directory, you need **`w` and `x` permissions on the parent directory**, regardless of your permissions on the file itself!

---

### 🔢 Numeric (Octal) vs. Symbolic `chmod`

#### Octal Values:
* `r = 4`
* `w = 2`
* `x = 1`
* `- = 0`

| Octal | Permissions | Common Practical Use |
| :---: | :---: | :--- |
| `755` | `rwxr-xr-x` | Executable scripts, public directories |
| `644` | `rw-r--r--` | Standard text/configuration files |
| `700` | `rwx------` | Private user directory (`~/.ssh`) |
| `600` | `rw-------` | Sensitive private keys (`~/.ssh/id_rsa`) |

#### Symbolic Syntax:
* **References:** `u` (user/owner), `g` (group), `o` (others), `a` (all).
* **Operators:** `+` (add), `-` (remove), `=` (set exact).

```bash
chmod u+x deploy.sh                 # Add execute for owner
chmod g-w config.yaml               # Remove write from group
chmod o=r notes.txt                 # Set others to read-only
chmod -R 755 /var/www/html          # Recursive permission change
```

#### Ownership Management:
```bash
chown alex app.py                   # Change owner to alex
chown alex:devops app.py            # Change owner and group
chgrp devops app.py                 # Change group only
chown -R www-data:www-data /var/www # Recursive ownership change
```

#### `umask` (User Mask):
Controls the default permissions assigned to newly created files and directories:
* Default base permissions: Files = `666`, Directories = `777`.
* Default umask: `0022`.
* Resulting file permissions: `666 - 022 = 644` (`rw-r--r--`).
* Resulting directory permissions: `777 - 022 = 755` (`rwxr-xr-x`).

---

### 🎯 Interview Q&A: Permissions & Ownership

#### ❓ Q13: What is the command to change file/directory ownership and group?
* **Answer:** `chown` (for owner and group) and `chgrp` (for group).

#### ❓ Q34: How to check a file's permissions?
* **Answer:** `ls -l <filename>` or `stat <filename>`.

#### ❓ Q68: What is the command to change file/directory permissions?
* **Answer:** `chmod` (e.g., `chmod 755 script.sh` or `chmod u+x script.sh`).

#### ❓ Q86: If I don’t want others to read my `file1`, how to do that?
* **Answer:** Remove read permission from others using `chmod o-r file1` (or set octal permissions such as `chmod 640 file1` or `chmod 600 file1`).

#### ❓ Q167: On file permissions, what are the first 3 bits for and who is it for?
* **Answer:** They represent Read (`r`), Write (`w`), and Execute (`x`) permissions for the **Owner (User)** of the file.

#### ❓ Q183: You tried to `cd` into a directory but got "Permission Denied". You are not the owner. What permission do you need and where?
* **Answer:** You need **Execute (`x`) permission** on that target directory for your group or others (`r-x` or `--x`).
* **Detailed Explanation:** In Linux, execute permission (`x`) on a directory allows a user to traverse into it (`cd`) and access files or subdirectories within it.

#### ❓ Q187: A user cannot write to a file because it says "Permission Denied", but the file is owned by that user. How do you troubleshoot?
* **Answer:** Check file permissions with `ls -l`. If the owner's write bit is missing (`-r--r--r--`), grant write permission using `chmod u+w <filename>` (or `chmod 644 <filename>`). Also verify that the filesystem is not mounted read-only (`ro`) and disk space/inodes are not exhausted (`df -h`, `df -i`).

---

## 9. Special Permission Bits (SUID, SGID, Sticky Bit)

Beyond standard `rwx`, Linux provides 3 special permission bits represented as a leading 4th octal digit:

```
Octal: 4 7 5 5
       │ └─┬─┘
       │   └── Standard permissions (rwxr-xr-x)
       └────── SUID bit active (4)
```

| Special Bit | Octal | Symbolic Position | Behavior on Files / Directories | Practical Example |
| :--- | :---: | :---: | :--- | :--- |
| **SUID** (Set User ID) | `4000` | `s` in owner execute (`-rwsr-xr-x`) | **On Executable Files:** Process runs with permissions of the **file owner** (usually root), not the calling user. | `/usr/bin/passwd` (allows regular users to modify `/etc/shadow`) |
| **SGID** (Set Group ID) | `2000` | `s` in group execute (`-rwxr-sr-x`) | **On Directories:** New files created inside automatically inherit the directory's **group ownership**. | Shared team collaboration directories (`/opt/devops_shared`) |
| **Sticky Bit** | `1000` | `t` in other execute (`drwxrwxrwt`) | **On Directories:** Only the file's owner or root can delete/rename files within the directory. | `/tmp` and `/var/tmp` |

```bash
# Setting Special Bits:
chmod 4755 /usr/local/bin/custom_tool # SUID
chmod 2775 /shared/devops/            # SGID
chmod 1777 /shared/scratch/           # Sticky Bit

chmod u+s file                        # Symbolic SUID
chmod g+s dir                         # Symbolic SGID
chmod +t dir                          # Symbolic Sticky Bit
```

---

### 🎯 Interview Q&A: Special Permissions

#### ❓ Q42: Which permission allows a user to run an executable with the permissions of the owner of that file?
* **Answer:** **SUID (Set User ID)** permission (octal `4000`, represented by an `s` in the owner's execute position: `-rwsr-xr-x`).
* **Security Context:** SUID binaries must be audited regularly (`find / -perm -4000 -type f 2>/dev/null`) because misconfigured SUID binaries can lead to privilege escalation attacks.

---

## 10. Searching, Locating & Help Commands (`find`, `which`, `locate`, `man`)

### 🔍 Finding Files: `find` vs. `locate`

* **`find`:** Scans the live filesystem directory tree in real time. Very powerful, supports matching on name, modification time, size, owner, permissions, and running batch commands via `-exec` or `-delete`.
* **`locate`:** Instant search using a pre-indexed database (`/var/lib/mlocate/mlocate.db`). Extremely fast, but may show stale results if database is not updated via `sudo updatedb`.

```bash
# Common find Recipes for Sysadmins & DevOps:
find / -name "httpd.conf" 2>/dev/null                    # Find file by name, suppress permission errors
find /var/log -iname "*.LOG"                             # Case-insensitive name search
find / -type f -size +100M                               # Find files larger than 100MB
find /var/log/myapp -name "*.log" -mtime +30 -delete     # Delete logs older than 30 days
find / -perm -4000 -type f 2>/dev/null                   # Security audit: find all SUID files
find / -perm -002 -type f 2>/dev/null                    # Security audit: find world-writable files
find ~/src -name "*.sh" -exec chmod +x {} +              # Make all matched shell scripts executable
```

---

### 📍 Locating Commands & Help

* `which <cmd>`: Shows the absolute path of the executable that will run from `$PATH` (e.g., `which chmod` -> `/usr/bin/chmod`).
* `whereis <cmd>`: Locates binary, source code, and man page files for a command.
* `type <cmd>`: Tells whether a command is a shell builtin (`cd`), alias (`ls`), function, or disk binary.
* `man <cmd>`: Opens the manual reference pages for a command. Press `q` to exit.

---

### 🎯 Interview Q&A: Searching & Command Help

#### ❓ Q72: There is a command which gives you information about other commands. Please explain that command and what it is used for?
* **Answer:** `man` (manual pages). It displays documentation covering command syntax, options, exit codes, and usage examples (e.g., `man ls`, `man fstab`).

#### ❓ Q170: How to quit out of the `man` command?
* **Answer:** Press `q`. (The `man` utility uses the `less` pager to render text).

#### ❓ Q125: Which command would you use to find the location of the `chmod` command?
* **Answer:** `which chmod` (or `whereis chmod` / `type chmod`).

#### ❓ Q169: How to write a command/script to delete log files older than 30 days automatically?
* **Answer:**
  ```bash
  find /var/log -type f -name "*.log" -mtime +30 -exec rm -f {} \;
  # OR using built-in -delete:
  find /var/log -type f -name "*.log" -mtime +30 -delete
  ```
* **Detailed Explanation:**
  * `-type f`: restricts matches to regular files.
  * `-name "*.log"`: targets files with `.log` extension.
  * `-mtime +30`: filters for files whose content was modified more than 30 days ago.
  * `-exec rm -f {} \;`: executes `rm -f` on each matched file (`{}` is replaced by filename).

#### ❓ Q205: You need to modify `httpd.conf` but cannot find it. Which command line tool can you use to find the file?
* **Answer:**
  ```bash
  find / -name "httpd.conf" 2>/dev/null
  # OR
  locate httpd.conf
  ```
* **Detailed Explanation:** `find / -name "httpd.conf"` searches starting from the root directory `/`. Appending `2>/dev/null` redirects `stderr` (permission denied errors for non-root users) to the null device, keeping the output clean.

---

## 11. Summary Mapping of Interview Questions

| Question # | Topic Covered | Target Command / Concept |
| :---: | :--- | :--- |
| **Q5** | Brace expansion & directory creation | `mkdir {a..c}{1..3}` |
| **Q11** | Path architecture | Absolute vs. Relative Paths |
| **Q13** | File & directory ownership | `chown`, `chgrp` |
| **Q14** | Filesystem types | `ext4`, `XFS`, `Btrfs`, `NTFS` |
| **Q15** | Login banner configuration | `/etc/motd` |
| **Q16** | FHS binary directories | `/bin` & `/usr/bin` |
| **Q23** | Creating directories | `mkdir` |
| **Q26** | System configuration repository | `/etc` |
| **Q34** | Inspecting file permissions | `ls -l`, `stat` |
| **Q38** | Superuser home directory | `/root` |
| **Q42** | Special permissions / SUID | SUID (`4000` / `-rwsr-xr-x`) |
| **Q44** | Kernel runtime pseudo-filesystem | `/proc` |
| **Q46** | Core filesystem navigation | `pwd`, `cd`, `ls` |
| **Q50** | Location of standard binaries | `/usr/bin`, `/bin` |
| **Q54** | Renaming files/directories | `mv` |
| **Q57** | Real-time log monitoring | `tail -f` |
| **Q68** | Changing file permissions | `chmod` |
| **Q70** | Purpose of `/etc` | System-wide configuration |
| **Q71** | Directory listing | `ls` / `ls -l` |
| **Q72** | Command documentation | `man` |
| **Q73** | Deletion operations | `rm`, `rmdir`, `rm -rf` |
| **Q74** | Default tail output | `tail` vs `tail -10` |
| **Q75** | File viewing utilities | `cat`, `less`, `more`, `head`, `tail` |
| **Q76** | Reading file head | `head -n 5` |
| **Q77** | Methods to write to files | `echo >`, Heredoc, Editors |
| **Q79** | Inodes and file metadata | Inode definition, `ls -i`, `stat` |
| **Q86** | Restricting read permissions | `chmod o-r filename` |
| **Q88** | Reverse time listing | `ls -ltr` |
| **Q91** | Comparing files | `diff`, `diff -u` |
| **Q97** | File creation & timestamps | `touch` |
| **Q99** | Word and line count | `wc`, `wc -l` |
| **Q109** | Top-level FHS directories | `/etc`, `/bin`, `/var`, `/home`, `/tmp` |
| **Q110** | Pipeline line extraction | `tail -10 filename \| head -1` |
| **Q125** | Locating executable binaries | `which chmod` |
| **Q128** | Listing hidden dotfiles | `ls -a`, `ls -la` |
| **Q139** | System logs repository | `/var/log` |
| **Q167** | First 3 permission bits | Owner / User `rwx` bits |
| **Q168** | Creating soft links | `ln -s` |
| **Q169** | Automated cleanup with `find` | `find -mtime +30 -delete` |
| **Q170** | Exiting manual pager | `q` |
| **Q178** | Filesystem Table columns | `/etc/fstab` 6-column breakdown |
| **Q180** | Piped command output limiting | `history \| head -2` |
| **Q183** | Directory traversal permissions | Directory Execute (`x`) bit |
| **Q187** | Resolving owner write denials | `chmod u+w filename` |
| **Q190** | Extracting specific lines | `sed -n '20p'`, `head \| tail` |
| **Q194** | Large file paging | `less`, `more` |
| **Q199** | Filesystem integrity repair | `fsck` |
| **Q201** | Combining/appending files | `cat fileA >> fileB` |
| **Q202** | Standard output printing | `echo` |
| **Q203** | Output redirection overwrite | `echo "..." > file1` |
| **Q204** | Superuser privilege configuration | `/etc/sudoers`, `visudo` |
| **Q205** | Finding missing files | `find / -name "..."` |
| **Q206** | Boot failure diagnostics | `/boot` corruption, GRUB repair |