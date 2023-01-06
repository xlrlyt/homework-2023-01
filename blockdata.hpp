//A: LLT
//Description
#pragma once

#include <stdlib.h>
#include <stdio.h>
#define BLOCK_NUM 7


int getLastHeight(int blockType, int blockHeight, int blockWidth, int blockRotation);
int getLastWidth(int blockType, int blockHeight, int blockWidth, int blockRotation);
const char** getBlock(int blockType, int blockRotation);