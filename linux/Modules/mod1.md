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
