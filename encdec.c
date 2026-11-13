#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int byte;

void uses(char *prog) { printf("uses: %s <enc|dec> <in File> <out File> <key>\n", prog); }

int proc(const char *inpPath, const char *outpPath, const char *key) { FILE *fin = fopen(inpPath, "rb"); FILE *fout = fopen(outpPath, "wb"); size_t keyLen = strlen(key);
if (!fin) { perror("input"); return 0; }
if (!fout) {perror("output"); fclose(fin); return 0; }
size_t i = 0; while ((byte = fgetc(fin)) != EOF) { unsigned char transfd = (unsigned char)byte ^ key[i % keyLen]; fputc(transfd, fout); i++; } fclose(fin); fclose(fout); return 1; }

int main(int argc, char *argv[]) {char *mode = argv[1]; char *inp = argv[2]; char *outp = argv[3]; char *key = argv[4];
if (argc < 5) { uses(argv[0]); return 1; }
if (strcmp(mode, "enc") == 0 || strcmp(mode, "dec") == 0) { if (proc(inp, outp, key)) { printf("PASS\n"); }
else { return 1; } }
else { printf("enc Or dec ? "); uses(argv[0]); return 1; } return 0; }
