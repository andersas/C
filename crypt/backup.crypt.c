#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void crypt(char *buffer, int len, FILE *key) {
	int i;
	for (i = 0; i < len; i++) {

		buffer[i] = buffer[i] ^ ((char) fgetc(key));

	}
}


int main(int argc, char *argv[]) {

	int i;
	struct stat f1, f2;

	char name[51];
	char buffer[100];

	FILE *datafile, *keyfile, *resultfile;
	
	if (argc != 3 && argc != 4) {
		printf("Usage: crypt keyfile cryptfile [encrypt]\n");
		exit(1);
	}
	if (argc == 4 && strcmp(argv[3], "encrypt")) {
		printf("Usage: crypt keyfile cryptfile [encrypt]\n");
		exit(5);
	}

	if (stat(argv[1], &f1) || stat(argv[2], &f2)) {
		perror("stat: ");
		exit(2);
	}
	
	if (argc == 4) {
	if (f1.st_size < f2.st_size + 50) {
		printf("Error: Keyfile is too small (must be at least 50 bytes longer than cryptfile).\n");
		exit(3);
	}
	}
	else {
	if (f1.st_size < f2.st_size) {
		printf("Error: Keyfile is smaller than cryptfile.\n");
		exit(6);
	}
	}

	keyfile = fopen(argv[1], "rb");
	datafile = fopen(argv[2], "rb");
	
	if (argc == 3) {
		if (fread(name, 1, 50, datafile) < 50) {
			printf("Bad cryptfile length.\n");
			exit(7);
		}

		crypt(name, 50, keyfile);
		name[50] = '\0';

		printf("Filename: \"%s\".\nAccept (y/n) ", name);
		scanf("%s", &buffer);
		if (buffer[0] != 'y' && buffer[0] != 'Y') {
			printf("Quitting! Bad key or datafile...\n");
			exit(4);
		}

	} else {

		printf("Enter a name for the output file:\n");
		scanf("%s", name);
	}
		

	resultfile = fopen(name, "wb");

	if (argc == 4) {
		strcpy(buffer, argv[2]);
		crypt(buffer, 50, keyfile);
		fwrite(buffer, 1, 50, resultfile);
	}

	while (i = fread(buffer, 1, 100, datafile)) {
		crypt(buffer, i, keyfile);
		fwrite(buffer, 1, i, resultfile);
	}

printf("All done! Please destroy the key file!\n");

return 0;

}

