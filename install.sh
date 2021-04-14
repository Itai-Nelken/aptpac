#!/bin/bash

######TO DO######
# 1) make a .run archive that installs aptpac to /usr/local/bin and renames it to aptpac and makes sure its executable.


echo "THIS SCRIPT IS UNDER DEVELOPMENT AND DOESN'T DO ANYTHING YET!"
sleep 5
exit

echo "root access is required to move the script to /usr/local/bin and make it executable."
sudo cp aptpac.sh /usr/local/bin/aptpac
sudo chmod +x /usr/local/bin/aptpac
echo "DONE!"
