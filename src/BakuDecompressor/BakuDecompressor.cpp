#include <stdio.h>
#include <intrin.h>
#include <string.h>
#include <malloc.h>

struct file_t {
	unsigned int prevData;
	char* data;
	int remainingBytes;
	int remainingBits;
};


// this actually just functions as a bitstream basically...
unsigned int ExtractBytes(file_t* file, int arg1) {
	int unk1 = -arg1 + 0x20;
	unsigned int retVal = 0;
	if (file->remainingBits < arg1) {
		if (file->remainingBytes == 0) {
			// this is likely just an error handler for if you reach eof, so not necessary
		}
		int leadingZeroes = __lzcnt(file->remainingBits);
		unsigned int prevData = file->prevData;
		char* origFile = file->data;
		file->prevData = _byteswap_ulong(((unsigned int*)file->data)[0]);
		retVal = (prevData << 0x20 - file->remainingBits) >> 0x20 - file->remainingBits & ~- (leadingZeroes >> 5 & 1);
		file->remainingBytes -= 4;
		if (file->remainingBits != 0x20) {
			retVal = retVal | _byteswap_ulong(((unsigned int*)file->data)[0]) << file->remainingBits;
		}
		file->data += 0x4;
		int prevRemain = file->remainingBits;
		file->remainingBits = 0x20 - (arg1 - file->remainingBits);
		file->prevData = file->prevData >> arg1 - prevRemain;
	}
	else {
		retVal = file->prevData;
		file->remainingBits -= arg1;
		file->prevData = file->prevData >> arg1;
	}
	/*unsigned int wtf = (retVal << unk1);
	unsigned int wtf2 = wtf >> (unk1 & arg1 | (0x20 - unk1));
	unsigned int wtf3 = wtf2 >> 0x1F;*/
	return (retVal << unk1) >> unk1 & (-arg1 | 0x20 - unk1) >> 0x1F;
}

