/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2004-2007 The Trustees of Indiana University and Indiana
 *                         University Research and Technology
 *                         Corporation.  All rights reserved.
 * Copyright (c) 2004-2006 The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 * Copyright (c) 2004-2005 High Performance Computing Center Stuttgart,
 *                         University of Stuttgart.  All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * Copyright (c) 2008      Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2012-2013 Los Alamos National Security, LLC. All rights
 *                         reserved.
 * Copyright (c) 2016      Intel, Inc. All rights reserved
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 * $HEADER$
 */

/**
 * @file
 *
 * This is the private declarations for the MCA variable system.
 * This file is internal to the MCA variable system and should not
 * need to be used by any other elements in SCON except the
 * special case of the ompi_info command.
 *
 * All the rest of the doxygen documentation in this file is marked as
 * "internal" and won't show up unless you specifically tell doxygen
 * to generate internal documentation (by default, it is skipped).
 */

#ifndef SCON_MCA_BASE_VAR_INTERNAL_H
#define SCON_MCA_BASE_VAR_INTERNAL_H

#include <src/include/scon_config.h>

#include "src/class/scon_object.h"
#include "src/class/scon_list.h"
#include "src/class/scon_value_array.h"
#include "src/class/scon_pointer_array.h"
#include "src/class/scon_hash_table.h"
#include "src/mca/base/scon_mca_base_var.h"

BEGIN_C_DECLS

/* Internal flags start at bit 16 */
#define SCON_MCA_BASE_VAR_FLAG_EXTERNAL_MASK 0x0000ffff

typedef enum {
    /** Variable is valid */
    SCON_MCA_BASE_VAR_FLAG_VALID   = 0x00010000,
    /** Variable is a synonym */
    SCON_MCA_BASE_VAR_FLAG_SYNONYM = 0x00020000,
    /** mbv_source_file needs to be freed */
    SCON_MCA_BASE_VAR_FLAG_SOURCE_FILE_NEEDS_FREE = 0x00040000
} scon_mca_base_var_flag_internal_t;

#define SCON_VAR_FLAG_ISSET(var, flag) (!!((var).mbp_flags & (flag)))

#define SCON_VAR_IS_VALID(var) (!!((var).mbv_flags & SCON_MCA_BASE_VAR_FLAG_VALID))
#define SCON_VAR_IS_SYNONYM(var) (!!((var).mbv_flags & SCON_MCA_BASE_VAR_FLAG_SYNONYM))
#define SCON_VAR_IS_INTERNAL(var) (!!((var).mbv_flags & SCON_MCA_BASE_VAR_FLAG_INTERNAL))
#define SCON_VAR_IS_DEFAULT_ONLY(var) (!!((var).mbv_flags & SCON_MCA_BASE_VAR_FLAG_DEFAULT_ONLY))
#define SCON_VAR_IS_SETTABLE(var) (!!((var).mbv_flags & SCON_MCA_BASE_VAR_FLAG_SETTABLE))
#define SCON_VAR_IS_DEPRECATED(var) (!!((var).mbv_flags & SCON_MCA_BASE_VAR_FLAG_DEPRECATED))

extern const char *scon_var_type_names[];
extern const size_t scon_var_type_sizes[];
extern bool scon_mca_base_var_initialized;

/**
 * \internal
 *
 * Structure for holding param names and values read in from files.
 */
struct scon_mca_base_var_file_value_t {
    /** Allow this to be an SCON OBJ */
    scon_list_item_t super;

    /** Parameter name */
    char *mbvfv_var;
    /** Parameter value */
    char *mbvfv_value;
    /** File it came from */
    char *mbvfv_file;
    /** Line it came from */
    int mbvfv_lineno;
};

/**
 * \internal
 *
 * Convenience typedef
 */
typedef struct scon_mca_base_var_file_value_t scon_mca_base_var_file_value_t;

/**
 * Object declaration for scon_mca_base_var_file_value_t
 */
SCON_CLASS_DECLARATION(scon_mca_base_var_file_value_t);

/**
 * \internal
 *
 * Get a group
 *
 * @param[in]  group_index Group index
 * @param[out] group       Returned group if it exists
 * @param[in]  invalidok   Return group even if it has been deregistered
 */
int scon_mca_base_var_group_get_internal (const int group_index, scon_mca_base_var_group_t **group, bool invalidok);

/**
 * \internal
 *
 * Parse a parameter file.
 */
int scon_mca_base_parse_paramfile(const char *paramfile, scon_list_t *list);

/**
 * \internal
 *
 * Add a variable to a group
 */
int scon_mca_base_var_group_add_var (const int group_index, const int param_index);

/**
 * \internal
 *
 * Add a performance variable to a group
 */
int scon_mca_base_var_group_add_pvar (const int group_index, const int param_index);

/**
 * \internal
 *
 * Generate a full name with _ between all of the non-NULL arguments
 */
int scon_mca_base_var_generate_full_name4 (const char *project, const char *framework,
                                           const char *component, const char *variable,
                                           char **full_name);

/**
 * \internal
 *
 * Call save_value callback for generated internal mca parameter storing env variables
 */
int scon_mca_base_internal_env_store(void);

/**
 * \internal
 *
 * Initialize/finalize MCA variable groups
 */
int scon_mca_base_var_group_init (void);
int scon_mca_base_var_group_finalize (void);

END_C_DECLS

#endif /* SCON_MCA_BASE_VAR_INTERNAL_H */