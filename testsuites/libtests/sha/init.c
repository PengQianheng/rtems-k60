/* SPDX-License-Identifier: BSD-2-Clause */

/*
 * Copyright (c) 2014 embedded brains GmbH.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <sha224.h>
#include <sha256.h>
#include <sha384.h>
#include <sha512.h>
#include <sha512t.h>
#include <stdio.h>
#include <string.h>

#include "tmacros.h"

#include <rtems/stackchk.h>

const char rtems_test_name[] = "SHA";

static const char *const test_vectors[] = {
  "abc",
  "",
  "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
  "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmn"
    "hijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu"
};

static const unsigned char
test_sha224_results[RTEMS_ARRAY_SIZE(test_vectors)][SHA224_DIGEST_LENGTH] = {
  {
    0x23, 0x09, 0x7d, 0x22, 0x34, 0x05, 0xd8, 0x22,
    0x86, 0x42, 0xa4, 0x77, 0xbd, 0xa2, 0x55, 0xb3,
    0x2a, 0xad, 0xbc, 0xe4, 0xbd, 0xa0, 0xb3, 0xf7,
    0xe3, 0x6c, 0x9d, 0xa7
  }, {
    0xd1, 0x4a, 0x02, 0x8c, 0x2a, 0x3a, 0x2b, 0xc9,
    0x47, 0x61, 0x02, 0xbb, 0x28, 0x82, 0x34, 0xc4,
    0x15, 0xa2, 0xb0, 0x1f, 0x82, 0x8e, 0xa6, 0x2a,
    0xc5, 0xb3, 0xe4, 0x2f
  }, {
    0x75, 0x38, 0x8b, 0x16, 0x51, 0x27, 0x76, 0xcc,
    0x5d, 0xba, 0x5d, 0xa1, 0xfd, 0x89, 0x01, 0x50,
    0xb0, 0xc6, 0x45, 0x5c, 0xb4, 0xf5, 0x8b, 0x19,
    0x52, 0x52, 0x25, 0x25
  }, {
    0xc9, 0x7c, 0xa9, 0xa5, 0x59, 0x85, 0x0c, 0xe9,
    0x7a, 0x04, 0xa9, 0x6d, 0xef, 0x6d, 0x99, 0xa9,
    0xe0, 0xe0, 0xe2, 0xab, 0x14, 0xe6, 0xb8, 0xdf,
    0x26, 0x5f, 0xc0, 0xb3
  }
};

static const unsigned char
test_sha256_results[RTEMS_ARRAY_SIZE(test_vectors)][SHA256_DIGEST_LENGTH] = {
  {
    0xba, 0x78, 0x16, 0xbf, 0x8f, 0x01, 0xcf, 0xea,
    0x41, 0x41, 0x40, 0xde, 0x5d, 0xae, 0x22, 0x23,
    0xb0, 0x03, 0x61, 0xa3, 0x96, 0x17, 0x7a, 0x9c,
    0xb4, 0x10, 0xff, 0x61, 0xf2, 0x00, 0x15, 0xad
  }, {
    0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14,
    0x9a, 0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24,
    0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c,
    0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55
  }, {
    0x24, 0x8d, 0x6a, 0x61, 0xd2, 0x06, 0x38, 0xb8,
    0xe5, 0xc0, 0x26, 0x93, 0x0c, 0x3e, 0x60, 0x39,
    0xa3, 0x3c, 0xe4, 0x59, 0x64, 0xff, 0x21, 0x67,
    0xf6, 0xec, 0xed, 0xd4, 0x19, 0xdb, 0x06, 0xc1
  }, {
    0xcf, 0x5b, 0x16, 0xa7, 0x78, 0xaf, 0x83, 0x80,
    0x03, 0x6c, 0xe5, 0x9e, 0x7b, 0x04, 0x92, 0x37,
    0x0b, 0x24, 0x9b, 0x11, 0xe8, 0xf0, 0x7a, 0x51,
    0xaf, 0xac, 0x45, 0x03, 0x7a, 0xfe, 0xe9, 0xd1
  }
};

static const unsigned char
test_sha384_results[RTEMS_ARRAY_SIZE(test_vectors)][SHA384_DIGEST_LENGTH] = {
  {
    0xcb, 0x00, 0x75, 0x3f, 0x45, 0xa3, 0x5e, 0x8b,
    0xb5, 0xa0, 0x3d, 0x69, 0x9a, 0xc6, 0x50, 0x07,
    0x27, 0x2c, 0x32, 0xab, 0x0e, 0xde, 0xd1, 0x63,
    0x1a, 0x8b, 0x60, 0x5a, 0x43, 0xff, 0x5b, 0xed,
    0x80, 0x86, 0x07, 0x2b, 0xa1, 0xe7, 0xcc, 0x23,
    0x58, 0xba, 0xec, 0xa1, 0x34, 0xc8, 0x25, 0xa7
  }, {
    0x38, 0xb0, 0x60, 0xa7, 0x51, 0xac, 0x96, 0x38,
    0x4c, 0xd9, 0x32, 0x7e, 0xb1, 0xb1, 0xe3, 0x6a,
    0x21, 0xfd, 0xb7, 0x11, 0x14, 0xbe, 0x07, 0x43,
    0x4c, 0x0c, 0xc7, 0xbf, 0x63, 0xf6, 0xe1, 0xda,
    0x27, 0x4e, 0xde, 0xbf, 0xe7, 0x6f, 0x65, 0xfb,
    0xd5, 0x1a, 0xd2, 0xf1, 0x48, 0x98, 0xb9, 0x5b
  }, {
    0x33, 0x91, 0xfd, 0xdd, 0xfc, 0x8d, 0xc7, 0x39,
    0x37, 0x07, 0xa6, 0x5b, 0x1b, 0x47, 0x09, 0x39,
    0x7c, 0xf8, 0xb1, 0xd1, 0x62, 0xaf, 0x05, 0xab,
    0xfe, 0x8f, 0x45, 0x0d, 0xe5, 0xf3, 0x6b, 0xc6,
    0xb0, 0x45, 0x5a, 0x85, 0x20, 0xbc, 0x4e, 0x6f,
    0x5f, 0xe9, 0x5b, 0x1f, 0xe3, 0xc8, 0x45, 0x2b
  }, {
    0x09, 0x33, 0x0c, 0x33, 0xf7, 0x11, 0x47, 0xe8,
    0x3d, 0x19, 0x2f, 0xc7, 0x82, 0xcd, 0x1b, 0x47,
    0x53, 0x11, 0x1b, 0x17, 0x3b, 0x3b, 0x05, 0xd2,
    0x2f, 0xa0, 0x80, 0x86, 0xe3, 0xb0, 0xf7, 0x12,
    0xfc, 0xc7, 0xc7, 0x1a, 0x55, 0x7e, 0x2d, 0xb9,
    0x66, 0xc3, 0xe9, 0xfa, 0x91, 0x74, 0x60, 0x39
  }
};

static const unsigned char
test_sha512_results[RTEMS_ARRAY_SIZE(test_vectors)][SHA512_DIGEST_LENGTH] = {
  {
    0xdd, 0xaf, 0x35, 0xa1, 0x93, 0x61, 0x7a, 0xba,
    0xcc, 0x41, 0x73, 0x49, 0xae, 0x20, 0x41, 0x31,
    0x12, 0xe6, 0xfa, 0x4e, 0x89, 0xa9, 0x7e, 0xa2,
    0x0a, 0x9e, 0xee, 0xe6, 0x4b, 0x55, 0xd3, 0x9a,
    0x21, 0x92, 0x99, 0x2a, 0x27, 0x4f, 0xc1, 0xa8,
    0x36, 0xba, 0x3c, 0x23, 0xa3, 0xfe, 0xeb, 0xbd,
    0x45, 0x4d, 0x44, 0x23, 0x64, 0x3c, 0xe8, 0x0e,
    0x2a, 0x9a, 0xc9, 0x4f, 0xa5, 0x4c, 0xa4, 0x9f
  }, {
    0xcf, 0x83, 0xe1, 0x35, 0x7e, 0xef, 0xb8, 0xbd,
    0xf1, 0x54, 0x28, 0x50, 0xd6, 0x6d, 0x80, 0x07,
    0xd6, 0x20, 0xe4, 0x05, 0x0b, 0x57, 0x15, 0xdc,
    0x83, 0xf4, 0xa9, 0x21, 0xd3, 0x6c, 0xe9, 0xce,
    0x47, 0xd0, 0xd1, 0x3c, 0x5d, 0x85, 0xf2, 0xb0,
    0xff, 0x83, 0x18, 0xd2, 0x87, 0x7e, 0xec, 0x2f,
    0x63, 0xb9, 0x31, 0xbd, 0x47, 0x41, 0x7a, 0x81,
    0xa5, 0x38, 0x32, 0x7a, 0xf9, 0x27, 0xda, 0x3e
  }, {
    0x20, 0x4a, 0x8f, 0xc6, 0xdd, 0xa8, 0x2f, 0x0a,
    0x0c, 0xed, 0x7b, 0xeb, 0x8e, 0x08, 0xa4, 0x16,
    0x57, 0xc1, 0x6e, 0xf4, 0x68, 0xb2, 0x28, 0xa8,
    0x27, 0x9b, 0xe3, 0x31, 0xa7, 0x03, 0xc3, 0x35,
    0x96, 0xfd, 0x15, 0xc1, 0x3b, 0x1b, 0x07, 0xf9,
    0xaa, 0x1d, 0x3b, 0xea, 0x57, 0x78, 0x9c, 0xa0,
    0x31, 0xad, 0x85, 0xc7, 0xa7, 0x1d, 0xd7, 0x03,
    0x54, 0xec, 0x63, 0x12, 0x38, 0xca, 0x34, 0x45
  }, {
    0x8e, 0x95, 0x9b, 0x75, 0xda, 0xe3, 0x13, 0xda,
    0x8c, 0xf4, 0xf7, 0x28, 0x14, 0xfc, 0x14, 0x3f,
    0x8f, 0x77, 0x79, 0xc6, 0xeb, 0x9f, 0x7f, 0xa1,
    0x72, 0x99, 0xae, 0xad, 0xb6, 0x88, 0x90, 0x18,
    0x50, 0x1d, 0x28, 0x9e, 0x49, 0x00, 0xf7, 0xe4,
    0x33, 0x1b, 0x99, 0xde, 0xc4, 0xb5, 0x43, 0x3a,
    0xc7, 0xd3, 0x29, 0xee, 0xb6, 0xdd, 0x26, 0x54,
    0x5e, 0x96, 0xe5, 0x5b, 0x87, 0x4b, 0xe9, 0x09
  }
};

static const unsigned char test_sha512_224_results
[RTEMS_ARRAY_SIZE(test_vectors)][SHA512_224_DIGEST_LENGTH] = {
  {
    0x46, 0x34, 0x27, 0x0f, 0x70, 0x7b, 0x6a, 0x54,
    0xda, 0xae, 0x75, 0x30, 0x46, 0x08, 0x42, 0xe2,
    0x0e, 0x37, 0xed, 0x26, 0x5c, 0xee, 0xe9, 0xa4,
    0x3e, 0x89, 0x24, 0xaa
  }, {
    0x6e, 0xd0, 0xdd, 0x02, 0x80, 0x6f, 0xa8, 0x9e,
    0x25, 0xde, 0x06, 0x0c, 0x19, 0xd3, 0xac, 0x86,
    0xca, 0xbb, 0x87, 0xd6, 0xa0, 0xdd, 0xd0, 0x5c,
    0x33, 0x3b, 0x84, 0xf4
  }, {
    0xe5, 0x30, 0x2d, 0x6d, 0x54, 0xbb, 0x24, 0x22,
    0x75, 0xd1, 0xe7, 0x62, 0x2d, 0x68, 0xdf, 0x6e,
    0xb0, 0x2d, 0xed, 0xd1, 0x3f, 0x56, 0x4c, 0x13,
    0xdb, 0xda, 0x21, 0x74
  }, {
    0x23, 0xfe, 0xc5, 0xbb, 0x94, 0xd6, 0x0b, 0x23,
    0x30, 0x81, 0x92, 0x64, 0x0b, 0x0c, 0x45, 0x33,
    0x35, 0xd6, 0x64, 0x73, 0x4f, 0xe4, 0x0e, 0x72,
    0x68, 0x67, 0x4a, 0xf9
  }
};

static const unsigned char test_sha512_256_results
[RTEMS_ARRAY_SIZE(test_vectors)][SHA512_256_DIGEST_LENGTH] = {
  {
    0x53, 0x04, 0x8e, 0x26, 0x81, 0x94, 0x1e, 0xf9,
    0x9b, 0x2e, 0x29, 0xb7, 0x6b, 0x4c, 0x7d, 0xab,
    0xe4, 0xc2, 0xd0, 0xc6, 0x34, 0xfc, 0x6d, 0x46,
    0xe0, 0xe2, 0xf1, 0x31, 0x07, 0xe7, 0xaf, 0x23
  }, {
    0xc6, 0x72, 0xb8, 0xd1, 0xef, 0x56, 0xed, 0x28,
    0xab, 0x87, 0xc3, 0x62, 0x2c, 0x51, 0x14, 0x06,
    0x9b, 0xdd, 0x3a, 0xd7, 0xb8, 0xf9, 0x73, 0x74,
    0x98, 0xd0, 0xc0, 0x1e, 0xce, 0xf0, 0x96, 0x7a
  }, {
    0xbd, 0xe8, 0xe1, 0xf9, 0xf1, 0x9b, 0xb9, 0xfd,
    0x34, 0x06, 0xc9, 0x0e, 0xc6, 0xbc, 0x47, 0xbd,
    0x36, 0xd8, 0xad, 0xa9, 0xf1, 0x18, 0x80, 0xdb,
    0xc8, 0xa2, 0x2a, 0x70, 0x78, 0xb6, 0xa4, 0x61
  }, {
    0x39, 0x28, 0xe1, 0x84, 0xfb, 0x86, 0x90, 0xf8,
    0x40, 0xda, 0x39, 0x88, 0x12, 0x1d, 0x31, 0xbe,
    0x65, 0xcb, 0x9d, 0x3e, 0xf8, 0x3e, 0xe6, 0x14,
    0x6f, 0xea, 0xc8, 0x61, 0xe1, 0x9b, 0x56, 0x3a
  }
};

static void print_result(const unsigned char *r, size_t n)
{
  size_t i;

  for (i = 0; i < n; ++i) {
    if (i == 0) {
      /* Do nothing */
    } else if (i % 32 == 0) {
      printf("\n");
    } else if (i % 8 == 0) {
      printf(" ");
    }

    printf("%02x", r[i]);
  }

  printf("\n");
}

