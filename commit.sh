#!/bin/bash
read -p "Commit description: " desc
git add . && \
git add -u && \
git commit -m "<`date +'%Y-%m-%d %H:%M:%S %z'`> [$desc]" && \
git pull --rebase && \
git push origin master
