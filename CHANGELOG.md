# aptpac's changelog
**DD/MM/YY**

### 15/4/2021
- Initial commit
- Versions 0.1-alpha and 0.1.1-alpha released.
- Theoretically the script is fully functional
### 03/5/2021
- Split the `update` command to `update` and `upgrade` so its more similar to apt.
- Version 0.3.1-alpha
### 05/5/2021
- make C edition as good as the bash edition.
- add 'purge' option to bash and C edition.
- fix typo in the help function in the C and bash editions.
- add 'show' and 'show-all' commands (C and bash editions).
- CleanMachine1: change the `clean`/`autoclean` from `pacman -Sc` to `pacman -Scc`.
- CleanMachine1: add `full-upgrade` (same as `upgrade`).
### 06-07/5/2021
- add workflows for github-actions for daily builds for each commit and pr and for checking if compilation is succesfull (for C-edition).
- error and exit if no packages are provided in `show` and `show-all` commands (C-edition).
- add `-DLEARN=1` and `-DCALLCOMMAND="xxx"` to CMakeLists.txt to compile with learning mode on and the command to use as the program name when printing the help respectively (C-edition)
### 09/05/2021
- If no option is passed for `CALLCOMMAND`, use default `aptpac` value, if a value that isn't `aptpac` or `./aptpac` is given, give a warning and use default `aptpac` as well.
- Improvement to about function (shown when running `aptpac --version`).
- Bumped version to 2.2
- Improved foundation for learning mode setting saving in bash edition.
- add experimental makefile for bash edition.
### 19/5/2021 (and a bit before that I forgot to add)
- Bump version to 2.5 (C-edition) and 2.5-bash (bash edition).
- Add ability to enable and disable learning mode in runtime (bash edition only).
- Add 'install-local' command to install local packages (pacman -U).
- Improve 'search' command (C-edition).
- more that I forgot to document...
### 28/5/2021
- bash edition: fix 'config' function when loading a single setting.
- C-edition: add DEBUG option that prints debug info in some places when enabled (enable with '-DDEBUG=1' when configuring with cmake).
- C-edition: add 'debug' function if debug mode enabled.
### 8/6/2021
- C-edition (also bash edition): add the ability to toggle learning mode in runtime using the `APTPAC_LEARN` environment variable.
- Release 2.6 (and 2.6-bash)
<hr>
