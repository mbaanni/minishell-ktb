# minishell-ktb

## Launch :
```
make && ./minishell
```
## Requirements :
#### For linux :
```
sudo apt-get install libreadline6 libreadline6-dev
```
#### For 1337 macuser:
install brew : ``` curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh ```

add this line to makefile : ``` READ_LINE = -lreadline -L ${HOME}/homebrew/opt/readline/lib -I ${HOME}/homebrew/opt/readline/include ```
