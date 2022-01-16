all: lsd

lsd:
	gcc main.c -o lsd


install: 
	gcc main.c -o lsd
	sudo cp lsd /usr/bin/
	sudo chown root:root /usr/bin/lsd
	sudo chmod +x /usr/bin/lsd
	sudo mkdir /var/lib/lsd
	sudo chmod 777 /var/lib/lsd
	touch /var/lib/lsd/pidlist

