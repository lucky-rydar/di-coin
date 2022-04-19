#pragma once

#include <lrrp.h>

/*
 * Adds transaction to mempool
 *
 * The problem with transactions. It can be cicled if several nodes knows
 * about each other and sends transaction to each other. Blocks have no such
 * problem because we can identify them
 */
