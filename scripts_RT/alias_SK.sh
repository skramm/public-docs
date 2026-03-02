
alias gits="git remote -v;git status"

alias gitls="git ls-tree -r --name-only HEAD"

alias dokill="docker kill \$(docker ps -q); docker rm \$(docker ps -aq)"
alias dops="docker ps -a"

# un df sans les "loop"
alias dfh="df -h | grep -v loop"

# https://stackoverflow.com/a/70223290
alias glog="git log --graph --pretty=format:'%C(auto)%h%C(blue) %<|(19)%as%C(auto)%d %s'"

alias tpon="echo 'Touchpad: Activé';xinput set-prop 14 'Device Enabled' 1"
alias tpoff="echo 'Touchpad: Désactivé ';xinput set-prop 14 'Device Enabled' 0"

