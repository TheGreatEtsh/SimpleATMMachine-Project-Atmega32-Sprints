# SimpleATMMachine-Project-Atmega32-Sprints
- owner : Mighty minds -> sprints-Automotive BC - W11
- Team Members->
    - Momen Hassan 
    - Ahmed Mohamed Hesham
    - Ahmed Atef
     <!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="logo.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Simple ATM Machine</h3>

  <p align="center">
    Simple ATM Machine
    <br />
    <a href="https://github.com/TheGreatEtsh/SimpleATMMachine-Project-Atmega32-Sprints/tree/main/Documents"><strong>Explore the docs »</strong></a>
    <br />
    <br />
  </p>
</div>
## Configuration

### Flags

When calling `zoxide init`, the following flags are available:

- `--cmd`
  - Changes the prefix of the `z` and `zi` commands.
  - `--cmd j` would change the commands to (`j`, `ji`).
  - `--cmd cd` would replace the `cd` command (doesn't work on Nushell / POSIX shells).
- `--hook <HOOK>`
  - Changes how often zoxide increments a directory's score:
    | Hook     | Description                       |
    | -------- | --------------------------------- |
    | `none`   | Never                             |
    | `prompt` | At every shell prompt             |
    | `pwd`    | Whenever the directory is changed |
- `--no-cmd`
  - Prevents zoxide from defining the `z` and `zi` commands.
  - These functions will still be available in your shell as `__zoxide_z` and
    `__zoxide_zi`, should you choose to redefine them.
