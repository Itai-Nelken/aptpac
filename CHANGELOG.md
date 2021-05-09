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
<hr>
