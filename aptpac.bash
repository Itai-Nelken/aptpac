_compgen() {
  local i r
  COMPREPLY=($(compgen -W '$*' -- "$cur"))
  for ((i=1; i < ${#COMP_WORDS[@]}-1; i++)); do
    for r in ${!COMPREPLY[@]}; do
      if [[ ${COMP_WORDS[i]} = ${COMPREPLY[r]} ]]; then
        unset 'COMPREPLY[r]'; break
      fi
    done
  done
}

_pkgs() {
  local act
  [[ "$1" == "all" ]] && arg=Slq
  [[ "$1" == "installed" ]] && arg=Qq
  _compgen "$(pacman -$arg 2>/dev/null | cut -d' ' -f1 | sort -u)"
}

_aptpac() {
  compopt -o default
  local cur prev words cword
  _init_completion || return
  local core
  core=("install" "install-local" "remove" "purge" "search" "find" "update" "upgrade" "full-upgrade" "autoclean" "clean" "autoremove" "show" "show-all" "list-installed" "help" "version")
  for opt in "${core[@]}"; do
  	[[ "$COMP_LINE" =~ "$opt" ]] && break
  done
  if [[ $? != 0 ]]; then 
    _compgen "${core[@]}"
  else 
    case $opt in
      install|show-all) _pkgs all;;
      upgrade|remove|purge|show) _pkgs installed;;
      *) compgen +o default;;
    esac
  fi
}

complete -F _aptpac aptpac
