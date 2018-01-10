/*
 * This file is part of libgpiod.
 *
 * Copyright (C) 2017 Bartosz Golaszewski <bartekgola@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 */

/* Test cases for the gpiodetect program. */

#include "gpiod-test.h"

#include <stdio.h>

static void gpiodetect_simple(void)
{
	test_tool_run("gpiodetect", (char *)NULL);
	test_tool_wait();

	TEST_ASSERT(test_tool_exited());
	TEST_ASSERT_RET_OK(test_tool_exit_status());
	TEST_ASSERT_NOT_NULL(test_tool_stdout());
	TEST_ASSERT_STR_CONTAINS(test_tool_stdout(),
				 test_build_str("%s [gpio-mockup-A] (4 lines)",
						test_chip_name(0)));
	TEST_ASSERT_STR_CONTAINS(test_tool_stdout(),
				 test_build_str("%s [gpio-mockup-B] (8 lines)",
						test_chip_name(1)));
	TEST_ASSERT_STR_CONTAINS(test_tool_stdout(),
				 test_build_str("%s [gpio-mockup-C] (16 lines)",
						test_chip_name(2)));
	TEST_ASSERT_NULL(test_tool_stderr());
}
TEST_DEFINE(gpiodetect_simple,
	    "tools: gpiodetect - simple",
	    0, { 4, 8, 16 });

static void gpiodetect_invalid_args(void)
{
	test_tool_run("gpiodetect", "unused argument", (char *)NULL);
	test_tool_wait();

	TEST_ASSERT(test_tool_exited());
	TEST_ASSERT_EQ(test_tool_exit_status(), 1);
	TEST_ASSERT_NULL(test_tool_stdout());
	TEST_ASSERT_NOT_NULL(test_tool_stderr());
	TEST_ASSERT_STR_CONTAINS(test_tool_stderr(), "unrecognized argument");
}
TEST_DEFINE(gpiodetect_invalid_args,
	    "tools: gpiodetect - invalid arguments",
	    0, { });
