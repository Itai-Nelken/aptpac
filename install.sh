#!/bin/bash

echo "root access is required to move the script to /usr/local/bin and make it executable."
sudo cp aptpac.sh /usr/local/bin/aptpac
sudo chmod +x /usr/local/bin/aptpac
echo "DONE!"
