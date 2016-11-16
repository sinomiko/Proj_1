#########################################################################
# File Name: git_config.sh
# Author: Miko Song
# mail: mikosong2013@gmail.com
# Created Time: Sun 23 Oct 2016 07:44:48 PM PDT
#########################################################################
#!/bin/bash
:
 git config --global alias.co checkout
 git config --global alias.ci commit
 git config --global alias.st status
 git config --global alias.br branch
 git config --global alias.hist 'log --graph --format=format:"%C(red)%h%C(reset) %C(yellow)%ad%C(reset) | %s %C(green)\[%an\]%C(reset)%C(bold blue)%d%C(reset)" --abbrev-commit --date=short'
 git config --global alias.root 'rev-parse --show-toplevel'
 git config --global alias.alias '!git config --global --list | grep ^alias'
 git config --global alias.head 'rev-list -n1 --abbrev-commit HEAD'
