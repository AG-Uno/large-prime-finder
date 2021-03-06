/*
 * Copyright 2014 Google Inc. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef LARGE_U_INT_H
#define LARGE_U_INT_H

#include <stdio.h>
#include <stdint.h>

#define MAX_NUM_LARGE_U_INT_BYTES 30

// A string buffer to hold a LargeUInt's base 10 represenation could be up to
// three times the number of bytes with one more byte for the trailing null
// terminator. This should be a safe overestimate.
#define BASE_10_LARGE_U_INT_BUFFER_SIZE MAX_NUM_LARGE_U_INT_BYTES * 3 + 1

typedef struct {
  int num_bytes_;
  uint8_t bytes_[MAX_NUM_LARGE_U_INT_BYTES];
} LargeUInt;

// The human readable format for large ints is in the following form: The
// number of bytes is listed first in hexidecimal using 2 bytes in little
// endian order. So for example 0A00 means that the number's value fits in 10
// bytes. The number of bytes is followed by an underscore as a seperator,
// then the bytes in the number's value are listed in hexidecimal in little
// endian order. As an example, the number 0x3D4A50 (4,016,720 in base 10)
// would be represented as 0300_054A3D.
void LargeUIntPrint(const LargeUInt* this, FILE* out);

// Prints out the base 10 (decimal) equivalent of the value stored in the
// large unsigned interger. This lists high order digits first as one would
// typically see an integer written.
void LargeUIntBase10Print(const LargeUInt* this, FILE* out);

// Reads the next available LargeUInt from the file and stores the value in
// the provided LargeUInt.
void LargeUIntRead(FILE* in, LargeUInt* this);

// Provides the number of characters required for the text representation
// of this large unsigned integer.
int LargeUIntBufferSize(const LargeUInt* this);

// Writes a text representation of this large unsigned integer into the
// provided string buffer.
void LargeUIntStore(const LargeUInt* this, int buffer_size, char* buffer);

// Writes the number as decimal text, with the high order digits listed
// first.
void LargeUIntBase10Store(
    const LargeUInt* this, int buffer_size, char* buffer);

// Reads the text representation of a large unsigned integer from a string
// and stores loaded value into the provided location.
void LargeUIntLoad(int buffer_size, char* buffer, LargeUInt* this);

// Initializes the large unsigned integer to be ready to store a value.
void LargeUIntInit(int starting_size, LargeUInt* this);

// Increases available size in the large unisigned integer's internal storage.
void LargeUIntGrow(LargeUInt* this);

// Removes any leading zeroes by shrinking the number of bytes.
void LargeUIntTrim(LargeUInt* this);

// Sets the byte at index to the provided value if the index is in range and
// the value will fit into an unsigned byte.
void LargeUIntSetByte(int value, int index, LargeUInt* this);

// Retrieves one byte from within the large unsigned integer.
int LargeUIntGetByte(int index, const LargeUInt* this);

// Reports the number of bytes currently in the large unsiged integer.
int LargeUIntNumBytes(const LargeUInt* this);

// Compares two large unsigned integers, returning 0 if they are equal, 1 if
// the second is greater than the first, and -1 if the first is greater than
// the second.
// this == that --> 0
// this < that  --> 1
// this > that  --> -1
int LargeUIntCompare(const LargeUInt* this, const LargeUInt* that);

// Returns 1 if the first argument is less than the second, otherwise 0.
int LargeUIntLessThan(const LargeUInt* this, const LargeUInt* that);

// Returns 1 if the first argument is less than the second or if both are
// equal. Otherwise returns 0.
int LargeUIntLessThanOrEqual(const LargeUInt* this, const LargeUInt* that);

// Returns 1 if both arguments are equal, otherwise 0.
int LargeUIntEqual(const LargeUInt* this, const LargeUInt* that);

// Copies the value from the first argument into the second argument.
void LargeUIntClone(const LargeUInt* that, LargeUInt* this);

// Adds a new zero byte at the low order end of the integer and shifts
// existing bytes up. Equivalent to multiplying by 256.
void LargeUIntByteShiftInc(LargeUInt* this);

// Reduces the number of bytes in the integer by shifting all bytes into a
// lower position. The lowest order byte is removed and its value returned. 
int LargeUIntByteShiftDec(LargeUInt* this);

// Adds zero bytes at the low order end of the integer and shifts
// existing bytes up. Each byte shifted is equivalent to multiplying by a
// power of 256.
void LargeUIntMultiByteShiftInc(int num_bytes, LargeUInt* this);

// Reduces the number of bytes in the integer by shifting all bytes into a
// lower position. The low order bytes are removed. 
void LargeUIntMultiByteShiftDec(int num_bytes, LargeUInt* this);

// Adds the first argument into the second argument. The value of the second
// argument is set to the sum of this and that.
void LargeUIntAdd(const LargeUInt* that, LargeUInt* this);

// Adds a small number (less than 256) to the large unsigned integer.
void LargeUIntAddByte(int byte, LargeUInt* this);

// Adds 1 to the provided large unsigned integer.
void LargeUIntIncrement(LargeUInt* this);

// Subtracts the first argument from the second argument. The value of the
// second argument is set to the difference of this and that. If the second
// argument is smaller than the first, execution will halt rather than
// allowing the second argument to go negative.
void LargeUIntSub(const LargeUInt* that, LargeUInt* this);

// Subtracts 1 to the provided large unsigned integer. The integer must be
// greater than zero.
void LargeUIntDecrement(LargeUInt* this);

// Multiplies the second argument by the first, storing the result in the
// location provided in the second argument. Will cause the program to halt
// if the result is too big to store in a large unsigned integer.
void LargeUIntMultiply(const LargeUInt* that, LargeUInt* this);

// Divides the numerator by the denominator storing the results in the
// quotient and remainder.
void LargeUIntDivide(const LargeUInt* numerator, const LargeUInt* denominator,
                     LargeUInt* quotient, LargeUInt* remainder);

// Performs modulus on the first argument. The remainder of first argument
// modulo the second argument is stored in the third argument.
void LargeUIntMod(const LargeUInt* numerator, const LargeUInt* divisor,
                  LargeUInt* remainder);

// Finds an integer that is close to the square root of the first argument
// without being less than the actual square root. Intended for a rough
// overestimate of the square root.
void LargeUIntApproximateSquareRoot(const LargeUInt* this, LargeUInt* root);

#endif