int recursive_func(int* whoknows, int* param_1_121fc, file_t* file) {
	int uvar1 = *param_1_121fc;
	*param_1_121fc += 1;
	int* ivar10 = whoknows + (uvar1 * 4);
	bool compressed = ExtractBytes(file, 1) == 1;
	if (!compressed) {
		// ?? ;n;
		whoknows[(uvar1 * 4) + 1] = ExtractBytes(file, 9);//_byteswap_ushort(ExtractBytes(file, 9)); // WHY 9? WHAT
	}
	else {
		whoknows[(uvar1 * 4) + 1] = 0x1000;
		uvar1 = *param_1_121fc;
		int ivar9 = uvar1;
		*param_1_121fc += 1;
		bool compressed2 = ExtractBytes(file, 1) == 1;
		if (!compressed2) {
			whoknows[(uvar1 * 4) + 1] = ExtractBytes(file, 9);
		}
		else {
			// this is stupid and really should've been done through a recursive function
			whoknows[(uvar1 * 4) + 1] = 0x1000;
			uvar1 = *param_1_121fc;
			*param_1_121fc += 1;
			compressed2 = ExtractBytes(file, 1) == 1;
			if (!compressed2) {
				whoknows[(uvar1 * 4) + 1] = ExtractBytes(file, 9);
			}
			else {
				// this is stupid and really should've been done through a recursive function
				whoknows[(uvar1 * 4) + 1] = 0x1000;
				// NEW FUNCTION?!?!?!?!??!?!?
				whoknows[(uvar1 * 4) + 3] = recursive_func(whoknows, param_1_121fc, file); // line 56 in main function, 43 in recursive
				whoknows[(uvar1 * 4) + 2] = recursive_func(whoknows, param_1_121fc, file); // this function (FUN_001f2030) is based on this function up to the i < decompblocksize line, and not a loop obvs
			}
			// we do not stop. the pain train does not stop.
			// ptr to next? whacko
			whoknows[(ivar9 * 4) + 3] = (int)(whoknows + (uvar1 * 4));
			uvar1 = *param_1_121fc;
			*param_1_121fc += 1;
			compressed2 = ExtractBytes(file, 1) == 1;
			if (!compressed2) {
				whoknows[(uvar1 * 4) + 1] = ExtractBytes(file, 9);
			}
			else {
				// this is stupid and really should've been done through a recursive function
				whoknows[(uvar1 * 4) + 1] = 0x1000;
				// NEW FUNCTION?!?!?!?!??!?!?
				whoknows[(uvar1 * 4) + 3] = recursive_func(whoknows, param_1_121fc, file); // line 56 in main function, 43 in recursive
				whoknows[(uvar1 * 4) + 2] = recursive_func(whoknows, param_1_121fc, file); // this function (FUN_001f2030) is based on this function up to the i < decompblocksize line, and not a loop obvs
			}
			// we do not stop. the pain train does not stop.
			// ptr to next? whacko
			whoknows[(ivar9 * 4) + 2] = (int)(whoknows + (uvar1 * 4));
		}
		// store at start i guess?
		ivar10[3] = (int)(whoknows + (ivar9 * 4));
		uvar1 = *param_1_121fc;
		*param_1_121fc += 1;
		ivar9 = uvar1;
		compressed2 = ExtractBytes(file, 1) == 1;
		if (!compressed2) {
			whoknows[(ivar9 * 4) + 1] = ExtractBytes(file, 9);
		}
		else {
			// i am in agonizing pain
			whoknows[(ivar9 * 4) + 1] = 0x1000;
			uvar1 = *param_1_121fc;
			*param_1_121fc += 1;
			compressed2 = ExtractBytes(file, 1) == 1;
			if (!compressed2) {
				whoknows[(uvar1 * 4) + 1] = ExtractBytes(file, 9);
			}
			else {
				whoknows[(uvar1 * 4) + 1] = 0x1000;
				whoknows[(uvar1 * 4) + 3] = recursive_func(whoknows, param_1_121fc, file);
				whoknows[(uvar1 * 4) + 2] = recursive_func(whoknows, param_1_121fc, file);
			}
			// and we do it again because why the hell not
			whoknows[(ivar9 * 4) + 3] = (int)(whoknows + (uvar1 * 4));
			uvar1 = *param_1_121fc;
			*param_1_121fc += 1;
			compressed2 = ExtractBytes(file, 1) == 1;
			if (!compressed2) {
				whoknows[(uvar1 * 4) + 1] = ExtractBytes(file, 9);
			}
			else {
				whoknows[(uvar1 * 4) + 1] = 0x1000;
				whoknows[(uvar1 * 4) + 3] = recursive_func(whoknows, param_1_121fc, file);
				whoknows[(uvar1 * 4) + 2] = recursive_func(whoknows, param_1_121fc, file);
			}
			whoknows[(ivar9 * 4) + 2] = (int)(whoknows + (uvar1 * 4));
		}
		ivar10[2] = (int)(whoknows + (ivar9 * 4));
	}
	return (int)ivar10;
}

