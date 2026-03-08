.SILENT: make install uninstall
make:
	echo -e "\e[1mUSAGE: run 'make install' to install and 'make uninstall' to uninstall.\e[0m"

install: aptpac.sh
	mkdir -p ~/.aptpac/completion
	cp ./aptpac.sh ~/.aptpac/
	cp ../aptpac.bash ~/.aptpac/completion/
	chmod +x ~/.aptpac/aptpac.sh
	echo "alias aptpac=\"~/.aptpac/aptpac.sh\"" >> ${HOME}/.bashrc
	echo "source \"~/.aptpac/completion/aptpac.bash\"" >> ${HOME}/.bashrc
	source ~/.bashrc
uninstall:
	sed -i '/alias aptpac=.*aptpac.*/d' ~/.bashrc
	sed -i '/source *completion*aptpac.*/d' ~/.bashrc
	rm -r ~/.aptpac
	source ~/.bashrc
