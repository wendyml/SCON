/*
 * Copyright (c) 2015     Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2016     Intel, Inc. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

#ifndef SCON_PDL_PDLOPEN
#define SCON_PDL_PDLOPEN

#include <src/include/scon_config.h>

#include "src/mca/sdl/sdl.h"

extern scon_sdl_base_module_t scon_sdl_sdlopen_module;

/*
 * Dynamic library handles generated by this component.
 *
 * If we're debugging, keep a copy of the name of the file we've opened.
 */
struct scon_sdl_handle_t {
    void *dlopen_handle;
#if SCON_ENABLE_DEBUG
    void *filename;
#endif
};

typedef struct {
    scon_sdl_base_component_t base;

    char *filename_suffixes_mca_storage;
    char **filename_suffixes;
} scon_sdl_sdlopen_component_t;

extern scon_sdl_sdlopen_component_t mca_sdl_sdlopen_component;

#endif /* SCON_PDL_PDLOPEN */