void DecompressFile(unsigned char* psuedoDecomp, file_t* file, unsigned char *out, int decompLeft) {
	int curr;
	// two megabytes allocation because *shrug*
	int* whoknows = (int*)malloc(1024*1024*2);

	// ?? zeroing out something
	do {
		if (file->remainingBytes <= 0) {
			break;
		}
		int uvar1 = 0;
		int decompBlockSize = ExtractBytes(file, 0x10);
		int param_1_121fc = 1;
		int* ivar10 = whoknows + (uvar1 * 4);
		bool compressed = ExtractBytes(file, 1) == 1;
		if (!compressed) {
			// ?? ;n;
			whoknows[1] = ExtractBytes(file, 9);//_byteswap_ushort(ExtractBytes(file, 9)); // WHY 9? WHAT
		}
		else {
			whoknows[(uvar1 * 4) + 1] = 0x1000;
			uvar1 = param_1_121fc;
			int ivar9 = uvar1;
			param_1_121fc += 1;
			bool compressed2 = ExtractBytes(file, 1) == 1;
			if (!compressed2) {
				whoknows[(uvar1 * 4) + 1] = ExtractBytes(file, 9);
			}
			else {
				// this is stupid and really should've been done through a recursive function
				whoknows[(uvar1 * 4) + 1] = 0x1000;
				uvar1 = param_1_121fc;
				param_1_121fc += 1;
				compressed2 = ExtractBytes(file, 1) == 1;
				if (!compressed2) {
					whoknows[(uvar1 * 4) + 1] = ExtractBytes(file, 9);
				}
				else {
					// this is stupid and really should've been done through a recursive function
					whoknows[(uvar1 * 4) + 1] = 0x1000;
					// NEW FUNCTION?!?!?!?!??!?!?
					whoknows[(uvar1 * 4) + 3] = recursive_func(whoknows, &param_1_121fc, file); // line 56 in main function, 43 in recursive
					whoknows[(uvar1 * 4) + 2] = recursive_func(whoknows, &param_1_121fc, file); // this function (FUN_001f2030) is based on this function up to the i < decompblocksize line, and not a loop obvs
				}
				// we do not stop. the pain train does not stop.
				// ptr to next? whacko
				whoknows[(ivar9 * 4) + 3] = (int)(whoknows + (uvar1 * 4));
				uvar1 = param_1_121fc;
				param_1_121fc += 1;
				compressed2 = ExtractBytes(file, 1) == 1;
				if (!compressed2) {
					whoknows[(uvar1 * 4) + 1] = ExtractBytes(file, 9);
				}
				else {
					// this is stupid and really should've been done through a recursive function
					whoknows[(uvar1 * 4) + 1] = 0x1000;
					// NEW FUNCTION?!?!?!?!??!?!?
					whoknows[(uvar1 * 4) + 3] = recursive_func(whoknows, &param_1_121fc, file); // line 56 in main function, 43 in recursive
					whoknows[(uvar1 * 4) + 2] = recursive_func(whoknows, &param_1_121fc, file); // this function (FUN_001f2030) is based on this function up to the i < decompblocksize line, and not a loop obvs
				}
				// we do not stop. the pain train does not stop.
				// ptr to next? whacko
				whoknows[(ivar9 * 4) + 2] = (int)(whoknows + (uvar1 * 4));
			}
			// store at start i guess?
			ivar10[3] = (int)(whoknows + (ivar9 * 4));
			uvar1 = param_1_121fc;
			param_1_121fc += 1;
			ivar9 = uvar1;
			compressed2 = ExtractBytes(file, 1) == 1;
			if (!compressed2) {
				whoknows[(ivar9 * 4) + 1] = ExtractBytes(file, 9);
			}
			else {
				// i am in agonizing pain
				whoknows[(ivar9 * 4) + 1] = 0x1000;
				uvar1 = param_1_121fc;
				param_1_121fc += 1;
				compressed2 = ExtractBytes(file, 1) == 1;
				if (!compressed2) {
					whoknows[(uvar1 * 4) + 1] = ExtractBytes(file, 9);
				}
				else {
					whoknows[(uvar1 * 4) + 1] = 0x1000;
					whoknows[(uvar1 * 4) + 3] = recursive_func(whoknows, &param_1_121fc, file);
					whoknows[(uvar1 * 4) + 2] = recursive_func(whoknows, &param_1_121fc, file);
				}
				// and we do it again because why the hell not
				whoknows[(ivar9 * 4) + 3] = (int)(whoknows + (uvar1 * 4));
				uvar1 = param_1_121fc;
				param_1_121fc += 1;
				compressed2 = ExtractBytes(file, 1) == 1;
				if (!compressed2) {
					whoknows[(uvar1 * 4) + 1] = ExtractBytes(file, 9);
				}
				else {
					whoknows[(uvar1 * 4) + 1] = 0x1000;
					whoknows[(uvar1 * 4) + 3] = recursive_func(whoknows, &param_1_121fc, file);
					whoknows[(uvar1 * 4) + 2] = recursive_func(whoknows, &param_1_121fc, file);
				}
				whoknows[(ivar9 * 4) + 2] = (int)(whoknows + (uvar1 * 4));
			}
			ivar10[2] = (int)(whoknows + (ivar9 * 4));
		}
		// i believe this is where recursive function ends, returning ivar10!
		// line 130...
		int* start = ivar10;
		// this is madness
		int bytesCopied = 0;
		int j = 0;
		while (j < decompBlockSize) {
			int* currLink = start;
			do {
				int compressed3 = ExtractBytes(file, 1);
				if (compressed3 == 0) {
					currLink = (int*)(currLink[2]);
				}
				else {
					currLink = (int*)(currLink[3]);
				}
			} while (currLink[1] == 0x1000);
			// what have we achieved, traversing that linked list like that?
			short tmp = _byteswap_ushort(currLink[1]);
			memcpy(psuedoDecomp + bytesCopied, &tmp, 2);
			bytesCopied += 2;
			++j;
			if (0xFF < currLink[1]) {
				// this hurts
				short bit12 = _byteswap_ushort(ExtractBytes(file, 0xC));
				// only...store...2 bytes...
				memcpy(psuedoDecomp + bytesCopied, &bit12, 2);
				bytesCopied += 2;
				++j;
			}
		}
		curr = 0;
		short* psuedoShort = (short*)psuedoDecomp;
		for (int i = 0; i < decompBlockSize;) {
			if (_byteswap_ushort(psuedoShort[curr / 2]) < 0x100) {
				// pretty sure this is how it works
				*out = psuedoDecomp[curr + 1];
				++out;
				++i;
				curr += 2;
			}
			else {
				int toProcess = _byteswap_ushort(psuedoShort[curr / 2]) - 0xFD;
				i += 2;
				curr += 2;
				int LZSSBack = _byteswap_ushort(psuedoShort[curr / 2]);
				curr += 2;
				int processedAlready = 0;
				if (toProcess > 0) {
					// this appears to just be an optimization check!
					int backCount = toProcess - processedAlready;
					if (backCount > 0) {
						while (backCount > 0) {
							*out = out[-LZSSBack];
							out += 1;
							--backCount;
						}
					}
				}
				// ? final file size probably
				decompLeft -= toProcess;
			}
		}
	} while (decompLeft > 0); // TODO: this maybe isn't right

	free(whoknows);
}