static void test_sha224(void)
{
  size_t i;

  printf("test SHA224\n");

  for (i = 0; i < RTEMS_ARRAY_SIZE(test_vectors); ++i) {
    SHA224_CTX ctx;
    unsigned char r[SHA224_DIGEST_LENGTH];
    const char *s = test_vectors[i];

    SHA224_Init(&ctx);
    SHA224_Update(&ctx, s, strlen(s));
    SHA224_Final(r, &ctx);

    print_result(&r[0], sizeof(r));

    rtems_test_assert(
      memcmp(&r[0], &test_sha224_results[i][0], sizeof(r)) == 0
    );
  }
}

static void test_sha256(void)
{
  size_t i;

  printf("test SHA256\n");

  for (i = 0; i < RTEMS_ARRAY_SIZE(test_vectors); ++i) {
    SHA256_CTX ctx;
    unsigned char r[SHA256_DIGEST_LENGTH];
    const char *s = test_vectors[i];

    SHA256_Init(&ctx);
    SHA256_Update(&ctx, s, strlen(s));
    SHA256_Final(r, &ctx);

    print_result(&r[0], sizeof(r));

    rtems_test_assert(
      memcmp(&r[0], &test_sha256_results[i][0], sizeof(r)) == 0
    );
  }
}

static void test_sha384(void)
{
  size_t i;

  printf("test SHA384\n");

  for (i = 0; i < RTEMS_ARRAY_SIZE(test_vectors); ++i) {
    SHA384_CTX ctx;
    unsigned char r[SHA384_DIGEST_LENGTH];
    const char *s = test_vectors[i];

    SHA384_Init(&ctx);
    SHA384_Update(&ctx, s, strlen(s));
    SHA384_Final(r, &ctx);

    print_result(&r[0], sizeof(r));

    rtems_test_assert(
      memcmp(&r[0], &test_sha384_results[i][0], sizeof(r)) == 0
    );
  }
}

