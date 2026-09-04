# Module 1: Linux Filesystem & Command Execution

## 📂 Command Binaries: `/bin` vs `/usr/bin`

### 🔍 Core Concepts
* **What is a Binary?** A binary is a compiled, machine-code executable file residing on the storage disk.
* **Commands are Files:** In Linux, almost all commands (e.g., `ls`, `mkdir`, `cat`) are simply executable binary files or scripts located somewhere on the filesystem. When you run a command, the shell locates and executes that file.

---

### 🌐 The Path Variable (`$PATH`)
When you type a command and hit Enter, Linux doesn't scan the entire filesystem. Instead, it looks in a specific list of directories defined in your `$PATH` environment variable.

You can view these directories by running:
```bash
echo $PATH
```

**Example Output:**
```text
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
```

The shell searches through these paths sequentially (from left to right) until it finds the matching executable. For instance, if you type `ls`:
1. It looks in `/usr/local/sbin` (Not found)
2. It looks in `/usr/local/bin` (Not found)
3. It looks in `/usr/sbin` (Not found)
4. It looks in `/usr/bin` (Found: `/usr/bin/ls`) 🚀 *Executes the binary*

---

### 🔄 The Symlink Merge (`/bin` ➔ `/usr/bin`)

> [!NOTE]  
> **Historical vs. Modern Layout:**
> * **Historically:** `/bin` contained critical system commands required to boot or repair the system in single-user mode (even if the `/usr` directory was not mounted). `/usr/bin` contained non-critical user-facing applications.
> * **Modern Linux (e.g., Ubuntu/Debian/Fedora):** Modern distributions merge these directories to simplify the filesystem hierarchy. `/bin` is now a symbolic link (symlink) pointing directly to `/usr/bin`.

---

## 🛠️ System Administration Binaries: `/usr/sbin`

### ⚙️ What is `/usr/sbin`?
The **`s`** in `sbin` stands for **System**. This directory contains administrative binaries and commands used for system maintenance, network configuration, and system control.

* **Target Audience:** Typically intended for the system administrator (`root` or users with `sudo` privileges).
* **Scope of Action:** Unlike regular user binaries, these commands affect the hardware, system state, services, or overall system configuration, rather than just manipulating user files.

### 📋 Common Commands in `/usr/sbin`

| Command | Description |
| :--- | :--- |
| `useradd` / `usermod` | Manage system user accounts and groups. |
| `iptables` | Configure packet filtering rules (firewall). |
| `fdisk` | Partition and manage storage disks. |
| `shutdown` / `reboot` | Power down or restart the computer. |


/etc -> It stores system wide config files. The program lives in /bin or /sbin meanwhile their settings(configuration) lives in /etc. DNS, users, nginx, any type of configuration or error is resolved from /etc. In intuitive terms, it's for how the system should behave.

/var -> It contains runtime data(variable data) that changes often while the process is ongoing.
/var/lib -> It stores application data. More like "The application's memory on disk". Docker stores lots of data here(/var/lib/Docker).
Database might also store data here(/var/lib/mysql).

/home -> It is the personal workspace(directory) for the normal users(/home/kshit/cs...).

/root -> It is the home directory for the root(administrators) users(/root). Only root can access files under this.

/usr -> It contains most of the OS's software. Programs installed using package manager. Most of the linux lives here.
/usr/local -> It stores software installed without using the manager(apt).

/tmp -> These are temporary files that are cleared automatically on reboot. 

/proc -> These are the files exposing the kernel and processes info. They are not stored on the disk but are created at runtime dynamically(i.e.cpuinfo, meminfo, runtime, etc), used for the process of troubleshooting.

/sys -> Similar to /proc but for advanced system fine-tuning.

/boot -> It contains linux kernel and boot loader files. In WSL windows handles it automatically.

/mnt -> Manual mount points i.e. accessing windows files from wsl. They are mounted on file hierarchy under /mnt.

/media -> Auto mounted removable devices i.e. USB drivers, External drives, peripherals, they live here.




ABSOLUTE PATH-> Starts from the root of the tree '/' ; /home/kshit/projects/app...
RELATIVE PATH-> Relative to your current working directory ; projects/app...

pwd: print working directory
cd: change directory
ls: simple list of exitsting cotents
ls -a: show hidden dotfiles as well.
ls -la: combine: long format + hidden files.
ls -lh: gives data in human redable sizes
ls -lt: sort by modification time
ls -lS: sort by size, largest first
ls -lR: recurse into subdirectories
ls -d */: list only directories in current location