void DecompressFile1(file_t* file, unsigned char* out, int decompSize) {
	// this is much easier...
	for (int i = 0; i < decompSize;) {
		bool compressed = ExtractBytes(file, 1) == 1;
		if (!compressed) {
			// just get next byte and put it to out
			*out = ExtractBytes(file, 8);
			++out;
			++i;
		}
		else {
			// get how many bytes to copy from before
			int bytesToCopy = ExtractBytes(file, 4) + 3;
			int bytesBack = ExtractBytes(file, 0xC);
			i += bytesToCopy;
			for (int j = 0; j < bytesToCopy; ++j) {
				*out = out[-bytesBack];
				++out;
			}
		}
	}
}

void main(int argc, char *argv[]) {
	char *fname = (char*)"input.cpwb";
	char* oname = (char*)"output";
	if (argc >= 3) {
		if (strcmp(argv[1], "-i") == 0) {
			fname = argv[2];
		}
	}
	if (argc >= 5) {
		if (strcmp(argv[3], "-o")) {
			oname = argv[4];
		}
	}
	FILE* f = fopen(fname, "rb");
	fseek(f, 0x4, SEEK_SET);
	unsigned int fileVer;
	fread(&fileVer, 4, 1, f);
	//fileVer = _byteswap_ulong(fileVer);
	fseek(f, 0xC, SEEK_SET);
	int decompSize;
	fread(&decompSize, 4, 1, f);
	decompSize = _byteswap_ulong(decompSize);
	unsigned char* out = (unsigned char*)malloc(decompSize);
	unsigned char* psuedoDecomp = (unsigned char*)malloc(1024 * 1024 * 2); // again, 2 megs because ??
	file_t file;
	fseek(f, 0, SEEK_END);
	int fsize = ftell(f);
	fseek(f, 0x10, SEEK_SET);
	file.data = (char*)malloc(fsize - 0x10);
	fread(file.data, fsize - 0x10, 1, f);
	fclose(f);
	file.remainingBits = 0;
	file.prevData = 0;
	file.remainingBytes = fsize - 0x10;
	char* origdata = file.data;
	if (fileVer == 2) {
		DecompressFile(psuedoDecomp, &file, out, decompSize);
	}
	else if (fileVer == 1) {
		DecompressFile1(&file, out, decompSize);
	}
	// write output file
	f = fopen(oname, "wb");
	fwrite(out, decompSize, 1, f);
	// done, clean up
	fclose(f);
	free(origdata);
	free(out);
	free(psuedoDecomp);
}