static void test_sha512(void)
{
  size_t i;

  printf("test SHA512\n");

  for (i = 0; i < RTEMS_ARRAY_SIZE(test_vectors); ++i) {
    SHA512_CTX ctx;
    unsigned char r[SHA512_DIGEST_LENGTH];
    const char *s = test_vectors[i];

    SHA512_Init(&ctx);
    SHA512_Update(&ctx, s, strlen(s));
    SHA512_Final(r, &ctx);

    print_result(&r[0], sizeof(r));

    rtems_test_assert(
      memcmp(&r[0], &test_sha512_results[i][0], sizeof(r)) == 0
    );
  }
}

static void test_sha512_224(void)
{
  size_t i;

  printf("test SHA512-224\n");

  for (i = 0; i < RTEMS_ARRAY_SIZE(test_vectors); ++i) {
    SHA512_CTX ctx;
    unsigned char r[SHA512_224_DIGEST_LENGTH];
    const char *s = test_vectors[i];

    SHA512_224_Init(&ctx);
    SHA512_224_Update(&ctx, s, strlen(s));
    SHA512_224_Final(r, &ctx);

    print_result(&r[0], sizeof(r));

    rtems_test_assert(
      memcmp(&r[0], &test_sha512_224_results[i][0], sizeof(r)) == 0
    );
  }
}

static void test_sha512_256(void)
{
  size_t i;

  printf("test SHA512-256\n");

  for (i = 0; i < RTEMS_ARRAY_SIZE(test_vectors); ++i) {
    SHA512_CTX ctx;
    unsigned char r[SHA512_256_DIGEST_LENGTH];
    const char *s = test_vectors[i];

    SHA512_256_Init(&ctx);
    SHA512_256_Update(&ctx, s, strlen(s));
    SHA512_256_Final(r, &ctx);

    print_result(&r[0], sizeof(r));

    rtems_test_assert(
      memcmp(&r[0], &test_sha512_256_results[i][0], sizeof(r)) == 0
    );
  }
}

static void Init(rtems_task_argument arg)
{
  TEST_BEGIN();

  test_sha224();
  test_sha256();
  test_sha384();
  test_sha512();
  test_sha512_224();
  test_sha512_256();
  rtems_stack_checker_report_usage();

  TEST_END();
  rtems_test_exit(0);
}

#define CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER
#define CONFIGURE_APPLICATION_NEEDS_SIMPLE_CONSOLE_DRIVER

#define CONFIGURE_MAXIMUM_TASKS 1

#define CONFIGURE_STACK_CHECKER_ENABLED

#define CONFIGURE_INITIAL_EXTENSIONS RTEMS_TEST_INITIAL_EXTENSION

#define CONFIGURE_RTEMS_INIT_TASKS_TABLE

/*
 * The SHA512_Update() function may need a lot of stack space if the compiler
 * optimization is disabled.
 */
#define CONFIGURE_INIT_TASK_STACK_SIZE (32 * 1024)

#define CONFIGURE_INIT

#include <rtems/confdefs.h>
